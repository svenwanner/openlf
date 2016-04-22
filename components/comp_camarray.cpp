/*
* Copyright (c) 2015 Heidelberg Collaboratory for Image Processing
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
* Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* Author Sven Wanner, Maximilian Diebold, Hendrik Siedelmann 
*
*/
#include <vigra/impex.hxx>
#include <thread>

#include "clif/subset3d.hpp"
#include "clif/preproc.hpp"
#include "clif/hdf5.hpp"

#include "dspatch/DspComponent.h"
#include "dspatch/DspPlugin.h"

#include "openlf.hpp"
#include "openlf/types.hpp"
#include "openlf/comp_mav.hpp"

#include "boost/algorithm/string.hpp"

#include "comp_camarray/cameraarray.h"

#ifdef OPENLF_WITH_OPENMP
	#include <omp.h>
#endif

#include <unordered_set>

//for printprogress
#include <cstdarg>

using namespace clif;
using namespace openlf;

//typedef unsigned int _uint;

#define DPPT DspParameter::ParamType
  
class component : public DspComponent {
public:
  component();
  DSPCOMPONENT_TRIVIAL_CLONE(component);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:  
  LF _out;
  clif::Dataset _out_set;
  std::vector<float> _exposures;
  camerarray::CameraArray *_cams = NULL;
  
  std::thread *_liveview_thread = NULL;
  int cam_count = 0;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  HANDLE Array_Of_Thread_Handles[1];
  HANDLE Handle_Of_Thread_1 = NULL;
#endif
  
  bool ParameterUpdating_(int index, const DspParameter& param);
  virtual ~component();
};
  
component::component()
{
  setTypeName_("COMP_camarray");
  AddInput_("input");
  AddOutput_("output");
  AddParameter_("camera_config", DspParameter(DspParameter::ParamType::LoadPath));
  AddParameter_("exposures", DspParameter(DspParameter::ParamType::String));
}

static cv::Mat view;

void cvGetManyViews(char* title, int inN, cv::Mat* outMats, unsigned int inNX, unsigned int inNY, unsigned int inType) {
	int i;
	int m, n;

	int size;

	// w - Maximum number of images in a row 
	// h - Maximum number of images in a column 
	int w, h;

	if (inN == 1) {
		w = 1; h = 1;
	}
	else {
		w = 4; h = 3;
	}

	size = inNX / h;

	// scale - How much we have to resize the image

	view.create(100 + size*h, 100 + size*w, inType);

	for (i = 0, m = 20, n = 20; i < inN; i++, m += (20 + size)) {

		// Used to Align the images
		if (i % w == 0 && m != 20) {
			m = 20;
			n += 20 + size;
		}

		outMats[i] = view(Range(n, n + size), Range(m, m + size));
	}
	imshow(title, view);
}



#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

static int updating = 0;
void cvUpdateManyViews(char* inTitle) {
	if (updating == 0) { //<=--possible concurrent execution, do cleanly
		updating = 1;
		imshow(inTitle, view);

		HWND hWnd = (HWND)cvGetWindowHandle(inTitle);
		::SendMessage(hWnd, WM_PAINT, 0, 0);
		updating = 0;
	}
}

#define BUF_SIZE 255

