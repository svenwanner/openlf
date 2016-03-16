// Code to grab images from several SiSo framegrabber
// HCI 2013, W.Mischler
// wolfgang.mischler@iwr.uni-heidelberg.de

#include "clif/clif.hpp"
#include "clif/dataset.hpp"
#include "cliini.h"
#include <vector>
#include <iostream>
#include <conio.h> 
#include "cameraarray.h"
#include <thread>
#include <stdio.h>
#include <sys/stat.h>
#include <windows.h> <WINDOWS.H>
#include <strsafe.h> <STRSAFE.H>

#define BUF_SIZE 255

using namespace std;

char* WindowName = "ImageView";
//FIXME make path to needed files relative or embedd them in exe
const char* CameraConfig = "../../camconfig/basler_ace2500_8bit_runtime5_4.mcf";

inline bool file_exists(const std::string& name)
{
	struct stat st;
	return (stat(name.c_str(), &st) == 0);
}

struct ConsoleInput{
	int exposure;
	int framerate;
	std::string outputFile;
	std::string store;
};

cliini_opt opts[] = {
	{
		"help",
		0, //argcount
		0, //argcount
		CLIINI_NONE, //type
		0, //flags
		'h'
	},
	{
		"exposure",
		1, //argcount min
		1, //argcount max
		CLIINI_STRING, //type
		0, //flags
		'e',
		NULL,
		"             exposure value in [ms], e.g. 4500 "
	},
	{
		"framerate",
		1, //argcount min
		1, //argcount max
		CLIINI_STRING, //type
		0, //flags
		'f',
		NULL,
		"            framerate [Hz] for autotrigger, e.g.10 "
	},
	{
		"store",
		1, //argcount min
		1, //argcount max
		CLIINI_STRING, //type
		0, //flags
		's',
		NULL,
		"                define storeage of dataset inside of hdf5-file"
	},
	{
		"output",
		1, //argcount
		CLIINI_ARGCOUNT_ANY, //argcount
		CLIINI_STRING, //type
		0, //flags
		'o',
		NULL,
		"        output clif file, e.g foo.clif",
		"<file>"
	}
};

cliini_optgroup group = {
	opts,
	NULL,
	sizeof(opts) / sizeof(*opts),
	0,
	0
};

const int cam_count = 11;

