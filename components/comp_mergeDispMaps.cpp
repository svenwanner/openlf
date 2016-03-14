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

class COMP_mergeDispMaps : public DspComponent {
public:
	COMP_mergeDispMaps();
	DSPCOMPONENT_TRIVIAL_CLONE(COMP_mergeDispMaps);
protected:
  virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
private:
  virtual bool ParameterUpdating_ (int i, DspParameter const &p);
  LF _out;
  clif::Dataset _out_set;
};

COMP_mergeDispMaps::COMP_mergeDispMaps()
{
  setTypeName_("COMP_mergeDispMaps");
  AddInput_("input");
  AddOutput_("ouput");
  AddParameter_("in_group", DspParameter(DspParameter::ParamType::String, "disparity"));
  AddParameter_("out_group", DspParameter(DspParameter::ParamType::String, "merged"));
}



void COMP_mergeDispMaps::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
	//generate IOs
	LF *in = NULL;
	LF *out = NULL;

	// Check if inputs are connected
	errorCond(inputs.GetValue(0, in), "missing input"); RETURN_ON_ERROR

	//Link memouy from input data to output
	out = &_out;
	out->data = &_out_set;
	out->data->memory_link(in->data);

	//connect ouput to module output
	outputs.SetValue(0, out);

	//Check if output exists
	errorCond(out, "output creation failed"); RETURN_ON_ERROR

	const std::string in_dataset_name = *GetParameter(0)->GetString();
	const std::string out_dataset_name = *GetParameter(1)->GetString();

	//get location of disparity and coherence map
	cpath disparity_root;
	try{
		disparity_root = in->data->getSubGroup(in_dataset_name);
		std::cout << "Found disparity results!" << std::endl;
	}
	catch (const std::exception& e){
		errorCond(false, "Dataset not found"); RETURN_ON_ERROR
	}

	//define storages used for merging
	Datastore *disparity_store = in->data->getStore(disparity_root / "data");
	Datastore *coherence_store = in->data->getStore(disparity_root / "coherence");

	//Set some output Metadata
	std::string tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/data");
	Datastore *store = out->data->addStore(tmp_dataset_name);
	out->path = tmp_dataset_name;

	//FIXME: Reference View is always the central view modify get_intensities function in clif
	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/subset/refView");
	out->data->setAttribute(tmp_dataset_name, (disparity_store->extent()[3] - 1) / 2);

	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/subset/source");
	//FIXME:Ask Hendrik how to get extrinsics_group() without subset;
	out->data->addLink(tmp_dataset_name, "calibration/extrinsics/default");

	tmp_dataset_name = out_dataset_name;
	tmp_dataset_name.append("/default/subset/in_data");
	out->data->addLink(tmp_dataset_name, disparity_root);

	if (configOnly())
		return;

	//read data result
	Mat_<float> disp;
	disparity_store->read(disp);

	Mat_<float> coh;
	coherence_store->read(coh);


	int refView = disparity_store->extent()[2] / 2;



	// Allocate memory for output images
	Idx Resultsize = { disparity_store->extent()[0], disparity_store->extent()[1], 1, 1 };
	Mat *result = new Mat(BaseType::FLOAT, Resultsize);
	Mat *coherence = new Mat(BaseType::FLOAT, Resultsize);
	cv::Mat single_result_disparity = cvMat(result->bind(3, 0).bind(2, 0));
	cv::Mat single_result_coherence = cvMat(coherence->bind(3, 0).bind(2, 0));
	cv::Mat single_input_disparity = cvMat(disp.bind(3, 0).bind(2, 0));


	//remove nan values from disp value
	int count = 0;
