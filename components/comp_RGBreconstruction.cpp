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
  AddParameter_("in_group_warped", DspParameter(DspParameter::ParamType::String, "warped"));
  AddParameter_("in_group_TV", DspParameter(DspParameter::ParamType::String, "2DTV"));
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
		std::cout << "Found warped results: " << warped_root << std::endl;
	}
	catch (const std::exception& e){
		errorCond(false, "Dataset warped not found"); RETURN_ON_ERROR
	}

	
	//define storages used for TV
	Datastore *warped_store = in->data->getStore(warped_root / "data");
	Datastore *lf_store = in->data->getStore(warped_root / "source_LF/data");

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


	std::cout << "Size warped storage: " << warped_store->extent() << std::endl;
	std::cout << "Size LF storage: " << lf_store->extent() << std::endl;


	if (configOnly())
		return;

//read warped result
	Mat_<uint16_t> warped;
	warped_store->read(warped, ProcData(UNDISTORT));

//External Data
	cv::Mat XYZ2RGB = (cv::Mat_<float>(3, 3) << 3.2406, -1.5372, -0.4986, -0.9689, 1.8758, 0.0415, 0.0557, -0.2040, 1.0570);
	//X first, Y second and Z third.
	//For PCO DATASET Pirate Worm Horse Butterfly
	cv::Mat _M = (cv::Mat_<float>(3, 21) <<  0.0368, 0.4677, -0.0043, 0.0297, 0.1804,  0.4501, 0.6272,  0.8639,  0.9826,  0.2641,  0.0164,  0.3290, 0.9895,  0.8679,  0.6320, 0.4999, 0.2312, 0.0185, 0.0085, 0.3797,  0.0062,\
											-0.0033, 0.0332,  0.3436, 0.5891, 0.8603,  1.0543, 0.9478,  0.5906,  0.5626,  0.1051, -0.0046,  0.1140, 0.5928,  0.6707,  0.9958, 1.0374, 0.9017, 0.6528, 0.3276, 0.0436, -0.0225, \
											 0.1441, 2.2404,  0.2925, 0.1245, 0.0288, -0.0009, 0.0075, -0.0002, -0.0060, -0.0041, -0.0111, -0.0027, 0.0015, -0.0055, -0.0101, 0.0131, 0.0351, 0.1134, 0.3608, 2.2894,  0.1417);
	//Pirate
	cv::Mat exposure = (cv::Mat_<float>(1, 21) << 0.0007, 0.0007, 0.0010, 0.0011, 0.0013, 0.0020, 0.0020, 0.0033, 0.0033, 0.0040, 0.0050, 0.0040, 0.0033, 0.0033, 0.0020, 0.0020, 0.0013, 0.0011, 0.0010, 0.0007, 0.0007);
	//for (int z = 0; z < exposure.size[1]; z++) {
	//	exposure.at<float>(0, z) = exposure.at<float>(0, z) * 200;
	//	std::cout << exposure.at<float>(0, z) << std::endl;
	//}

	//For Demonstrator Synthetic DATASET
	//cv::Mat _M = (cv::Mat_<float>(3, 11) <<    0.1390, 0.1772,    0.2, 0.000663, 0.0841, 0.4215, 0.8421, 1.0618, 0.7489,  0.2686, 0.1419, \
											-0.000127, 0.0107, 0.0739,   0.3210, 0.7899,  0.995, 0.9154, 0.6252, 0.3047,  0.0978, 0.0061, \
											   0.6859, 0.8440, 1.3173,   0.2713, 0.0465,  0.006, 0.0018, 0.0008 ,0.0001, 0.00001, 0.7172);
	//For Heterogeneous light field array
	//cv::Mat _M = (cv::Mat_<float>(3, 11) <<  0.4505, 0.3875, 0.2730, 0.0042, 0.1780, 0.7205, 1.5813, 1.6807,  1.6010, 0.6885,   0.307, \
											 0.0171, 0.0372, 0.1431, 0.5333, 1.2180, 1.4932, 1.5406, 0.9461,  0.6894, 0.2598, 0.00977, \
											 2.2078, 1.9758, 2.0134, 0.4474, 0.0611, 0.0023, 0.0031, 0.0016, 0.00038,      0,       0);

	float gamma = 0.82;

