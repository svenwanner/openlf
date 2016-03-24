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
#include <vigra/convolution.hxx>
#include <vigra/multi_convolution.hxx>
#include "clif/subset3d.hpp"
#include "clif/mat_helpers.hpp"
#include "openlf/types.hpp"
#include <opencv2/highgui/highgui.hpp>

#include "dspatch/DspPlugin.h"
\

using namespace clif;
using namespace vigra;
using namespace openlf;

class COMP_2DTV : public DspComponent {
public:
	COMP_2DTV();
	DSPCOMPONENT_TRIVIAL_CLONE(COMP_2DTV);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:
  virtual bool ParameterUpdating_ (int i, DspParameter const &p);
  LF _out;
  clif::Dataset _out_set;
};

COMP_2DTV::COMP_2DTV()
{
  setTypeName_("COMP_2DTV");
  AddInput_("input");
  AddOutput_("ouput");
  AddParameter_("iterations", DspParameter(DspParameter::ParamType::Int, 1000));
  AddParameter_("tau", DspParameter(DspParameter::ParamType::Float, 0.012f));
  AddParameter_("sigma", DspParameter(DspParameter::ParamType::Float, 0.5f));
  AddParameter_("delta", DspParameter(DspParameter::ParamType::Float, 0.2f));
  AddParameter_("iota", DspParameter(DspParameter::ParamType::Float, 0.4f));
  AddParameter_("phi", DspParameter(DspParameter::ParamType::Float, 0.2f));
  AddParameter_("alpha", DspParameter(DspParameter::ParamType::Float, 0.22f));
  AddParameter_("alpha_edge", DspParameter(DspParameter::ParamType::Float, 0.0000000001f));
  AddParameter_("beta", DspParameter(DspParameter::ParamType::Float, 0.088f));
  AddParameter_("beta_edge", DspParameter(DspParameter::ParamType::Float, 0.0000000001f));
  AddParameter_("initialValue", DspParameter(DspParameter::ParamType::Float, 0.0f));
  AddParameter_("Display", DspParameter(DspParameter::ParamType::Int, 1));
  AddParameter_("TVposition", DspParameter(DspParameter::ParamType::Int, 0));
  AddParameter_("out_group", DspParameter(DspParameter::ParamType::String, "2DTV"));
  AddParameter_("in_group", DspParameter(DspParameter::ParamType::String, "merged"));
}

