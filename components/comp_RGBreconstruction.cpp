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
	Datastore *lf_store = in->data->getStore(TV_root / "source_LF/data");

	//Set some output Metadata
	std::string tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/xyz");
	Datastore *store_xyz = out->data->addStore(tmp_dataset_name);
	out->path = tmp_dataset_name;

	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/data");
	Datastore *store_rgb = out->data->addStore(tmp_dataset_name);
	out->path = tmp_dataset_name;

	//FIXME: Reference View is always the central view modify get_intensities function in clif
	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/refView");
	int tmp;
	in->data->get(warped_root / "refView", tmp);
	out->data->setAttribute(tmp_dataset_name, tmp);

	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/source_LF");
	cpath tmpSource = warped_root;
	tmpSource.append("/source_LF");
	out->data->addLink(tmp_dataset_name, tmpSource);
	//out->data->addLink(tmp_dataset_name, "calibration/extrinsics/default");

	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/source");
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
	//For PCO DATASET
	//cv::Mat _M = (cv::Mat_<float>(3,21) <<  0.0466, 0.4376, -0.0073, 0.0389, 0.1881,  0.4412, 0.6265, 0.8842,    0.9900,  0.2659,  0.0158,    0.3166,  0.9811,     0.8447,  0.6334, 0.5044, 0.2094, 0.0084, 0.0090, 0.4149, -0.0042, \
											0.0016, 0.0681,  0.3226, 0.6270, 0.8864,    1.06, 0.9824, 0.6204,    0.5910,  0.1351, -0.0066,      0.08,  0.5614,     0.6326,  0.9678, 1.0370, 0.8759, 0.6175, 0.3497, 0.0187, -0.0238, \
											0.1297, 3.0483,  0.3217, 0.1255, 0.0172, -0.0077, 0.0067, 0.0074, -0.000404, -0.0099, -0.0099, -0.000404, -0.0073, 0.00076751, -0.0098, 0.0174, 0.039,  0.1031, 0.3277, 3.0421,  0.1564);
	//For Demonstrator Synthetic DATASET
	cv::Mat _M = (cv::Mat_<float>(3, 11) <<    0.1390, 0.1772,    0.2, 0.000663, 0.0841, 0.4215, 0.8421, 1.0618, 0.7489,  0.2686, 0.1419, \
											-0.000127, 0.0107, 0.0739,   0.3210, 0.7899,  0.995, 0.9154, 0.6252, 0.3047,  0.0978, 0.0061, \
											   0.6859, 0.8440, 1.3173,   0.2713, 0.0465,  0.006, 0.0018, 0.0008 ,0.0001, 0.00001, 0.7172);
	//For Heterogeneous light field array
	//cv::Mat _M = (cv::Mat_<float>(3, 11) <<  0.4505, 0.3875, 0.2730, 0.0042, 0.1780, 0.7205, 1.5813, 1.6807,  1.6010, 0.6885,   0.307, \
											 0.0171, 0.0372, 0.1431, 0.5333, 1.2180, 1.4932, 1.5406, 0.9461,  0.6894, 0.2598, 0.00977, \
											 2.2078, 1.9758, 2.0134, 0.4474, 0.0611, 0.0023, 0.0031, 0.0016, 0.00038,      0,       0);

	float gamma = 0.6;

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
				single_result_XYZ.at<float>(x, y, 0) += _M.at<float>(0, z) * warped.at<float>(x, y, 0, z);
				single_result_XYZ.at<float>(x, y, 1) += _M.at<float>(1, z) * warped.at<float>(x, y, 0, z);
				single_result_XYZ.at<float>(x, y, 2) += _M.at<float>(2, z) * warped.at<float>(x, y, 0, z);
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
	/*
	bool display = true;
	if (display){
		cv::Mat displayMat = cv::Mat::zeros(TV_store->extent()[1], TV_store->extent()[0], CV_8UC3);
		//cv2ClifMat(&single_result_RGB, &displayMat);
		cv::namedWindow("RGB_recon", 0);
		cv::resizeWindow("RGB_recon", single_result_RGB.size[0] / 4, single_result_RGB.size[1] / 4);
		cv::imshow("RGB_recon", displayMat);
		cv::waitKey(1);
	}
	*/

	store_rgb->write(result_RGB);
	store_xyz->write(result_XYZ);
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