DWORD WINAPI Thread_no_1(LPVOID lpParam)
{
	struct ConsoleInput Data;
	int     count = 0;
	HANDLE  hStdout = NULL;
	std::vector<float> exposures(cam_count);

	// Get Handle To screen.
	// Else how will we print?
	if ((hStdout = GetStdHandle(STD_OUTPUT_HANDLE))	== INVALID_HANDLE_VALUE)
		return 1;

	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	// Cast the parameter to the correct
	// data type passed by called i.e main() in our case.
	Data = *((struct ConsoleInput*)lpParam);
	
	//try
	//{
	bool found_exposures = false;
	if (boost::filesystem::exists("params.clif")) {
		clif::ClifFile p_file;
		p_file.open("params.clif", H5F_ACC_RDONLY);
		clif::Dataset *p_set;
		if (p_file.datasetCount()) {
			p_set = p_file.openDataset();
			found_exposures = true;
			p_set->get("acquisition/exposure", exposures);
			delete p_set;
		}
	}

	if (!found_exposures)
	{
		for (auto &e : exposures)
			e = Data.exposure;
	}

	// Print message using thread-safe functions.
	StringCchPrintf(msgBuf, BUF_SIZE, TEXT("  Framerate: %02d, \n  Exposure: %02d \n  Store: %s \n Output: %s"),Data.framerate,Data.exposure,Data.store.c_str(),Data.outputFile.c_str());
	StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
	WriteConsole(hStdout, msgBuf, cchStringSize, &dwChars, NULL);


	cv::Mat* im = new cv::Mat[cam_count];
	cv::Mat* views = new cv::Mat[cam_count];
	cv::Mat tmp;

	clif::ClifFile f_out;

	if (file_exists(Data.outputFile)) {
		f_out.open(Data.outputFile, H5F_ACC_RDWR);
	}
	else
		f_out.create(Data.outputFile);

	clif::Dataset *set;
	if (f_out.datasetCount()) {
		printf("INFO: appending to HDF5 DataSet %s\n", f_out.datasetList()[0].c_str());
		set = f_out.openDataset(0);
	}
	else {
		printf("INFO: creating new HDF5 DataSet %s\n", Data.outputFile.c_str());
		set = f_out.createDataset();
	}
	clif::Datastore *store = set->addStore(Data.store, 5);
	
	// load camerarray
	camerarray::CameraArray	cams(CameraConfig, cam_count, 3);//11Cams connected and No of Framegrabbers 
	cams.PrintConnectedCameras();
	cams.SetTriggerMode(1);
	cams.SetFramerate(Data.framerate);
	cams.Acquire();
		
		
	for(int i=0;i<cam_count;i++)
		cams.GetCamera(i)->SetExposureTime(exposures[i]);

	// set up window
	cv::namedWindow(WindowName, cv::WINDOW_NORMAL);
        cvGetManyViews(WindowName, cam_count, views, 1000, 1000);//11Cams connected
	clif::Idx pos(5);

	std::cout << "cams.GetNumberOfCameras(): " << cams.GetNumberOfCameras() << std::endl;
	int j = 0;
	bool outputSelection = true;

	while (true) {
		for (int i = 0; i < cams.GetNumberOfCameras(); i++) {
			int curIdx = cams.GetCamera(i)->GetCurrentImage()-1;
			if (curIdx < 0)
				curIdx = cams.GetNumberOfCameras();
			im[i] = cams.GetImageFromBuffer(i, curIdx);
		}
		char c = cv::waitKey(10);
		if (c == 'q')
			break;
		if (c == 'a'){
			cams.SetTriggerMode(0);
			cams.SetFramerate(Data.framerate);
		}
		if (c == 'm')
			cams.SetTriggerMode(1);

		if (c == 's'){
			printf("snap images "); fflush(NULL);
			for (int i = 0; i < cams.GetNumberOfCameras(); i++) {
				store->write(clif::Mat3d(im[i]), pos);
				//store->append(clif::Mat3d(cams.GetImageFromBuffer(i, 0)));
				pos[3]++;
				printf("."); fflush(NULL);
			}
			printf("done\n");
			pos[4]++;
			pos[3] = 0;
		}
        if (c == 'u'){
			j++;
			outputSelection = false;
			if (j >= cams.GetNumberOfCameras()) j = 0;
        }
		
		if (outputSelection) {
			if (c == 'e')
				for (auto &e : exposures)
					e *= sqrt(2);
			else if (c == 'w')
				for (auto &e : exposures)
					e /= sqrt(2);
			if (c == 'e' || c == 'w')
				for(int i=0;i<cam_count;i++)
					cams.GetCamera(i)->SetExposureTime(exposures[i]);
		}
		else {
			if (c == 'e')
				exposures[j] *= sqrt(2);
			else if (c == 'w')
				exposures[j]  /= sqrt(2);
			if (c == 'e' || c == 'w')
				cams.GetCamera(j)->SetExposureTime(exposures[j]);
		}

		if (c == 'l'){
			j--;
			outputSelection = false;
			if (j < 0) j = cams.GetNumberOfCameras();
		}
		if (c == 'r'){
			outputSelection = true;
		}

#pragma omp parallel for
		for (int i = 0; i < cams.GetNumberOfCameras(); i++) {
			cv::cvtColor(im[i], tmp, CV_GRAY2RGB);
			resize(tmp, views[i], views[i].size());
		}

		if (outputSelection){
			cvUpdateManyViews(WindowName);
		}
		else{
			cv::imshow(WindowName, im[j]);
		}
	}

	{
		clif::ClifFile p_file;
		if (boost::filesystem::exists("params.clif"))
			p_file.open("params.clif", H5F_ACC_RDWR);
		else
			p_file.create("params.clif");
		
		clif::Dataset *p_set = p_file.createDataset();
		set->setAttribute("acquisition/exposure", exposures);
		p_set->setAttribute("acquisition/exposure", exposures);
		p_set->writeAttributes();
		delete p_set;
		p_file.close();
	}

	// clean up 
	delete[] im;
	delete[] views;

	return 0;
}



int main(int argc, const char* argv[]) {

	int Data_Of_Thread_1 = 1;
	HANDLE Handle_Of_Thread_1 = 0;
	HANDLE Array_Of_Thread_Handles[1];

	cliini_args *args = cliini_parsopts(argc, argv, &group);
	cliini_arg *framerate = cliargs_get(args, "framerate");
	cliini_arg *output = cliargs_get(args, "output");
	cliini_arg *exposure = cliargs_get(args, "exposure");
	cliini_arg *store = cliargs_get(args, "store");

	if (!args || cliargs_get(args, "help\n") || (!output && !exposure && !framerate && !store) || !output) {
		cliini_help(&group);
		return 1;
	}
	ConsoleInput Inputlist;
	Inputlist.outputFile = cliarg_nth_str(output, 0);
	Inputlist.store = cliarg_nth_str(store, 0);
	Inputlist.exposure = std::stoi(cliarg_nth_str(exposure, 0));
	Inputlist.framerate = std::stoi(cliarg_nth_str(framerate, 0));

	// Create thread 1.
	Handle_Of_Thread_1 = CreateThread(NULL, 0, Thread_no_1, &Inputlist, 0, NULL);
	if (Handle_Of_Thread_1 == NULL)
		ExitProcess(Data_Of_Thread_1);

	Array_Of_Thread_Handles[0] = Handle_Of_Thread_1;

	// Wait until all threads have terminated.
	WaitForMultipleObjects(1, Array_Of_Thread_Handles, TRUE, INFINITE);

	std::cout << "All threads are executed and get close." << std::endl;

	CloseHandle(Handle_Of_Thread_1);

	return 0;
}