void COMP_2DTV::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
	//generate IOs
	LF *in = NULL;
	LF *out = NULL;

	// Check if inputs are connected
	errorCond(inputs.GetValue(0, in), "Dataset not found / missing input"); RETURN_ON_ERROR

	//Link memouy from input data to output
	out = &_out;
	out->data = &_out_set;
	out->data->memory_link(in->data);

	//connect ouput to module output
	outputs.SetValue(0, out);

	//Check if output exists
	errorCond(out, "output creation failed"); RETURN_ON_ERROR


	//Define some test parameter
	int TV_time_total = *GetParameter(0)->GetInt();																							//AddParameter_("iterations", DspParameter(DspParameter::ParamType::Int, 100));
	float tau = *GetParameter(1)->GetFloat();																								//AddParameter_("tau", DspParameter(DspParameter::ParamType::Float, 0.012f));
	float sigma = *GetParameter(2)->GetFloat();																								//AddParameter_("sigma", DspParameter(DspParameter::ParamType::Float, 0.5f));
	float delta = *GetParameter(3)->GetFloat();																								//AddParameter_("delta", DspParameter(DspParameter::ParamType::Float, 0.2f));
	float iota = *GetParameter(4)->GetFloat();																								//AddParameter_("iota", DspParameter(DspParameter::ParamType::Float, 0.4f));
	float phi = *GetParameter(5)->GetFloat();																								//AddParameter_("phi", DspParameter(DspParameter::ParamType::Float, 0.2f));
	float alpha = *GetParameter(6)->GetFloat();																								//AddParameter_("alpha", DspParameter(DspParameter::ParamType::Float, 0.22f));
	float alpha_edge = *GetParameter(7)->GetFloat();																						//AddParameter_("alpha_edge", DspParameter(DspParameter::ParamType::Float, 0.0000000001f));
	float beta = *GetParameter(8)->GetFloat();																								//AddParameter_("beta", DspParameter(DspParameter::ParamType::Float, 0.088f));
	float beta_edge = *GetParameter(9)->GetFloat();																							//AddParameter_("beta_edge", DspParameter(DspParameter::ParamType::Float, 0.0000000001f));
	float initialValue = *GetParameter(10)->GetFloat();																						//AddParameter_("initialValue", DspParameter(DspParameter::ParamType::Float, 0.0f));
	int display = *GetParameter(11)->GetInt();																								//AddParameter_("Display", DspParameter(DspParameter::ParamType::Int, 1));
	std::string out_dataset_name = *GetParameter(13)->GetString();																				//AddParameter_("out_dataset", DspParameter(DspParameter::ParamType::String, "2DTV"));
	std::string in_dataset_name = *GetParameter(14)->GetString();																				//AddParameter_("in_dataset", DspParameter(DspParameter::ParamType::String, "2DTV"));


	//get location of disparity and coherence map
	cpath disparity_root;
	try{
		disparity_root = in->data->getSubGroup(in_dataset_name);
		std::cout << "Found disparity results!" << std::endl;
	}
	catch (const std::exception& e){
		std::cout << "Disparity results not found!" << std::endl;
		errorCond(false, "Dataset not found"); RETURN_ON_ERROR
	}

	// Load Disparity store
	Datastore *disp_store = in->data->getStore(disparity_root / "data");
	errorCond(disp_store, "no disp_store available"); RETURN_ON_ERROR

	cpath tmp_data_root = disparity_root;
	cpath searchPath = tmp_data_root;
	bool breakCond = false;
	bool use_coherence = false;
	int timer = 0;

	while (breakCond == false){

		searchPath = tmp_data_root;
		searchPath /= "coherence";
		if (in->data->store(searchPath) != NULL)
		{
			std::cout << "Found Coherence!" << std::endl;
			std::cout << "Coherence path" << searchPath << std::endl;
			use_coherence = true;
			breakCond = true;
		}
		else
		{
			tmp_data_root /= "source";
			use_coherence = false;
			std::cout << "Search path" << tmp_data_root << std::endl;
		}

		timer++;
		if (timer == 10){
			breakCond = true;

		}
	}
	errorCond(use_coherence, "no coherence measure found"); RETURN_ON_ERROR

	Datastore *coh_store;
	try{
		coh_store = in->data->getStore(tmp_data_root / "coherence");
	}
	catch (const std::exception& e){
		errorCond(coh_store, "no coh_store available"); RETURN_ON_ERROR
	}

	// Load scaled Light Field
	float scale = 1.0;
	Attribute *attr;
	attr = in->data->get(tmp_data_root / "subset/scale");
	if (attr)  attr->get(scale);
	ProcData opts(UNDISTORT);
	opts.set_scale(scale);
	Subset3d subset(in->data, tmp_data_root / "source_LF", opts);

	Datastore *lf_store = in->data->getStore(tmp_data_root / "source_LF/data");
	errorCond(lf_store, "no lf_store available"); RETURN_ON_ERROR

	tmp_data_root = out_dataset_name;
	tmp_data_root /= "/default/subset/scale";
	out->data->setAttribute(tmp_data_root, scale);

	//std::cout << "lf_store Dims : " << subset.EPIWidth() << " " << subset.EPICount() << " " << subset.EPIHeight() << " " << subset.EPIDepth() << " " << std::endl;
	//std::cout << "coh_store Dims : " << coh_store->extent() << std::endl;
	//std::cout << "disp_store Dims : " << disp_store->extent() << std::endl;

	
	int TVposition = 0;
	try{
		in->data->get(tmp_data_root / "refView", TVposition);
		SetParameter_(12, DspParameter(DspParameter::ParamType::Int, TVposition));
	}
	catch (const std::exception& e) {
		SetParameter_(12, DspParameter(DspParameter::ParamType::Int, (subset.EPIHeight() - 1) / 2));
	}

	TVposition = *GetParameter(12)->GetInt();																							//AddParameter_("TVposition", DspParameter(DspParameter::ParamType::Int, 0));

	if (TVposition >= subset.EPIHeight() || TVposition < 0){
		TVposition = subset.EPIHeight() / 2;
	}
	
	//Set some Metadata
	std::string tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/refView");
	out->data->setAttribute(tmp_dataset_name, TVposition);

	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/source_LF");
	cpath tmp = disparity_root;
	tmp /= "/source_LF";
	out->data->addLink(tmp_dataset_name, tmp);

	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/source");
	out->data->addLink(tmp_dataset_name, disparity_root);

	//Initialize output store of module
	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/data");
	out->path = tmp_dataset_name;
	Datastore *store = out->data->addStore(tmp_dataset_name);


	// Check parameters only
	if (configOnly())
		return;

	/*****************************
	Finish initialization
	******************************
	Start Processing section
	******************************/

	// Load Light Field itself
	Mat_<float> lf;
	lf_store->read(lf, opts);
	// Load Coherence store
	Mat_<float> coh;
	coh_store->read(coh);
	// Load Disparity store
	Mat_<float> disp;
	disp_store->read(disp);


	Mat single_Image = lf.bind(3, TVposition);
	int refView = TVposition;