DWORD WINAPI Thread_no_1(LPVOID lpParam)
{
	camerarray::CameraArray * _cams_thread = NULL;
	int     count = 0;
	HANDLE  hStdout = NULL;

	// Get Handle To screen.
	// Else how will we print?
	if ((hStdout = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
		return 1;

	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	// Cast the parameter to the correct
	// data type passed by called i.e main() in our case.
	_cams_thread = (camerarray::CameraArray*)lpParam;
	
	cv::Mat* im = new cv::Mat[_cams_thread->GetNumberOfCameras()];
	cv::Mat* views = new cv::Mat[_cams_thread->GetNumberOfCameras()];
	cv::Mat tmp;

	// set up window
	cv::namedWindow("LiveView", cv::WINDOW_NORMAL);
	cvGetManyViews("LiveView", _cams_thread->GetNumberOfCameras(), views, 1000, 1000, CV_8UC3);

	std::cout << "cams.GetNumberOfCameras(): " << _cams_thread->GetNumberOfCameras() << std::endl;
	int j = 0;
	bool outputSelection = true;
	bool quitSelection = false;

	while (true) {
		for (int i = 0; i < _cams_thread->GetNumberOfCameras(); i++) {
			int curIdx = _cams_thread->GetCamera(i)->GetCurrentImage() - 1;
			if (curIdx < 0)
				curIdx = _cams_thread->GetNumberOfCameras();
			im[i] = _cams_thread->GetImageFromBuffer(i, curIdx);
		}
		char c = cv::waitKey(10);
		if (c == 'q')
			quitSelection = true;
		if (c == 'a'){
			_cams_thread->SetTriggerMode(0);
		}
		if (c == 'm')
			_cams_thread->SetTriggerMode(1);
		if (c == 'u'){
			j++;
			outputSelection = false;
			if (j >= _cams_thread->GetNumberOfCameras()) j = 0;
		}
		if (c == 'l'){
			j--;
			outputSelection = false;
			if (j < 0) j = _cams_thread->GetNumberOfCameras();
		}
		if (c == 'r'){
			outputSelection = true;
		}

		for (int i = 0; i < _cams_thread->GetNumberOfCameras(); i++) {
			cv::cvtColor(im[i], tmp, CV_GRAY2RGB);
			resize(tmp, views[i], views[i].size());
		}

		if (outputSelection){
			cvUpdateManyViews("LiveView");
		}
		else{
			cv::imshow("LiveView", im[j]);
		}
		if (quitSelection){
			cv::destroyWindow("LiveView");
			break;
		}
	}

	// clean up 
	delete[] im;
	delete[] views;
	
	return 0;
}
#else


/*Function///////////////////////////////////////////////////////////////

Name:       cvShowManyImages

Purpose:    This is a function illustrating how to display more than one 
               image in a single window using Intel OpenCV

Parameters: char *title: Title of the window to be displayed
            int nArgs:   Number of images to be displayed
            ...:         IplImage*, which contains the images

Language:   C++

The method used is to set the ROIs of a Single Big image and then resizing 
and copying the input images on to the Single Big Image.

This function does not stretch the image... 
It resizes the image without modifying the width/height ratio..

This function can be called like this:

cvShowManyImages("Images", 2, img1, img2);
or
cvShowManyImages("Images", 5, img2, img2, img3, img4, img5);

This function can display upto 12 images in a single window.
It does not check whether the arguments are of type IplImage* or not.
The maximum window size is 700 by 660 pixels.
Does not display anything if the number of arguments is less than
    one or greater than 12.

If you pass a pointer that is not IplImage*, Error will occur.
Take care of the number of arguments you pass, and the type of arguments, 
which should be of type IplImage* ONLY.

Idea was from BettySanchi of OpenCV Yahoo! Groups.

If you have trouble compiling and/or executing
this code, I would like to hear about it.

You could try posting on the OpenCV Yahoo! Groups
[url]http://groups.yahoo.com/group/OpenCV/messages/ [/url]


Parameswaran, 
Chennai, India.

cegparamesh[at]gmail[dot]com            

...
///////////////////////////////////////////////////////////////////////*/
/*
void cvShowManyImages(char* title, int nArgs, ...) {

    // img - Used for getting the arguments 
    cv::Mat img;

    // DispImage - the image in which input images are to be copied
	//Mat DispImage;

    int size;
    int i;
    int m, n;
    int x, y;

    // w - Maximum number of images in a row 
    // h - Maximum number of images in a column 
    int w, h;

    // scale - How much we have to resize the image
    float scale;
    int max;

    // If the number of arguments is lesser than 0 or greater than 18
    // return without displaying 
    if(nArgs <= 0) {
        printf("Number of arguments too small....\n");
        return;
    }
    else if(nArgs > 18) {
        printf("Number of arguments too large....\n");
        return;
    }
    // Determine the size of the image, 
    // and the number of rows/cols 
    // from number of arguments 
    else if (nArgs == 1) {
        w = h = 1;
        size = 400;
    }
    else if (nArgs == 2) {
        w = 2; h = 1;
        size = 400;
    }
    else if (nArgs == 3 || nArgs == 4) {
        w = 2; h = 2;
        size = 400;
    }
    else if (nArgs == 5 || nArgs == 6) {
        w = 3; h = 2;
        size = 400;
    }
    else if (nArgs == 7 || nArgs == 8) {
        w = 4; h = 2;
        size = 400;
    }
	else if (nArgs == 16) {
        w = 4; h = 4;
        size = 400;
    }
    else {
        w = 4; h = 3;
        size = 400;
    }

    // Create a new 1 channel image
   cv::Mat DispImage(cvSize(100 + size*w, 60 + size*h), CV_8UC1);

    // Used to get the arguments passed
    va_list args;
    va_start(args, nArgs);

    // Loop for nArgs number of arguments
    for (i = 0, m = 20, n = 20; i < nArgs; i++, m += (20 + size)) {
		cv::Mat* ptr;
        // Get the Pointer to the IplImage
        ptr = va_arg(args, cv::Mat*);

		
        // Check whether it is NULL or not
        // If it is NULL, release the image, and return
        //if(img == 0) {
        //    printf("Invalid arguments");
        //    cvReleaseImage(&DispImage);
        //    return;
        //}

        // Find the width and height of the image
        x = ptr->cols;//width;
        y = ptr->rows;//->height;

        // Find whether height or width is greater in order to resize the image
        max = (x > y)? x: y;

        // Find the scaling factor to resize the image
        scale = (float) ( (float) max / size );

        // Used to Align the images
        if( i % w == 0 && m!= 20) {
            m = 20;
            n+= 20 + size;
        }

        // Set the image ROI to display the current image
		cv::Mat DispImageROI;
		DispImageROI = DispImage(Range(n,n+(int)( y/scale )),Range(m,m+(int)( x/scale )));

		//cvSetImageROI(DispImage, cvRect(m, n, (int)( x/scale ), (int)( y/scale )));

        // Resize the input image and copy the it to the Single Big Image
        //cvResize(img, DispImage);

		resize(*ptr, DispImageROI, DispImageROI.size() );

        // Reset the ROI in order to display the next image
        //cvResetImageROI(DispImage);
    }

    // Create a new window, and show the Single Big Image
    imshow(title, DispImage);

    // End the number of arguments
    va_end(args);
}




static int updating = 0;

void cvUpdateManyViews(char* inTitle) {
imshow(inTitle, view);
//	if(updating == 0) { //<=--possible concurrent execution, do cleanly
//		updating = 1;
//		imshow(inTitle, view);
//
//		HWND hWnd = (HWND)cvGetWindowHandle(inTitle);
//		::SendMessage(hWnd, WM_PAINT, 0, 0);
//		updating = 0;
//	}
}

void liveview(camerarray::CameraArray *array)
{
  uint last_img = 0;
  cv::Mat tmp;
  cv::Mat* im = new cv::Mat[array->GetNumberOfCameras()];
  cv::Mat* views = new cv::Mat[array->GetNumberOfCameras()];
  
  cv::namedWindow("liveview", cv::WINDOW_NORMAL);
  cvGetManyViews("liveview", array->GetNumberOfCameras(), views, 1000, 1000, CV_8UC3);
  
  int j = 0;
  bool outputSelection = true;
  
  return;
  
  while (true) {
    for (int i = 0; i < array->GetNumberOfCameras(); i++) {
      int curIdx = array->GetCamera(i)->GetCurrentImage()-1;
      if (curIdx < 0)
        curIdx = array->GetNumberOfCameras();
      im[i] = array->GetImageFromBuffer(i, curIdx);
    }
    char c;
    while (array->GetCamera(0)->GetCurrentImage() == last_img)
      c = cv::waitKey(50);
    last_img = array->GetCamera(0)->GetCurrentImage();
    if (c == 'q')
      break;
    if (c == 'u'){
      j++;
      outputSelection = false;
      if (j > array->GetNumberOfCameras()) j = 0;
    }
    if (c == 'l'){
      j--;
      outputSelection = false;
      if (j < 0) j = array->GetNumberOfCameras();
    }
    if (c == 'r') {
      outputSelection = true;
    }
    
#pragma omp parallel for private(tmp)
    for (int i = 0; i < array->GetNumberOfCameras(); i++) {
      cv::cvtColor(im[i], tmp, CV_GRAY2RGB);
      resize(tmp, views[i], views[i].size());
    }
    
    if (outputSelection){
      printf("show many!\n");
      cvUpdateManyViews("liveview");
    }
    else{
      cv::imshow("liveview", im[j]);
    }
  }
  
  // clean up 
  delete[] im;
  delete[] views;
}
*/

#endif

void component::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  LF *out = NULL;
    
  errorCond(GetParameter(0) && 
            GetParameter(0)->GetString() &&
            GetParameter(0)->GetString()->size() && 
            boost::filesystem::exists(*GetParameter(0)->GetString()),
            "missing camera config");
  RETURN_ON_ERROR

  
  
  std::string camera_config = *GetParameter(0)->GetString();
  float exp = *GetParameter(1)->GetFloat();
  
  printf("cam config: %s\n", camera_config.c_str());
  
  inputs.GetValue(0, in);
  
  errorCond(inputs.GetValue(0, in) && in, "missing input"); RETURN_ON_ERROR
  
  if (in)
    _out_set.memory_link(in->data);
  else {
    ClifFile f = h5_memory_file();
    _out_set.create(f);
  }
  
  out = &_out;
  out->data = &_out_set;
  outputs.SetValue(0, out);
  
  errorCond(out, "output creation failed"); RETURN_ON_ERROR

  if (!_cams) {
    _cams = new camerarray::CameraArray(camera_config.c_str());
    cam_count = _cams->GetNumberOfCameras();
    _cams->PrintConnectedCameras();
    _cams->SetTriggerMode(1);
    _cams->Acquire();
    _exposures.resize(cam_count);
    for(auto &e : _exposures)
      e = 50000;
    
  }
  
  errorCond(_cams->GetNumberOfCameras(), "no cameras found!"); RETURN_ON_ERROR  
  
  const std::string *exp_str =  GetParameter(1)->GetString();
  
  if (exp_str) {
    std::vector<std::string> strs;
    boost::split(strs, *exp_str, boost::is_any_of(" ,:;"));
    int idx = 0;
    for(auto s : strs) {
      float exp = std::stof(s);
      if (idx >= _exposures.size())
        break;
      _exposures[idx] = exp*1000.0;
      idx++;
    }
  }
  
  for (int i=0;i<cam_count;i++)
    _cams->GetCamera(i)->SetExposureTime(_exposures[i]);
  
  out->data->setAttribute("acquisition/exposure", _exposures);
  
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  
  if (!Handle_Of_Thread_1){
	  int Data_Of_Thread_1 = 1;
	  Handle_Of_Thread_1 = CreateThread(NULL, 0, Thread_no_1, _cams, 0, NULL);
	  if (Handle_Of_Thread_1 == NULL)
		  ExitProcess(Data_Of_Thread_1);
	  Array_Of_Thread_Handles[0] = Handle_Of_Thread_1;
  }
#else
  //if (!_liveview_thread)
  //  _liveview_thread = new std::thread(liveview, _cams);
#endif 

  if (configOnly())
    return;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__) 

  //if (Handle_Of_Thread_1){
	  //WaitForMultipleObjects(1, Array_Of_Thread_Handles, TRUE, 5);
	  //std::cout << "All threads are executed and get close." << std::endl;
	  //CloseHandle(Handle_Of_Thread_1);
	  //Handle_Of_Thread_1 = NULL;
  //}

#else
  //if (_liveview_thread)
  //  _liveview_thread->join();
#endif 

  cv::Mat* imgs = new cv::Mat[cam_count];
  
  for(int i=0;i<cam_count;i++) {
    int idx = _cams->GetCamera(i)->GetCurrentImage();
    if (idx < 0)
      idx = cam_count-1;
	std::cout << "Get Image: " << i << ::std::endl;
    imgs[i] = _cams->GetImageFromBuffer(i, idx);
	}
  
  clif::Mat imgs_mat(CvDepth2BaseType(imgs[0].depth()), {imgs[0].size().width, imgs[0].size().height, 1, cam_count});
  for(int i=0;i<cam_count;i++)
	imgs[i].copyTo(cvMat(imgs_mat.bind(3, i).bind(2, 0)));
  
  
  Datastore *store = out->data->getStore("calibration/extrinsics/default/data");
  store->cache_flush();
  store->write(imgs_mat);
}

component::~component()
{
  if (_cams)
    delete _cams;
}

//FIXME remove alias for replaced sub-component!
bool component::ParameterUpdating_(int index, const DspParameter& param)
{
  //just store parameter 
  SetParameter_(index, param);
  
  return true;      
}

EXPORT_DSPCOMPONENT(component)
