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
#include <cmath>

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
  LF _out_rgb;
  LF _out_xyz;
  clif::Dataset _out_set;
};

COMP_warpToRefView::COMP_warpToRefView()
{
  setTypeName_("COMP_spectral2RGB_XYZ");
  AddInput_("shifted");
  AddOutput_("xyz");
  AddOutput_("rgb");
  AddParameter_("rgb_name", DspParameter(DspParameter::ParamType::String, "RGBrecon"));
  AddParameter_("gamma", DspParameter(DspParameter::ParamType::Float, 0.5f));
}

void COMP_warpToRefView::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
	//generate IOs
	LF *in_shifted = NULL;
	LF *out_rgb = NULL;
	LF *out_xyz = NULL;

	// Check if inputs are connected
	errorCond(inputs.GetValue(0, in_shifted), "missing input"); RETURN_ON_ERROR

	//Link memory from input data to output
	out_rgb = &_out_rgb;
	out_rgb->data = &_out_set;
	out_rgb->data->memory_link(in_shifted->data);

	out_xyz = &_out_xyz;
	out_xyz->data = &_out_set;
	out_xyz->data->memory_link(in_shifted->data);

	//connect ouput to module output
	outputs.SetValue(0, out_rgb);
	outputs.SetValue(1, out_xyz);

	//Check if output exists
	errorCond(out_rgb, "output creation failed"); RETURN_ON_ERROR
	errorCond(out_xyz, "output creation failed"); RETURN_ON_ERROR

	if (configOnly())
		return;

	const std::string out_dataset_name = *GetParameter(0)->GetString();
	float gamma = *GetParameter(1)->GetFloat();

	//Set some output Metadata
	std::string tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/xyz");
	Datastore *store_xyz = out_xyz->data->addStore(tmp_dataset_name);
	out_xyz->path = tmp_dataset_name;

	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/rgb");
	Datastore *store_rgb = out_rgb->data->addStore(tmp_dataset_name);
	out_rgb->path = tmp_dataset_name;

	Datastore *warped_store = in_shifted->data->store(in_shifted->path);


//read warped result
	Mat_<uint16_t> warped;
	warped_store->read(warped);

//External Data
	cv::Mat XYZ2RGB = (cv::Mat_<float>(3, 3) << 3.2406, -1.5372, -0.4986, -0.9689, 1.8758, 0.0415, 0.0557, -0.2040, 1.0570);

//For PCO DATASET Pirate Worm Horse Butterfly
	cv::Mat _M = (cv::Mat_<float>(3, 21) <<  0.0368, 0.4677, -0.0043, 0.0297, 0.1804,  0.4501, 0.6272,  0.8639,  0.9826,  0.2641,  0.0164,  0.3290, 0.9895,  0.8679,  0.6320, 0.4999, 0.2312, 0.0185, 0.0085, 0.3797,  0.0062,\
											-0.0033, 0.0332,  0.3436, 0.5891, 0.8603,  1.0543, 0.9478,  0.5906,  0.5626,  0.1051, -0.0046,  0.1140, 0.5928,  0.6707,  0.9958, 1.0374, 0.9017, 0.6528, 0.3276, 0.0436, -0.0225, \
											 0.1441, 2.2404,  0.2925, 0.1245, 0.0288, -0.0009, 0.0075, -0.0002, -0.0060, -0.0041, -0.0111, -0.0027, 0.0015, -0.0055, -0.0101, 0.0131, 0.0351, 0.1134, 0.3608, 2.2894,  0.1417);
//Pirate
	cv::Mat exposure = (cv::Mat_<float>(1, 21) << 0.007, 0.007, 0.0010, 0.0011, 0.0013, 0.0020, 0.0020, 0.0033, 0.0033, 0.0040, 0.0050, 0.0040, 0.0033, 0.0033, 0.0020, 0.0020, 0.0013, 0.0011, 0.0010, 0.007, 0.007);