#pragma parallel for
	for (int y = 0; y < disparity_store->extent()[0]; y++) {
		for (int x = 0; x < disparity_store->extent()[1]; x++) {
			for (int z = 0; z < disparity_store->extent()[3]; z++) {
				if (std::isnan(disp.at<float>(y, x, z))){
					disp.at<float>(y, x, 0 ,z) = 0;
					coh.at<float>(y, x, 0, z) = 0;
					single_result_coherence.at<float>(x, y) = 0;
					single_result_disparity.at<float>(x, y) = 0;
				}
			}
		}
	}

	/*
	
	for (int y = 0; y < disparity_store->extent()[0]; y++) {
		for (int x = 0; x < 7; x++) {
			std::cout << single_input_disparity.at<float>(y, x) << std::endl;
		}
	}
	*/

	//Put here stuff to average channels

	std::cout << "Dims 0 : " << disparity_store->extent()[0] << std::endl;
	std::cout << "Dims 1 : " << disparity_store->extent()[1] << std::endl;
	std::cout << "Dims 2 : " << disparity_store->extent()[3] << std::endl;

	Shape3 disp_count;

	disp_count[0] = disparity_store->extent()[0];
	disp_count[1] = disparity_store->extent()[1];
	disp_count[2] = disparity_store->extent()[3];

	cv::namedWindow("MergeInput", 0);
	cv::resizeWindow("MergeInput", single_input_disparity.size[1] / 4, single_input_disparity.size[0] / 4);
	cv::imshow("MergeInput", single_input_disparity);
	cv::waitKey(1);

	//initialize regular grid
	std::vector<int> grid;
	std::vector<int> output;
	std::vector<int> CenterGrid;

	std::cout << "refView: " << refView << std::endl;

	for (int y = 0; y < disp_count[0]; y++){
		grid.push_back(y);
		output.push_back(0);												// Hier soll die Position gespeichert werden, wo der Disparitaetswert in die ReferenzView geschrieben werden soll "Initialisierung"
		CenterGrid.push_back(0);
	}
	std::cout << "grid: " << grid.size() << std::endl;
	std::cout << "output: " << output.size() << std::endl;
	std::cout << "CenterGrid: " << CenterGrid.size() << std::endl;

//loop over all EPI
	int Center = disp_count[2] / 2;
	int Shift = Center - refView;


	for (int x = 0; x < disp_count[1]; x++){
		//std::cout << "x : " << x << std::endl;
		// Loop over all EPI rows
		int z = 0;// for (int z = 0; z < disp_count[2]; z++)
		{
			//Loop over each pixel
			for (int y = 0; y < disp_count[0]; y++) {
				output[y] = grid[y] + disp.at<float>(y, x, 0, z)*(z - refView); // Definiere wo jeder Disparitaetswert in der Centerview abgebildt werden soll
				output[y] = std::round(output[y]);
			}
			//Check if interpolation positions are outside of the image border

			if (std::abs(z - refView) <= Center - std::abs(Shift)){
				for (int y = 0; y < disp_count[0]; y++){
					if (output[y] > (disp_count[0]-1) || output[y] < 0){
						output[y] = grid[y] -disp.at<float>(y, x, 0, z)*(z - refView);
					}
					output[y] = std::round(output[y]);
				}
			}
			else{
				for (int y = 0; y < disp_count[0]; y++){
					if (output[y] > (disp_count[0] - 1) || output[y] < 0){
						output[y] = grid[y] -disp.at<float>(y - 2 * Shift, x, 0, z)*(z - 2 * Shift - refView);
					}
					output[y] = std::round(output[y]);
				}
			}

			// Round to even pixel values NN and check that it remains in the borders
			for (int y = 0; y < disp_count[0]; y++) {
				CenterGrid[y] = std::round(output[y]);
				if (CenterGrid[y] >= disp_count[0]){
					CenterGrid[y] = disp_count[0] - 1;
					count++;
				}
				if (CenterGrid[y] < 0){
					CenterGrid[y] = 0;
					count++;
				}
			}

			
			//This is the final merging
			for (int y = 0; y < disp_count[0]; y++) {
				
				if (single_result_coherence.at<float>(x, CenterGrid[y]) < coh.at<float>(y, x, z)){
					if (single_result_disparity.at<float>(x, CenterGrid[y]) < disp.at<float>(y, x, z)){
						single_result_disparity.at<float>(x, CenterGrid[y]) = disp.at<float>(y, x, z);
						single_result_coherence.at<float>(x, CenterGrid[y]) = coh.at<float>(y, x, z) * (1 - std::abs(refView - z)*0.005);
					}
				}
			}
		}
	}


	cv::namedWindow("MergeResult", 0);
	cv::resizeWindow("MergeResult", single_result_disparity.size[1] / 4, single_result_disparity.size[0] / 4);
	cv::imshow("MergeResult", single_result_disparity);
	cv::waitKey(10);

	// This is to set nan values in the point clouds where the measurements are bad
#pragma parallel for
	for (int y = 0; y < disp_count[1]; y++) {
		for (int x = 0; x < disp_count[0]; x++) {
			if (single_result_disparity.at<float>(y, x) == 0){
				single_result_disparity.at<float>(y, x) = std::numeric_limits<float>::quiet_NaN();
				single_result_coherence.at<float>(y, x) = 0;
			}
		}
	}
	std::cout << "cout: " << count << std::endl;

	store->write(result);
  
}

bool COMP_mergeDispMaps::ParameterUpdating_(int i, DspParameter const &p)
{
  //we only have two parameters
  if (i >= 3)
    return false;
  
  if (p.Type() != DspParameter::ParamType::String)
    return false;
  
  SetParameter_(i, p);
  return true;
}

EXPORT_DSPCOMPONENT(COMP_mergeDispMaps)
