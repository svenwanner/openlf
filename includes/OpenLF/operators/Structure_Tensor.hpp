/*
* Copyright (c) 2014 Sven Wanner
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
*/

#ifndef STRUCTURE_TENSOR_HPP
#define	STRUCTURE_TENSOR_HPP
#include "OpenLF/operators/Operator_EPI.hpp"

namespace OpenLF { 
    namespace operators { 
        //namespace ST_structs {

struct ST
{
    vigra::MultiArray<2, float> xx;
    vigra::MultiArray<2, float> xy;
    vigra::MultiArray<2, float> yy;
    vigra::MultiArray<2, float> coherence;
    
};

struct ST_hv {
    ST h;
    ST v;

};

typedef std::map <std::string, std::vector<OpenLF::operators::ST>> tensor_map;

struct orientation {
    array_2D ori;
    array_2D coh;

};

typedef std::vector<int> focuses;

class Structure_Tensor : public Operator_EPI {
public:
    Structure_Tensor(std::vector<std::string> inslots, std::vector<std::string> outslots) : Operator_EPI(inslots,outslots) {};
    virtual ~Structure_Tensor();

    vigra::MultiArray<2, float> gaussian_smoothing(vigra::MultiArrayView<2, float> image, double scale_x, double scale_y);
    vigra::MultiArray<2, float> gaussian_smoothing(vigra::MultiArrayView<2, float> image, double scale_x);
    ST Scharr5x5_structure_tensor_from_source(vigra::MultiArrayView<2, float> & source, double scale);

    ST Scharr5x5_structure_tensor(std::string channel, int epi, int focus, DIRECTION direction, double scale);
    //st vigra_structure_tensor(int focus, int epi, double inner_scale, double outer_scale);
    ST vigra_structure_tensor(std::string channel, int epi, int focus, DIRECTION direction, double inner_scale, double outer_scale, double scale=0.0);
    //OpenLF::operators::ST_structs::ST vigra_structure_tensor_from_source(vigra::MultiArrayView<2, float> & source, double inner_scale, double outer_scale);
    ST vigra_structure_tensor_from_source(vigra::MultiArrayView<2, float> & source, double inner_scale, double outer_scale, double scale);
    
    array_2D orientation(ST tensor, std::string coherence = "None", double coh_threshold=0.5, double max_slope=1.2);

    OpenLF::operators::orientation focused_orientation(view_2D & source, focuses f, double smoothing_scale, double inner_scale=0.6, double outer_scale=1.1, double max_slope=1.0, double coh_threshold=0.95, std::string st_type="vigra");

    std::vector<array_2D> reconstruct_depth(std::string channel, std::string method="vigra", std::string coherence="None", int focus=0, DIRECTION direction=HORIZONTAL, double inner_scale=0.6, double outer_scale=1.1, double smoothing_scale=1.1, double coh_threshold=0.95, double max_slope=1.0, focuses f= {-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10});

    std::vector<array_2D> images_from_epis(std::string channel, DIRECTION direction = HORIZONTAL);

    std::vector<array_2D> images_from_orientations(std::string channel, DIRECTION direction = HORIZONTAL);

    void allocate() {};
    void precompute() {};
    void compute() {};
    void postcompute() {};

//protected:
    //m_inner_scale = inslots[0];
    //m_outer_scale = inslots[1];
    //m_method = inslots[2];
    
    //std::map<std::string, MultiArray<2, TinyVector<float, 3> >> m_ST_threeband;
    //std::unique_ptr<MultiArray<2, TinyVector<float, 3>> m_ST_threeband_ptr;

    tensor_map m_ST;

    epi_map orientations_horizontal;
    epi_map orientations_vertical;
    epi_map coherences_horizontal;
    epi_map coherences_vertical;

};

}}

#endif	/* STRUCTURE_TENSOR_HPP */