//FIXME Crashes if TVPos is larger than array
	//if (disp_store->extent()[3] < 2){
	//	refView = 0;
	//	SetParameter_(12, DspParameter(DspParameter::ParamType::Int, TVposition));
	//}	
	std::cout << disp_store->extent()[3] << " "<< refView << std::endl;

	std::cout << "TVposition reset to: " << refView << std::endl;

	//slice single disparity and coherence images as well as center view image to modify boundary movability


	cv::Mat single_dispMap = cvMat(disp.bind(3, refView).bind(2, 0));
	cv::Mat single_cohMap = cvMat(coh.bind(3, refView).bind(2, 0));

	//Generate result Storate of light field size and initialize it with a predefined starting value
	Idx size = { single_dispMap.size[1], single_dispMap.size[0] };
	Idx Resultsize = { single_dispMap.size[1], single_dispMap.size[0], 1, 1 };

	Mat *result = new Mat(BaseType::FLOAT, Resultsize);		cv::Mat single_result = cvMat(result->bind(3,0).bind(2,0));
	Mat *result_old = new Mat(BaseType::FLOAT, size);		cv::Mat single_result_old = cvMat(*result_old);
	Mat *result_tmp = new Mat(BaseType::FLOAT, size);		cv::Mat single_result_tmp = cvMat(*result_tmp);

	Mat *grad_tmp_x = new Mat(BaseType::FLOAT, size);		cv::Mat gradient_tmp_x = cvMat(*grad_tmp_x);
	Mat *grad_tmp_y = new Mat(BaseType::FLOAT, size);		cv::Mat gradient_tmp_y = cvMat(*grad_tmp_y);

	Mat *grad_x = new Mat(BaseType::FLOAT, size);			cv::Mat gradient_x = cvMat(*grad_x);
	Mat *grad_y = new Mat(BaseType::FLOAT, size);			cv::Mat gradient_y = cvMat(*grad_y);


	Mat *grad_tmp_xx = new Mat(BaseType::FLOAT, size);		cv::Mat gradient_tmp_xx = cvMat(*grad_tmp_xx);
	Mat *grad_tmp_yy = new Mat(BaseType::FLOAT, size);		cv::Mat gradient_tmp_yy = cvMat(*grad_tmp_yy);
	Mat *grad_tmp_dd = new Mat(BaseType::FLOAT, size);		cv::Mat gradient_tmp_dd = cvMat(*grad_tmp_dd);

	Mat *grad_xx = new Mat(BaseType::FLOAT, size);			cv::Mat gradient_xx = cvMat(*grad_xx);
	Mat *grad_yy = new Mat(BaseType::FLOAT, size);			cv::Mat gradient_yy = cvMat(*grad_yy);
	Mat *grad_dd = new Mat(BaseType::FLOAT, size);			cv::Mat gradient_dd = cvMat(*grad_dd);


	Mat *alpha_new_tmp = new Mat(BaseType::FLOAT, size);	cv::Mat alpha_new = cvMat(*alpha_new_tmp);
	Mat *beta_new_tmp = new Mat(BaseType::FLOAT, size);		cv::Mat beta_new = cvMat(*beta_new_tmp);


	Mat *displayTmp = new Mat(BaseType::FLOAT, size);		cv::Mat forDisplay = cvMat(*displayTmp);

	
	//derivative kernels for the first order regularization
	cv::Mat gradX = (cv::Mat_<float>(1, 3)   <<  0.0, 1.0, -1.0);
	cv::Mat gradX_T = (cv::Mat_<float>(1, 3) << -1.0, 1.0,  0.0);
	cv::Mat gradY = (cv::Mat_<float>(3, 1)   <<  0.0, 1.0,  -1.0);
	cv::Mat gradY_T = (cv::Mat_<float>(3, 1) << -1.0, 1.0, 0.0);
	// derivative kernels for the second order regularization
	cv::Mat Sec_gradX = (cv::Mat_<float>(1, 3) << 1.0, -2.0, 1.0);
	cv::Mat Sec_gradY = (cv::Mat_<float>(3, 1) << 1.0, -2.0, 1.0);
	cv::Mat Sec_gradD = (cv::Mat_<float>(3, 3) << 0.5, 0.0, -0.5, 0.0, 0.0, 0.0, -0.5, 0.0, 0.5);