//Result Storage
	Idx Resultsize = { lf_store->extent()[0], lf_store->extent()[1], 3, 1 };
	Mat_<float> *result_XYZ = new Mat_<float>(BaseType::FLOAT, Resultsize);
	Mat_<float> *result_RGB = new Mat_<float>(BaseType::FLOAT, Resultsize);

	
	for (int x = 0; x < lf_store->extent()[0]; x++) {
		for (int y = 0; y < lf_store->extent()[1]; y++) {
			for (int z = 0; z < 3; z++) {
				result_XYZ->at<float>(x, y, z, 0) = 0;
				result_RGB->at<float>(x, y, z, 0) = 0;
			}
		}
	}

	//std::cout << "Dim0: " << warped_store->extent()[0] << std::endl;
	//std::cout << "Dim1: " << warped_store->extent()[1] << std::endl;
	//std::cout << "Dim2: " << warped_store->extent()[3] << std::endl;

	float InputMaxValue = 0;
	for (int z = 0; z < warped_store->extent()[3]; z++) {
		for (int x = 0; x < warped_store->extent()[0]; x++) {
				for (int y = 0; y < warped_store->extent()[1]; y++) {
					warped(x, y, 0, z) = warped(x, y, 0, z)	* exposure.at<float>(0, z);
					if (InputMaxValue < warped(x, y, 0, z)) InputMaxValue = warped(x, y, 0, z);
			}
		}
	}
	std::cout << "InputMaxValue: " << InputMaxValue << std::endl;

	//Mat single_result_XYZ = result_XYZ->bind(3, 0);
	//Mat single_result_RGB = result_RGB->bind(3, 0);

	//std::cout << "single_result_XYZ storage: " << single_result_XYZ.size() << std::endl;
	//std::cout << "single_result_RGB storage: " << single_result_RGB.size() << std::endl;
	
	//for (int z = 0; z < _M.size[1]; z++) {
	//	std::cout << _M.at<float>(0, z)  << std::endl;
	//}

	//for (int x = 0; x < _M.size[1]; x++) {
	//	cv::Mat tmpImage = cvMat(warped.bind(3, x).bind(2, 0));
	//	std::cout << tmpImage.size() << std::endl;
	//	cv::namedWindow("warped", 0);
	//	cv::imshow("warped", tmpImage);
	//	cv::waitKey(30);
	//}

	//First step is the reconstruction of the XYZ space
	float maxValue = 0;
	for (int x = 0; x < lf_store->extent()[0]; x++) {
		for (int y = 0; y < lf_store->extent()[1]; y++) {
			for (int z = 0; z < _M.size[1]; z++) {
					result_XYZ->at<float>(x, y, 0, 0) = result_XYZ->at<float>(x, y, 0, 0) + (_M.at<float>(0, z) * (float)warped.at<float>(x, y, 0, z) );
					result_XYZ->at<float>(x, y, 1, 0) = result_XYZ->at<float>(x, y, 1, 0) + (_M.at<float>(1, z) * (float)warped.at<float>(x, y, 0, z) );
					result_XYZ->at<float>(x, y, 2, 0) = result_XYZ->at<float>(x, y, 2, 0) + (_M.at<float>(2, z) * (float)warped.at<float>(x, y, 0, z) );
					if (result_XYZ->at<float>(x, y, 0, 0) > maxValue) maxValue = result_XYZ->at<float>(x, y, 0, 0);
					if (result_XYZ->at<float>(x, y, 1, 0) > maxValue) maxValue = result_XYZ->at<float>(x, y, 1, 0);
					if (result_XYZ->at<float>(x, y, 2, 0) > maxValue) maxValue = result_XYZ->at<float>(x, y, 2, 0);
			}
		}
	}

	std::cout << "MaxValue of result_XYZ: " << maxValue << std::endl;

	for (int x = 0; x < lf_store->extent()[0]; x++) {
		for (int y = 0; y < lf_store->extent()[1]; y++) {
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
	float maxValue0 = 0;
	float minValue0 = 10;
	for (int x = 0; x < lf_store->extent()[0]; x++) {
		for (int y = 0; y < lf_store->extent()[1]; y++) {
			for (int z = 0; z < 3; z++) {
				result_RGB->at<float>(x, y, 0, 0) = result_RGB->at<float>(x, y, 0, 0) + (XYZ2RGB.at<float>(0, z) * result_XYZ->at<float>(x, y, z, 0));
				result_RGB->at<float>(x, y, 1, 0) = result_RGB->at<float>(x, y, 1, 0) + (XYZ2RGB.at<float>(1, z) * result_XYZ->at<float>(x, y, z, 0));
				result_RGB->at<float>(x, y, 2, 0) = result_RGB->at<float>(x, y, 2, 0) + (XYZ2RGB.at<float>(2, z) * result_XYZ->at<float>(x, y, z, 0));
				if (result_RGB->at<float>(x, y, 0, 0) > maxValue0) maxValue0 = result_RGB->at<float>(x, y, 0, 0);
				if (result_RGB->at<float>(x, y, 1, 0) > maxValue0) maxValue0 = result_RGB->at<float>(x, y, 1, 0);
				if (result_RGB->at<float>(x, y, 2, 0) > maxValue0) maxValue0 = result_RGB->at<float>(x, y, 2, 0);
				if (result_RGB->at<float>(x, y, 0, 0) < minValue0) minValue0 = result_RGB->at<float>(x, y, 0, 0);
				if (result_RGB->at<float>(x, y, 1, 0) < minValue0) minValue0 = result_RGB->at<float>(x, y, 1, 0);
				if (result_RGB->at<float>(x, y, 2, 0) < minValue0) minValue0 = result_RGB->at<float>(x, y, 2, 0);
			}
		}
	}
	std::cout << "MaxValue0: " << maxValue0 << std::endl;
	std::cout << "minValue0: " << minValue0 << std::endl;

	//Apply gamma correction to normalized distribution
	for (int x = 0; x < lf_store->extent()[0]; x++) {
		for (int y = 0; y < lf_store->extent()[1]; y++) {
			if (result_RGB->at<float>(x, y, 0, 0) < 0) result_RGB->at<float>(x, y, 0, 0) = 0;
			if (result_RGB->at<float>(x, y, 1, 0) < 0) result_RGB->at<float>(x, y, 1, 0) = 0;
			if (result_RGB->at<float>(x, y, 2, 0) < 0) result_RGB->at<float>(x, y, 2, 0) = 0;
			result_RGB->at<float>(x, y, 0, 0) = std::pow(result_RGB->at<float>(x, y, 0, 0) / maxValue, gamma);
			result_RGB->at<float>(x, y, 1, 0) = std::pow(result_RGB->at<float>(x, y, 1, 0) / maxValue, gamma);
			result_RGB->at<float>(x, y, 2, 0) = std::pow(result_RGB->at<float>(x, y, 2, 0) / maxValue, gamma);
		}
	}

	
	//display
	for (int x = 0; x < lf_store->extent()[0]; x++) {
		for (int y = 0; y < lf_store->extent()[1]; y++) {
			result_RGB->at<float>(x, y, 0, 0) *= (255);
			result_RGB->at<float>(x, y, 1, 0) *= (255);
			result_RGB->at<float>(x, y, 2, 0) *= (255);
		}
	}

	bool display = true;
	if (display){
		cv::Mat _tmp = cvMat(result_RGB->bind(3, 0));
		cv::Mat output;
		clifMat2cv(&_tmp, &output);
		cv::namedWindow("RGB_recon", 0);
		cv::cvtColor(output, output, CV_RGB2BGR);
		cv::imshow("RGB_recon", output);
		cv::waitKey(0);
	}
	

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