//For Heterogeneous light field array
	//cv::Mat _M = (cv::Mat_<float>(3, 11) <<  0.4505, 0.3875, 0.2730, 0.0042, 0.1780, 0.7205, 1.5813, 1.6807,  1.6010, 0.6885,   0.307, \
											 0.0171, 0.0372, 0.1431, 0.5333, 1.2180, 1.4932, 1.5406, 0.9461,  0.6894, 0.2598, 0.00977, \
											 2.2078, 1.9758, 2.0134, 0.4474, 0.0611, 0.0023, 0.0031, 0.0016, 0.00038,      0,       0);
// cv::Mat exposure = (cv::Mat_<float>(1, 11) << 320, 113, 80, 80, 80, 113, 160, 160, 320, 160, 320);
  /*std::vector<float> exposure(11);
  
  in->data->get("acquisition/exposure", exposure);*/

//Result Storage

	Idx Resultsize = { warped_store->extent()[0], warped_store->extent()[1], 3, 1 };
	Mat_<float> *result_XYZ = new Mat_<float>(BaseType::FLOAT, Resultsize);
	Mat_<float> *result_RGB = new Mat_<float>(BaseType::FLOAT, Resultsize);
	
	for (int x = 0; x < warped_store->extent()[0]; x++) {
		for (int y = 0; y < warped_store->extent()[1]; y++) {
			for (int z = 0; z < 3; z++) {
				result_XYZ->at<float>(x, y, z, 0) = 0;
				result_RGB->at(x, y, z, 0) = 0;
			}
		}
	}
	std::cout << warped_store->extent() << std::endl;

	//First step is the reconstruction of the XYZ space
	float maxValue = 0;
	for (int x = 0; x < warped_store->extent()[0]; x++) {
		for (int y = 0; y < warped_store->extent()[1]; y++) {
			for (int z = 0; z < warped_store->extent()[3]; z++) {
				result_XYZ->at<float>(x, y, 0, 0) = result_XYZ->at<float>(x, y, 0, 0) + (_M.at<float>(0, z) * (float)warped.at(x, y, 0, z) * exposure.at<float>(0, z));
				result_XYZ->at<float>(x, y, 1, 0) = result_XYZ->at<float>(x, y, 1, 0) + (_M.at<float>(1, z) * (float)warped.at(x, y, 0, z) * exposure.at<float>(0, z));
				result_XYZ->at<float>(x, y, 2, 0) = result_XYZ->at<float>(x, y, 2, 0) + (_M.at<float>(2, z) * (float)warped.at(x, y, 0, z) * exposure.at<float>(0, z));
					if (result_XYZ->at<float>(x, y, 0, 0) > maxValue) maxValue = result_XYZ->at<float>(x, y, 0, 0);
					if (result_XYZ->at<float>(x, y, 1, 0) > maxValue) maxValue = result_XYZ->at<float>(x, y, 1, 0);
					if (result_XYZ->at<float>(x, y, 2, 0) > maxValue) maxValue = result_XYZ->at<float>(x, y, 2, 0);
			}
		}
	}

	std::cout << "MaxValue of result_XYZ: " << maxValue << std::endl;
	
	for (int x = 0; x < warped_store->extent()[0]; x++) {
		for (int y = 0; y < warped_store->extent()[1]; y++) {
			result_XYZ->at<float>(x, y, 0, 0) = result_XYZ->at<float>(x, y, 0, 0) / maxValue;
			result_XYZ->at<float>(x, y, 1, 0) = result_XYZ->at<float>(x, y, 1, 0) / maxValue;
			result_XYZ->at<float>(x, y, 2, 0) = result_XYZ->at<float>(x, y, 2, 0) / maxValue;
		}
	}

	for (int z = 0; z < 3; z++) {
		std::cout << XYZ2RGB.at<float>(0, z) << std::endl;
	}
	for (int z = 0; z < 3; z++) {
		std::cout << XYZ2RGB.at<float>(1, z) << std::endl;
	}
	for (int z = 0; z < 3; z++) {
		std::cout << XYZ2RGB.at<float>(2, z) << std::endl;
	}

	//Convert to RGB and scale result between 0 and 1
	float maxValue0 = -4000000000.0f;
	float minValue0 = 4000000000.0f;
	for (int x = 0; x < warped_store->extent()[0]; x++) {
		for (int y = 0; y < warped_store->extent()[1]; y++) {
			for (int z = 0; z < 3; z++) {
				result_RGB->at(x, y, 0, 0) = result_RGB->at(x, y, 0, 0) + (XYZ2RGB.at<float>(0, z) * result_XYZ->at<float>(x, y, z, 0));
        //FIXME BAAAAD HACK :'-(
				//result_RGB->at(x, y, 0, 0) *= 0.4;
				result_RGB->at(x, y, 1, 0) = result_RGB->at(x, y, 1, 0) + (XYZ2RGB.at<float>(1, z) * result_XYZ->at<float>(x, y, z, 0));
				//result_RGB->at(x, y, 1, 0) *= 0.1;
				result_RGB->at(x, y, 2, 0) = result_RGB->at(x, y, 2, 0) + (XYZ2RGB.at<float>(2, z) * result_XYZ->at<float>(x, y, z, 0));
        //result_RGB->at(x, y, 2, 0) *= 0.1;
				if (result_RGB->at(x, y, 0, 0) > maxValue0) maxValue0 = result_RGB->at(x, y, 0, 0);
				if (result_RGB->at(x, y, 1, 0) > maxValue0) maxValue0 = result_RGB->at(x, y, 1, 0);
				if (result_RGB->at(x, y, 2, 0) > maxValue0) maxValue0 = result_RGB->at(x, y, 2, 0);
				if (result_RGB->at(x, y, 0, 0) < minValue0) minValue0 = result_RGB->at(x, y, 0, 0);
				if (result_RGB->at(x, y, 1, 0) < minValue0) minValue0 = result_RGB->at(x, y, 1, 0);
				if (result_RGB->at(x, y, 2, 0) < minValue0) minValue0 = result_RGB->at(x, y, 2, 0);
			}
		}
	}
	std::cout << "MaxValue0: " << maxValue0 << std::endl;
	std::cout << "minValue0: " << minValue0 << std::endl;

	//Apply gamma correction to normalized distribution
	for (int x = 0; x < warped_store->extent()[0]; x++) {
		for (int y = 0; y < warped_store->extent()[1]; y++) {
			if (result_RGB->at(x, y, 0, 0) < 0) result_RGB->at(x, y, 0, 0) = 0;
			if (result_RGB->at(x, y, 1, 0) < 0) result_RGB->at(x, y, 1, 0) = 0;
			if (result_RGB->at(x, y, 2, 0) < 0) result_RGB->at(x, y, 2, 0) = 0;
			result_RGB->at(x, y, 0, 0) = std::pow((result_RGB->at(x, y, 0, 0) / maxValue0), gamma);
			result_RGB->at(x, y, 1, 0) = std::pow((result_RGB->at(x, y, 1, 0) / maxValue0), gamma);
			result_RGB->at(x, y, 2, 0) = std::pow((result_RGB->at(x, y, 2, 0) / maxValue0), gamma);
		}
	}

	
	//display
	bool display = true;
	if (display){
		cv::Mat _tmp = cvMat(result_RGB->bind(3, 0));
		cv::Mat output;
		clifMat2cv(&_tmp, &output);
		cv::namedWindow("RGB_recon", 0);
		int reduceSize = 1;
		if (warped_store->extent()[1] > 1200 || warped_store->extent()[2] > 1200) reduceSize = 4;
		cv::resizeWindow("MergeInput", warped_store->extent()[2] / reduceSize, warped_store->extent()[1] / reduceSize);
		cv::cvtColor(output, output, CV_RGB2BGR);
		cv::normalize(output, output, 0, 1, cv::NORM_MINMAX);
		cv::imshow("RGB_recon", output);
		cv::waitKey(1);
	}
	
	store_rgb->write(result_RGB);
	store_xyz->write(result_XYZ);
}

bool COMP_warpToRefView::ParameterUpdating_(int i, DspParameter const &p)
{
  //we only have two parameters
  if (i >= 5)
    return false;
  
  if (p.Type() != DspParameter::ParamType::String && p.Type() != DspParameter::ParamType::Float)
    return false;
  
  SetParameter_(i, p);
  return true;
}

EXPORT_DSPCOMPONENT(COMP_warpToRefView)
