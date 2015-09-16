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

/* the structure tensor container */
struct ST
{
    vigra::MultiArray<2, float> xx;
    vigra::MultiArray<2, float> xy;
    vigra::MultiArray<2, float> yy;
    vigra::MultiArray<2, float> coherence;
    
};

/* the structure tensor container as a view*/
struct ST_view
{
    vigra::MultiArrayView<2, float> xx;
    vigra::MultiArrayView<2, float> xy;
    vigra::MultiArrayView<2, float> yy;
    vigra::MultiArrayView<2, float> coherence;
    
};

/* the structure tensor container for both directions*/
struct ST_hv {
    ST h;
    ST v;

};

/* the map of structure tensors */
typedef std::map <std::string, std::vector<OpenLF::operators::ST>> tensor_map;

/* the orientation container with the corresponding coherence */
struct orientation {
    array_2D ori;
    array_2D coh;

};

/* the vector of focuses for refocusing */
typedef std::vector<int> focuses;

class Structure_Tensor : public Operator_EPI {
public:
    Structure_Tensor(std::vector<std::string> inslots, std::vector<std::string> outslots) : Operator_EPI(inslots,outslots) {};
    virtual ~Structure_Tensor();

    //******************************************************
    //***** Gaussian smoothing 
    //******************************************************

    /* this function applies a gaussian smoothing directly to a channel and saves it in tmp_views[channel] */
    vigra::MultiArray<2, float> gaussian_smoothing(vigra::MultiArrayView<2, float> image, double scale_x, double scale_y);
    vigra::MultiArray<2, float> gaussian_smoothing(vigra::MultiArrayView<2, float> image, double scale_x);

    //*****************************************************
    //***** Scharr5x5 structure tensor
    //*****************************************************

    /* This function constructs a Scharr5x5 tensor from a source epi*/
    ST Scharr5x5_structure_tensor_from_source(vigra::MultiArrayView<2, float> & source, double scale);

    /* This function constructs a Scharr5x5 structure tensor on a single epi from the map of refocused epis, which is intintialized with the given focus. */
    ST Scharr5x5_structure_tensor(std::string channel, int epi, int focus, DIRECTION direction, double scale);
    
    //*****************************************************
    //***** vigra structure tensor
    //*****************************************************

    /* This function constructs a vigra structure tensor on a single epi from the map of refocused epis, which is intintialized with the given focus. */
    ST vigra_structure_tensor(std::string channel, int epi, int focus, DIRECTION direction, double inner_scale, double outer_scale, double scale=0.0);

    /* This function constructs a vigra structure tensor from a source epi */
    ST vigra_structure_tensor_from_source(vigra::MultiArrayView<2, float> & source, double inner_scale, double outer_scale, double scale);
    
    //*****************************************************
    //***** Scharr3x3 structure tensor
    //*****************************************************

    /* This function constructs a Scharr3x3 tensor from a source epi*/
    ST Scharr3x3_structure_tensor_from_source(vigra::MultiArrayView<2, float> & source, double scale);

    /* This function constructs a Scharr3x3 structure tensor on a single epi from the map of refocused epis, which is intintialized with the given focus. */
    ST Scharr3x3_structure_tensor(std::string channel, int epi, int focus, DIRECTION direction, double scale);

    //*****************************************************
    //***** orientation map
    //*****************************************************

    /* This function calculates the orientation from a given structure tensor ST. */
    array_2D orientation(ST tensor, std::string coherence = "None", double coh_threshold=0.5, double max_slope=1.2);

    /* This function calculates the focused orientation from a source epi */
    OpenLF::operators::orientation focused_orientation(view_2D & source, focuses f, double smoothing_scale, double inner_scale=0.6, double outer_scale=1.1, double max_slope=1.0, double coh_threshold=0.95, std::string st_type="vigra");

    //********************************************************
    //***** reconstruction of images from epis/orientations
    //********************************************************

