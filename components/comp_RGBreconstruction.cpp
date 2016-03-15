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

#include "clif/subset3d.hpp"
#include "clif/mat_helpers.hpp"
#include "openlf/types.hpp"
#include <opencv2/highgui/highgui.hpp>

#include "dspatch/DspPlugin.h"

using namespace clif;
using namespace vigra;
using namespace openlf;

class COMP_warpToRefView : public DspComponent {
public:
	COMP_warpToRefView();
	DSPCOMPONENT_TRIVIAL_CLONE(COMP_warpToRefView);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:
  virtual bool ParameterUpdating_ (int i, DspParameter const &p);
  LF _out;
  clif::Dataset _out_set;
};

COMP_warpToRefView::COMP_warpToRefView()
{
  setTypeName_("COMP_RGBrecon");
  AddInput_("input");
  AddOutput_("output");
  AddParameter_("in_group", DspParameter(DspParameter::ParamType::String, "warped"));
  AddParameter_("in_group", DspParameter(DspParameter::ParamType::String, "2DTV"));
  AddParameter_("out_group", DspParameter(DspParameter::ParamType::String, "RGBrecon"));
}

void COMP_warpToRefView::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
	//generate IOs
	LF *in = NULL;
	LF *out = NULL;

	// Check if inputs are connected
	errorCond(inputs.GetValue(0, in), "missing input"); RETURN_ON_ERROR

	//Link memory from input data to output
	out = &_out;
	out->data = &_out_set;
	out->data->memory_link(in->data);

	//connect ouput to module output
	outputs.SetValue(0, out);

	//Check if output exists
	errorCond(out, "output creation failed"); RETURN_ON_ERROR

	const std::string in_dataset_name = *GetParameter(0)->GetString();
	const std::string in2_dataset_name = *GetParameter(1)->GetString();
	const std::string out_dataset_name = *GetParameter(2)->GetString();


	//get location of disparity and coherence map
	cpath warped_root;
	try{
		warped_root = in->data->getSubGroup(in_dataset_name);
		std::cout << "Found warped results!" << std::endl;
	}
	catch (const std::exception& e){
		errorCond(false, "Dataset warped not found"); RETURN_ON_ERROR
	}

	cpath TV_root;
	try{
		TV_root = in->data->getSubGroup(in2_dataset_name);
		std::cout << "Found TV results!" << std::endl;
	}
	catch (const std::exception& e){
		errorCond(false, "Dataset TV not found"); RETURN_ON_ERROR
	}
	
	//define storages used for TV
	Datastore *TV_store = in->data->getStore(TV_root / "data");
	Datastore *warped_store = in->data->getStore(warped_root / "data");
	Datastore *lf_store = in->data->getStore(TV_root / "subset/source/data");

	//Set some output Metadata
	std::string tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/data");
	Datastore *store = out->data->addStore(tmp_dataset_name);
	out->path = tmp_dataset_name;

	//FIXME: Reference View is always the central view modify get_intensities function in clif
	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/subset/refView");
	int tmp;
	in->data->get(warped_root / "subset/refView", tmp);
	out->data->setAttribute(tmp_dataset_name, tmp);

	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/subset/source");
	out->data->addLink(tmp_dataset_name, "calibration/extrinsics/default");

	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/subset/in_data");
	out->data->addLink(tmp_dataset_name, TV_root);

	std::cout << "Size TV storage: " << TV_store->extent() << std::endl;
	std::cout << "Size warped storage: " << warped_store->extent() << std::endl;
	std::cout << "Size LF storage: " << lf_store->extent() << std::endl;


	if (configOnly())
		return;

//read TV result
	Mat_<float> TV;
	TV_store->read(TV);

//read warped result
	Mat_<float> warped;
	warped_store->read(warped);

//External Data
	cv::Mat XYZ2RGB = (cv::Mat_<float>(3, 3) << 3.2406, -1.5372, -0.4986, -0.9689, 1.8758, 0.0415, 0.0557, -0.2040, 1.0570);
	//X first, Y second and Z third.
	cv::Mat _M = (cv::Mat_<float>(3,11) <<  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, \
											1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, \
											1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);

	float gamma = 1;