/*********************************************************************************************************************************************************************************
**********************************************************************************************************************************************************************************
***  	FIXME:  edgeMap
**********************************************************************************************************************************************************************************
*********************************************************************************************************************************************************************************/
	/*float maxVal = 0;
	#pragma omp parallel for schedule(dynamic,1)
	for (int y = 0; y < single_result.size[0]; y++) {
		for (int x = 0; x < single_result.size[1]; x++) {
			edgeMap.at<float>(y, x) = (single_Image[x, y, 0] + single_Image[x, y, 1] + single_Image[x, y, 2]) /(float) 3.0;
			if (maxVal < edgeMap.at<float>(y, x)) maxVal = edgeMap.at<float>(y, x);
		}
	}

	Idx size2 = { single_dispMap.size[1], single_dispMap.size[0], 3};

	Mat *tmpImage = new Mat(BaseType::FLOAT, size2);
	cv::Mat tmpImage2 = cvMat(*tmpImage);
	cv::Mat tmpin = cvMat(single_Image);
	clifMat2cv(&tmpin, &tmpImage2);

	std::cout << tmpImage2.size() << std::endl;

	cv::namedWindow("EdgeMap", 0);
	cv::resizeWindow("EdgeMap", edgeMap.size[1] / 4, edgeMap.size[0] / 4);
	cv::imshow("EdgeMap", *tmpImage);
	cv::waitKey(0);


	cv::filter2D(edgeMap, edgeMap, -1, gradX, cv::Point(-1, -1), 0, cv::BORDER_REFLECT_101);
	cv::filter2D(edgeMap, edgeMap, -1, gradY, cv::Point(-1, -1), 0, cv::BORDER_REFLECT_101);
	maxVal=0;
	#pragma omp parallel for schedule(dynamic,1)
	for (int y = 0; y < single_result.size[0]; y++) {
		for (int x = 0; x < single_result.size[1]; x++) {
			edgeMap.at<float>(y, x) = std::sqrt((edgeMap.at<float>(y, x) * edgeMap.at<float>(y, x)) + (edgeMap.at<float>(y, x) * edgeMap.at<float>(y, x)));
			if (maxVal < edgeMap.at<float>(y, x)) maxVal = edgeMap.at<float>(y, x);
		}
	}
	#pragma omp parallel for schedule(dynamic,1)
	for (int y = 0; y < single_result.size[0]; y++) {
		for (int x = 0; x < single_result.size[1]; x++) {
			edgeMap.at<float>(y, x) = edgeMap.at<float>(y, x) / maxVal;
		}
	}
	*/

/*********************************************************************************************************************************************************************************
**********************************************************************************************************************************************************************************
*********************************************************************************************************************************************************************************/



/*********************************************************************************************************************************************************************************
**********************************************************************************************************************************************************************************
*** 	Initialize Arrays
**********************************************************************************************************************************************************************************
*********************************************************************************************************************************************************************************/
	float maxDispValue = 0;
	#pragma omp parallel for schedule(dynamic,1)
	for (int y = 0; y < single_result.size[0]; y++) {
		for (int x = 0; x < single_result.size[1]; x++) {
			single_result.at<float>(y, x) = initialValue;
			single_result_old.at<float>(y, x) = initialValue;
			single_result_tmp.at<float>(y, x) = initialValue;
			gradient_x.at<float>(y, x) = (float)0.0;
			gradient_y.at<float>(y, x) = (float)0.0;
			if (std::isnan(single_dispMap.at<float>(y, x))){
				single_dispMap.at<float>(y, x) = 0;
				single_cohMap.at<float>(y, x) = 0;
			}
			if (std::isnan(single_cohMap.at<float>(y, x))){
				single_dispMap.at<float>(y, x) = 0;
				single_cohMap.at<float>(y, x) = 0;
			}
			if (maxDispValue < single_dispMap.at<float>(y, x))
				maxDispValue = single_dispMap.at<float>(y, x);
		}
	}	