    /* this function reconstructs lightfield images from epis (for testing) */
    std::vector<array_2D> images_from_epis(std::string channel, DIRECTION direction = HORIZONTAL);

    /* this function reconstructs lightfield images from orientations vector */
    std::vector<array_2D> images_from_orientations(std::string channel, DIRECTION direction = HORIZONTAL);

    /* this function reconstructs lightfield images from lightweight orientations vector */
    array_2D image_from_orientations_lightweight(int m, std::string channel, DIRECTION direction = HORIZONTAL);

    //********************************************************************
    //***** reconstruct depth field along a horizontal/vertical direction
    //********************************************************************

    /* This function reconstructs the depth field from the orientations vector. */
    std::vector<array_2D> reconstruct_depth(std::string channel, std::string method="vigra", std::string coherence="None", int focus=0, DIRECTION direction=HORIZONTAL, double inner_scale=0.6, double outer_scale=1.1, double smoothing_scale=1.1, double coh_threshold=0.95, double max_slope=1.0, focuses f= {0});

    /* This function reconstructs the depth field from the lightweight orientations vector  along a single direction. It returns a vector of images along the direction. */
    std::vector<array_2D> reconstruct_depth_lightweight(std::string channel, std::string method="vigra", std::string coherence="None", DIRECTION direction=HORIZONTAL, double inner_scale=0.6, double outer_scale=1.1, double smoothing_scale=1.1, double coh_threshold=0.95, double max_slope=1.0, focuses f= {0});

     /* This function reconstructs the depth field from the lightweight orientations vector along a single direction. It returns a single image at position (n,m). */
     array_2D reconstruct_depth_lightweight(std::string channel, int n, int m, std::string method="vigra", std::string coherence="None", DIRECTION direction=HORIZONTAL, double inner_scale=0.6, double outer_scale=1.1, double smoothing_scale=1.1, double coh_threshold=0.95, double max_slope=1.0, focuses f= {0});

    //********************************************************************
    //***** reconstruct depth field along both directions
    //********************************************************************

    /* This function reconstructs the depth field from the orientations vector along both directions. It returns a single image at middle position. */
    array_2D get_depth_image(std::string channel, std::string method="vigra", std::string coherence="None", int focus=0, double inner_scale=0.6, double outer_scale=1.1, double smoothing_scale=1.1, double coh_threshold=0.95, double max_slope=1.0, focuses f= {0});

    /* This function reconstructs the depth field from the lightweight orientations vector along both directions. It returns a single image at middle position. */
    array_2D get_depth_image_lightweight(std::string channel, std::string method="vigra", std::string coherence="None", double inner_scale=0.6, double outer_scale=1.1, double smoothing_scale=1.1, double coh_threshold=0.95, double max_slope=1.0, focuses f= {0});

    /* This function reconstructs the depth field from the lightweight orientations vector along both directions. It returns a single image at the position (n,m). */
    array_2D get_depth_image_lightweight(std::string channel, int n, int m, std::string method="vigra", std::string coherence="None", double inner_scale=0.6, double outer_scale=1.1, double smoothing_scale=1.1, double coh_threshold=0.95, double max_slope=1.0, focuses f= {0});

    void allocate() {};
    void precompute() {};
    void compute() {};
    void postcompute() {};

    /* stores structure tensors */
    tensor_map m_ST;
     
    /* stores horizontal orientations */
    epi_map orientations_horizontal;
    /* stores vertical orientations */
    epi_map orientations_vertical;
    
    /* stores selected horizontal orientations */
    epi_map orientations_horizontal_lightweight;
    /* stores selected vertical orientations */
    epi_map orientations_vertical_lightweight;
    
    /* stores hhorizontal coherences */
    epi_map coherences_horizontal;
    /* stores vertical coherences */
    epi_map coherences_vertical;

};

}}

#endif	/* STRUCTURE_TENSOR_HPP */