//Result Storage
	Idx Resultsize = { TV_store->extent()[0], TV_store->extent()[1], 3, 1 };
	Mat *result_XYZ = new Mat(BaseType::FLOAT, Resultsize);		
	Mat *result_RGB = new Mat(BaseType::FLOAT, Resultsize);

	cv::Mat single_result_XYZ = cvMat(result_XYZ->bind(3, 0));
	cv::Mat single_result_RGB = cvMat(result_RGB->bind(3, 0));
	


	//First step is the reconstruction of the XYZ space
	for (int x = 0; x < single_result_XYZ.size[0]; x++) {
		for (int y = 0; y < single_result_XYZ.size[1]; y++) {
			for (int z = 0; z < _M.size[1]; z++) {
				single_result_XYZ.at<float>(x, y, 0) += _M.at<float>(0, z) * warped.at<float>(x, y, 0, 0);
				single_result_XYZ.at<float>(x, y, 1) += _M.at<float>(1, z) * warped.at<float>(x, y, 0, 0);
				single_result_XYZ.at<float>(x, y, 2) += _M.at<float>(2, z) * warped.at<float>(x, y, 0, 0);
			}
		}
	}

	//Convert to RGB and scale result between 0 and 1
	int maxValue = 10;
	for (int x = 0; x < single_result_XYZ.size[0]; x++) {
		for (int y = 0; y < single_result_XYZ.size[1]; y++) {
			for (int z = 0; z < 3; z++) {
				single_result_RGB.at<float>(x, y, 0) += XYZ2RGB.at<float>(0, z) * single_result_XYZ.at<float>(x, y, z);
				single_result_RGB.at<float>(x, y, 1) += XYZ2RGB.at<float>(1, z) * single_result_XYZ.at<float>(x, y, z);
				single_result_RGB.at<float>(x, y, 2) += XYZ2RGB.at<float>(2, z) * single_result_XYZ.at<float>(x, y, z);
				if (single_result_RGB.at<float>(x, y, 0) > maxValue) single_result_RGB.at<float>(x, y, 0) = maxValue;
				if (single_result_RGB.at<float>(x, y, 1) > maxValue) single_result_RGB.at<float>(x, y, 1) = maxValue;
				if (single_result_RGB.at<float>(x, y, 2) > maxValue) single_result_RGB.at<float>(x, y, 2) = maxValue;
			}
		}
	}


	//Apply gamma correction to normalized distribution
	for (int x = 0; x < single_result_XYZ.size[0]; x++) {
		for (int y = 0; y < single_result_XYZ.size[1]; y++) {
			if (single_result_RGB.at<float>(x, y, 0) < 0) single_result_RGB.at<float>(x, y, 0) = 0;
			if (single_result_RGB.at<float>(x, y, 1) < 0) single_result_RGB.at<float>(x, y, 1) = 0;
			if (single_result_RGB.at<float>(x, y, 2) < 0) single_result_RGB.at<float>(x, y, 2) = 0;
			single_result_RGB.at<float>(x, y, 0) = std::pow(single_result_RGB.at<float>(x, y, 0) / maxValue, gamma);
			single_result_RGB.at<float>(x, y, 1) = std::pow(single_result_RGB.at<float>(x, y, 1) / maxValue, gamma);
			single_result_RGB.at<float>(x, y, 2) = std::pow(single_result_RGB.at<float>(x, y, 2) / maxValue, gamma);
		}
	}


	//display

	bool display = true;
	if (display){
		cv::Mat displayMat = cv::Mat::zeros(TV_store->extent()[1], TV_store->extent()[0], CV_8UC3);
		//cv2ClifMat(&single_result_RGB, &displayMat);
		cv::namedWindow("RGB_recon", 0);
		cv::resizeWindow("RGB_recon", single_result_RGB.size[0] / 4, single_result_RGB.size[1] / 4);
		cv::imshow("RGB_recon", displayMat);
		cv::waitKey(1);
	}
}

bool COMP_warpToRefView::ParameterUpdating_(int i, DspParameter const &p)
{
  //we only have two parameters
  if (i >= 4)
    return false;
  
  if (p.Type() != DspParameter::ParamType::String)
    return false;
  
  SetParameter_(i, p);
  return true;
}

EXPORT_DSPCOMPONENT(COMP_warpToRefView)