/*********************************************************************************************************************************************************************************
**********************************************************************************************************************************************************************************
*	Define Movability
**********************************************************************************************************************************************************************************
*********************************************************************************************************************************************************************************/

//FIXME: edgemap for normal TV, in heterogeneous light fields this is not necessary. Thus it is set to zero.
#pragma omp parallel for schedule(dynamic,1)
	for (int y = 0; y < single_result.size[0]; y++) {
		for (int x = 0; x < single_result.size[1]; x++) {
			alpha_new.at<float>(y, x) = ((alpha - alpha_edge) * (1 - 0)) + alpha_edge;
			beta_new.at<float>(y, x) = ((beta - beta_edge) * (1 - 0)) + beta_edge;
		}
	}


/*********************************************************************************************************************************************************************************
**********************************************************************************************************************************************************************************
*	Main Loop of 2DTV
**********************************************************************************************************************************************************************************
*********************************************************************************************************************************************************************************/
	
	/*************************************************************/
	// initialize display
	if (display){
		cv::namedWindow("TV_result", 0);
		int reduceSize = 1;
		if (single_result.size[0] > 1200 || single_result.size[1] > 1200) reduceSize = 4;
		cv::resizeWindow("MergeInput", single_result.size[1] / reduceSize, single_result.size[0] / reduceSize);
	}
	
	for (unsigned int time = 0; time < TV_time_total; time++)
	{

	/*************************************************************/
	// Primal part of regularization
		single_result.copyTo(single_result_old);
		
		#pragma omp parallel for schedule(dynamic,1)
		for (int y = 0; y < single_result.size[0]; y++) {
			for (int x = 0; x < single_result.size[1]; x++) {
				single_result.at<float>(y, x) = single_result.at<float>(y, x) - tau * single_cohMap.at<float>(y, x) * (single_result.at<float>(y, x) - single_dispMap.at<float>(y, x));
		}}
	
	/*************************************************************/
	// Dual part first order regularization	

		cv::filter2D(single_result_tmp, gradient_tmp_x, -1, gradX, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);
		cv::filter2D(single_result_tmp, gradient_tmp_y, -1, gradY, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);

		#pragma omp parallel for schedule(dynamic,1)
		for (int y = 0; y < single_result.size[0]; y++) {
			for (int x = 0; x < single_result.size[1]; x++) {

				gradient_x.at<float>(y, x) = gradient_x.at<float>(y, x) + sigma * gradient_tmp_x.at<float>(y, x);
				gradient_y.at<float>(y, x) = gradient_y.at<float>(y, x) + sigma * gradient_tmp_y.at<float>(y, x);

				gradient_x.at<float>(y, x) = (alpha_new.at<float>(y, x) / std::max(std::sqrt((gradient_x.at<float>(y, x) * gradient_x.at<float>(y, x)) + (gradient_y.at<float>(y, x) * gradient_y.at<float>(y, x))), alpha_new.at<float>(y, x)) ) * gradient_x.at<float>(y, x);
				gradient_y.at<float>(y, x) = (alpha_new.at<float>(y, x) / std::max(std::sqrt((gradient_x.at<float>(y, x) * gradient_x.at<float>(y, x)) + (gradient_y.at<float>(y, x) * gradient_y.at<float>(y, x))), alpha_new.at<float>(y, x)) ) * gradient_y.at<float>(y, x);
			}
		}
		
		cv::filter2D(gradient_x, gradient_tmp_x, -1, gradX_T, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);
		cv::filter2D(gradient_y, gradient_tmp_y, -1, gradY_T, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);

		#pragma omp parallel for schedule(dynamic,1)
		for (int y = 0; y < single_result.size[0]; y++) {
			for (int x = 0; x < single_result.size[1]; x++) {

				single_result.at<float>(y, x) = single_result.at<float>(y, x) - iota * (1 - single_cohMap.at<float>(y, x) * 0.99) * ((gradient_tmp_x.at<float>(y, x) + gradient_tmp_y.at<float>(y, x)) / (float)2.0);
			}
		}

	/*************************************************************/
	// Dual part second order regularization	

		cv::filter2D(single_result, gradient_tmp_xx, -1, Sec_gradX, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);
		cv::filter2D(single_result, gradient_tmp_yy, -1, Sec_gradY, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);
		cv::filter2D(single_result, gradient_tmp_dd, -1, Sec_gradD, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);

		#pragma omp parallel for schedule(dynamic,1)
		for (int y = 0; y < single_result.size[0]; y++) {
			for (int x = 0; x < single_result.size[1]; x++) {

				gradient_xx.at<float>(y, x) = gradient_xx.at<float>(y, x) + delta * gradient_tmp_xx.at<float>(y, x);
				gradient_yy.at<float>(y, x) = gradient_yy.at<float>(y, x) + delta * gradient_tmp_yy.at<float>(y, x);
				gradient_dd.at<float>(y, x) = gradient_dd.at<float>(y, x) + delta * gradient_tmp_dd.at<float>(y, x);

				gradient_xx.at<float>(y, x) = (beta_new.at<float>(y, x) / std::max(beta_new.at<float>(y, x), std::sqrt((gradient_xx.at<float>(y, x)*gradient_xx.at<float>(y, x)) + (gradient_yy.at<float>(y, x)*gradient_yy.at<float>(y, x)) + ((float)2.0 * gradient_dd.at<float>(y, x) * gradient_dd.at<float>(y, x)) ))) * gradient_xx.at<float>(y, x);
				gradient_yy.at<float>(y, x) = (beta_new.at<float>(y, x) / std::max(beta_new.at<float>(y, x), std::sqrt((gradient_xx.at<float>(y, x)*gradient_xx.at<float>(y, x)) + (gradient_yy.at<float>(y, x)*gradient_yy.at<float>(y, x)) + ((float)2.0 * gradient_dd.at<float>(y, x) * gradient_dd.at<float>(y, x)) ))) * gradient_yy.at<float>(y, x);
				gradient_dd.at<float>(y, x) = (beta_new.at<float>(y, x) / std::max(beta_new.at<float>(y, x), std::sqrt((gradient_xx.at<float>(y, x)*gradient_xx.at<float>(y, x)) + (gradient_yy.at<float>(y, x)*gradient_yy.at<float>(y, x)) + ((float)2.0 * gradient_dd.at<float>(y, x) * gradient_dd.at<float>(y, x)) ))) * gradient_dd.at<float>(y, x);

			}
		}

		cv::filter2D(gradient_xx, gradient_tmp_xx, -1, Sec_gradX, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);
		cv::filter2D(gradient_yy, gradient_tmp_yy, -1, Sec_gradY, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);
		cv::filter2D(gradient_dd, gradient_tmp_dd, -1, Sec_gradD, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);

		#pragma omp parallel for schedule(dynamic,1)
		for (int y = 0; y < single_result.size[0]; y++) {
			for (int x = 0; x < single_result.size[1]; x++) {
				single_result.at<float>(y, x) = single_result.at<float>(y, x) - phi * (1 - single_cohMap.at<float>(y, x) * 0.1) * (gradient_tmp_xx.at<float>(y, x) + gradient_tmp_yy.at<float>(y, x) + (float)2.0) * (gradient_tmp_dd.at<float>(y, x) / (float)4.0);
			}
		}


	/*************************************************************/
	// Extrapolation (Estimation of the next position to update the regularization) 
		#pragma omp parallel for schedule(dynamic,1)
		for (int y = 0; y < single_result.size[0]; y++) {
			for (int x = 0; x < single_result.size[1]; x++) {
				single_result_tmp.at<float>(y, x) = (float)2.5 * single_result.at<float>(y, x) - single_result_old.at<float>(y, x);
			}
		}



	/*************************************************************/
	// Display current result			
		if (display){
			#pragma omp parallel for schedule(dynamic,1)
			for (int y = 0; y < single_result.size[0]; y++) {
				for (int x = 0; x < single_result.size[1]; x++) {
					forDisplay.at<float>(y, x) = single_result.at<float>(y, x) / maxDispValue;
				}
			}
			cv::imshow("TV_result", forDisplay);
			cv::waitKey(1);
		}
		progress_((float)time / TV_time_total);

	}
	
/*************************************************************/
// save final result

  // save results
  store->write(result);
  
}

bool COMP_2DTV::ParameterUpdating_(int i, DspParameter const &p)
{
  //we have eleven parameters
  if (i >= 15)
    return false;
  // and we check if the types are matching
  else if (p.Type() != DspParameter::ParamType::Float && p.Type() != DspParameter::ParamType::Int && p.Type() != DspParameter::ParamType::String)
    return false;
  else{
	  SetParameter_(i, p);
	  return true;
  }
}

EXPORT_DSPCOMPONENT(COMP_2DTV)


