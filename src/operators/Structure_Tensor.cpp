/* 
 * File:   Structure_Tensor.cpp
 * Author: swanner
 * 
 * Created on May 15, 2014, 2:03 PM
 */

#include "OpenLF/operators/Structure_Tensor.hpp"
using namespace vigra::multi_math;

OpenLF::operators::Structure_Tensor::~Structure_Tensor() {
    
}

/* this function applies a gaussian smoothing directly to a channel and saves it in tmp_views[channel] */
vigra::MultiArray<2, float> OpenLF::operators::Structure_Tensor::gaussian_smoothing(vigra::MultiArrayView<2, float> image, double scale_x, double scale_y) {

    //m_tmp_views[channel] = vigra::MultiArray<2, float>(image_ptr(channel)->shape(),0.0);
    vigra::MultiArray<2, float> result(image.shape(),0.0);
    vigra::gaussianSmoothing(image, result, scale_x, scale_y);
    return result;
    
}

/* this function applies a gaussian smoothing directly to a channel and saves it in tmp_views[channel] */
vigra::MultiArray<2, float> OpenLF::operators::Structure_Tensor::gaussian_smoothing(vigra::MultiArrayView<2, float> image, double scale_x) {

    //m_tmp_views[channel] = vigra::MultiArray<2, float>(image_ptr(channel)->shape(),0.0);
    vigra::MultiArray<2, float> result(image.shape(),0.0);
    vigra::gaussianSmoothing(image, result, scale_x);
    return result;
}


/* This function constructs a vigra structure tensor only on a r+g+b or bw epi from the map of refocused epis, which is intintialized with the given focus. */
/*
OpenLF::operators::Structure_Tensor::ST OpenLF::operators::Structure_Tensor::vigra_structure_tensor(int focus, int epi, double inner_scale, double outer_scale) {

    // create a grayscale image to operate on 
    if (lf->hasRGB()) {
    // refocus 
    if (focus != get_focus("r")) {
        refocus(focus, "r");
    }
    if (focus != get_focus("g")) {
        refocus(focus, "g");
    }
    if (focus != get_focus("b")) {
        refocus(focus, "b");
    }
    vigra::MultiArray<2, float> rgb_h, rgb_v;

    rgb_h = 0.3f * m_horizontal_refocused["r"][epi] + 
            0.59f * m_horizontal_refocused["g"][epi] + 
            0.11f * m_horizontal_refocused["b"][epi];

    rgb_v = 0.3f * m_vertical_refocused["r"][epi] +    
            0.59f * m_vertical_refocused["g"][epi] + 
            0.11f * m_vertical_refocused["b"][epi];

    OpenLF::operators::Structure_Tensor::ST st;
    st.h = vigra_structure_tensor_from_source(rgb_h, inner_scale, outer_scale);
    st.v = vigra_structure_tensor_from_source(rgb_v, inner_scale, outer_scale);
    }

    else if(lf->hasBW()) {
        if (focus != get_focus("bw")) {
            refocus(focus, "bw");
        }

        OpenLF::operators::Structure_Tensor::ST st;
        st.h = vigra_structure_tensor_from_source(m_horizontal_refocused["bw"], inner_scale, outer_scale);
        st.v = vigra_structure_tensor_from_source(m_vertical_refocused["bw"], inner_scale, outer_scale);
    }
    return ST;

    else {
       throw OpenLF_Exception("OpenLF::operators::Structure_Tensor::vigra_structure_tensor() : Channels unsupported!");
    }  
}
*/


/* This function constructs a vigra structure tensor on a single epi from the map of refocused epis, which is intintialized with the given focus. */

OpenLF::operators::ST OpenLF::operators::Structure_Tensor::vigra_structure_tensor(std::string channel, int epi, int focus, DIRECTION direction, double inner_scale, double outer_scale, double scale) {
    //check channel
    if (!lf->hasChannel(channel)) {
        throw OpenLF_Exception("OpenLF::operators::Structure_Tensor::vigra_structure_tensor : Channel doesn't exist!");
    } 

    //TODO: check epi

    if (focus != get_focus(channel) && focus != 0) {
        refocus(focus, channel);
    }

    OpenLF::operators::ST tensor;

    if (direction == HORIZONTAL) {
        //check epi
        if (epi > lf->height()) {
            throw OpenLF_Exception("OpenLF::operators::Structure_Tensor::vigra_structure_tensor : epi out of range!");
        }
        if (focus==0) {
            tensor = OpenLF::operators::Structure_Tensor::vigra_structure_tensor_from_source(m_horizontal_epis[channel][epi],inner_scale, outer_scale, scale);
        }
        else {
            tensor = OpenLF::operators::Structure_Tensor::vigra_structure_tensor_from_source(m_horizontal_refocused[channel][epi],inner_scale, outer_scale, scale);
        }
    }
    if (direction == VERTICAL) {
        //check epi
        if (epi > lf->width()) {
            throw OpenLF_Exception("OpenLF::operators::Structure_Tensor::vigra_structure_tensor : epi out of range!");
        }
        if (focus==0) {
            tensor = OpenLF::operators::Structure_Tensor::vigra_structure_tensor_from_source(m_vertical_epis[channel][epi],inner_scale, outer_scale, scale);
        } 
        else {
            tensor = OpenLF::operators::Structure_Tensor::vigra_structure_tensor_from_source(m_vertical_refocused[channel][epi],inner_scale, outer_scale, scale);
        }
    }

    return tensor;
}

/* This function constructs a vigra structure tensor from a source epi */
OpenLF::operators::ST OpenLF::operators::Structure_Tensor::vigra_structure_tensor_from_source(vigra::MultiArrayView<2, float> & source, double inner_scale, double outer_scale, double scale) {

    vigra::Shape2 shape = source.shape();
    vigra::MultiArray<2, float> stxx(shape), stxy(shape), styy(shape);
    vigra::structureTensor(source, stxx, stxy, styy, inner_scale, outer_scale);
    OpenLF::operators::ST st;
    st.xx = stxx;
    st.xy = stxy;
    st.yy = styy;

    vigra::gaussianSmoothing(st.xx, st.xx, scale);
    vigra::gaussianSmoothing(st.xy, st.xy, scale);
    vigra::gaussianSmoothing(st.yy, st.yy, scale);

    vigra::MultiArray<2, float> up(source.shape());
    vigra::MultiArray<2, float> down(source.shape());

    up = sqrt(pow(st.yy-st.xx, 2.0) + pow(4*st.xy,2.0));
    down = st.yy+st.xx;

    #pragma omp parallel for
    for(auto it = down.begin(); it<down.end(); it++) {
        if(*it < pow(1.0,-9)) {
            *it = 1.0;
        }
    }
    vigra::MultiArray<2, float> coherence(source.shape());
    st.coherence = up/down;

    return st;
}

/* This function constructs a Scharr5x5 tensor from a source epi*/
OpenLF::operators::ST OpenLF::operators::Structure_Tensor::Scharr5x5_structure_tensor_from_source(vigra::MultiArrayView<2, float> & source, double scale) {
    vigra::Kernel2D<float> scharr_x;
    vigra::Kernel2D<float> scharr_y;
    scharr_x.initExplicitly(vigra::Diff2D(-2,-2), vigra::Diff2D(2,2)) =
    -1.0, -1.0, 0.0, 1.0, 1.0,
    -2.0, -2.0, 0.0, 2.0, 2.0,
    -3.0, -6.0, 0.0, 6.0, 3.0, 
    -2.0, -2.0, 0.0, 2.0, 2.0,
    -1.0, -1.0, 0.0, 1.0, 1.0;

    //scharr.normalize(); //to one

    scharr_y.initExplicitly(vigra::Diff2D(-2,-2), vigra::Diff2D(2,2)) =
    -1, -2, -3, -2, -1,
    -1, -2, -6, -2, -1,
    0, 0, 0, 0, 0,
    1, 2, 6, 2, 1,
    1, 2, 3, 2, 1;

    float norm = 42.0/60.0;
    scharr_x.normalize(norm);
    scharr_y.normalize(norm);

    vigra::MultiArray<2, float> destination_x(source.shape());
    vigra::MultiArray<2, float> destination_y(source.shape());
    vigra::convolveImage(source, destination_x,scharr_x);
    vigra::convolveImage(source, destination_y,scharr_y);

    OpenLF::operators::ST st;

    st.xx = destination_x*destination_x; //careful, this is not Python
    st.xy = destination_x*destination_y;
    st.yy = destination_y*destination_y;

    vigra::gaussianSmoothing(st.xx, st.xx, scale);
    vigra::gaussianSmoothing(st.xy, st.xy, scale);
    vigra::gaussianSmoothing(st.yy, st.yy, scale);

    vigra::MultiArray<2, float> up(source.shape());
    vigra::MultiArray<2, float> down(source.shape());

    up = sqrt(pow(st.yy-st.xx, 2.0) + (4*st.xy,2.0));
    down = st.yy+st.xx;

    #pragma omp parallel for
    for(auto it = down.begin(); it<down.end(); it++) {
        if(*it < pow(1.0,-9)) {
            *it = 1.0;
        }
    }
    vigra::MultiArray<2, float> coherence(source.shape());
    st.coherence = up/down;
   
    return st;
    
}

OpenLF::operators::ST OpenLF::operators::Structure_Tensor::Scharr5x5_structure_tensor(std::string channel, int epi, int focus, DIRECTION direction, double scale) {
    if (!lf->hasChannel(channel)) {
        throw OpenLF_Exception("OpenLF::operators::Structure_Tensor::Scharr5x5_structure_tensor : Channel doesn't exist!");
    } 

    //TODO: check epi

    if (focus != get_focus(channel)) {
    refocus(focus, channel);
    }

    OpenLF::operators::ST st;

    if (direction == HORIZONTAL) {
        //check epi
        if (epi > lf->width()) {
            throw OpenLF_Exception("OpenLF::operators::Structure_Tensor:Scharr5x5_structure_tensor : epi out of range!");
        }
        st = OpenLF::operators::Structure_Tensor::Scharr5x5_structure_tensor_from_source(m_horizontal_refocused[channel][epi], scale); 
    }
    if (direction == VERTICAL) {
        //check epi
        if (epi > lf->height()) {
            throw OpenLF_Exception("OpenLF::operators::Structure_Tensor::Scharr5x5_structure_tensor : epi out of range!");
        }
        st = OpenLF::operators::Structure_Tensor::Scharr5x5_structure_tensor_from_source(m_vertical_refocused[channel][epi], scale);
    }
    return st;  
}

vigra::MultiArray<2, float> OpenLF::operators::Structure_Tensor::orientation(ST tensor, std::string coherence, double coh_threshold, double max_slope) {

    vigra::MultiArray<2, float> slope(tensor.xx.shape());
    slope = atan2(2.0*tensor.xy, tensor.yy-tensor.xx) / 2.0;
    slope = tan(slope);
    if (coherence != "None" && coh_threshold > 0.0 && max_slope > 0.0) {
        auto it1 = slope.begin();
        auto it2 = tensor.coherence.begin();
        while(it1 < slope.end()) {
            if(*it1 > max_slope || *it1 < -max_slope) {
                *it1 = -max_slope;
                *it2 = 0.0;
            }
            it1++;
            it2++;
        }
        auto it3 = tensor.coherence.begin();
        auto it4 = slope.begin();
        while(it3 < tensor.coherence.end()) {
            if (*it3 < coh_threshold) {
                *it3 = 0.0;
                *it4 = -max_slope;
            }
            it3++;
            it4++;
        }
    }
    return slope;

}
OpenLF::operators::orientation OpenLF::operators::Structure_Tensor::focused_orientation(view_2D & source, focuses f, double smoothing_scale, double inner_scale, double outer_scale, double max_slope, double coh_threshold, std::string st_type) {
    
    OpenLF::operators::ST st;
    std::vector<array_2D> slopes;
    std::vector<array_2D> coherences;
    
    #pragma omp parallel for
    for (int i=0; i<int(f.size()); i++) {
        array_2D s;
        s = refocus(f[i], source);

        if (st_type == "vigra") {
            st = OpenLF::operators::Structure_Tensor::vigra_structure_tensor_from_source(s, inner_scale, outer_scale, smoothing_scale);
        }
   
        if (st_type == "scharr_5x5") {
            st = Scharr5x5_structure_tensor_from_source(s, smoothing_scale);
        } 

        array_2D orientation;

        orientation = OpenLF::operators::Structure_Tensor::orientation(st, "yes", coh_threshold, max_slope);
        orientation += f[i];
        
        orientation = refocus_uncut(-f[i], orientation);
        st.coherence = refocus_uncut(-f[i], st.coherence);

        for (auto it = st.coherence.begin(); it != st.coherence.end(); it++) {
            if (*it < coh_threshold) {
                *it = 0.0;
            }
        }

        slopes[i] = orientation;
        coherences[i] = st.coherence;
    }
    array_2D coherences_sum(source.shape());

    #pragma omp parallel for
    for(auto it = coherences.begin(); it < coherences.end(); it++) {
        coherences_sum += *it;
    }

    #pragma omp parallel for
    for(auto it = coherences_sum.begin(); it < coherences_sum.end(); it++) {
        if (*it < pow(10,-9)) {
            *it = 1.0;
        }
    }

    #pragma omp parallel for
    for(auto it = coherences.begin(); it < coherences.end(); it++) {
        *it /= coherences_sum;
    }
    
    auto it1 = coherences.begin();
    auto it2 = slopes.begin();
    while(it1 != coherences.end()) {
        *it1 *= *it2;
        it1++;
        it2++;
    }

    #pragma omp parallel for
    for(auto it = coherences.begin(); it < coherences.end(); it++) {
        *it /= coherences_sum;
    }
    
    array_2D coh_final_sum(source.shape(), 0.0); 
    array_2D ori_final_sum(source.shape(), 0.0);

    #pragma omp parallel for
    for(auto it = coherences.begin(); it < coherences.end(); it++) {
        coh_final_sum += *it;
    }

    #pragma omp parallel for
    for(auto it = slopes.begin(); it < slopes.end(); it++) {
        ori_final_sum += *it;
    }

    OpenLF::operators::orientation ori;
    ori.ori = ori_final_sum;
    ori.coh = coh_final_sum;
    return ori;
}

std::vector<array_2D> OpenLF::operators::Structure_Tensor::images_from_epis(std::string channel, DIRECTION direction) {
    //TODO vertical
    std::vector<array_2D> images;
    int width = lf->imgWidth();
    int height = lf->imgHeight();
    int size = width*height; 
    int cams_v = lf->cams_v(); 
    int cams_h = lf->cams_h();

    //loop over rows in epis 
    for(int k=0; k<cams_v; k++) {
       for(int j=0; j<cams_h; j++) {
        
            std::vector<float> data;
            //for(int i=0; i<nr_epis(channel, direction); i++) { 
            //loop over epis
            for(int i=0; i<height; i++) {
                view_1D line = m_horizontal_epis[channel][i+k*height].bind<1>(j);
                data.insert(data.end(),line.begin(),line.end());
            }
            array_2D img = array_2D(width,height);
            for(int i=0; i<size; i++) {
                img.data()[i] = data[i];
            }
            images.push_back(img);
        }
    }
    return images;
}

std::vector<array_2D> OpenLF::operators::Structure_Tensor::images_from_orientations(std::string channel, DIRECTION direction) {
    //TODO vertical
    std::vector<array_2D> images;
    int width = lf->imgWidth();
    int height = lf->imgHeight();
    int size = width*height; 
    int cams_v = lf->cams_v(); 
    int cams_h = lf->cams_h();

    //loop over rows in epis 
    for(int k=0; k<cams_v; k++) {
       for(int j=0; j<cams_h; j++) {
        
            std::vector<float> data;
            //for(int i=0; i<nr_epis(channel, direction); i++) { 
            //loop over epis
            for(int i=0; i<height; i++) {
                view_1D line = orientations[channel][i+k*height].bind<1>(j);
                data.insert(data.end(),line.begin(),line.end());
            }
            array_2D img = array_2D(width,height);
            for(int i=0; i<size; i++) {
                img.data()[i] = data[i];
            }
            images.push_back(img);
        }
    }
    return images;
}


std::vector<array_2D> OpenLF::operators::Structure_Tensor::reconstruct_depth(std::string channel, int focus, DIRECTION direction, double inner_scale, double outer_scale, std::string coherence, double coh_threshold, double max_slope, std::string method) {

    //horizontal only, vigra only
    // loop over epis and construct structure tensor + orientation for each. Save orientations.

    orientations[channel].clear();
    for(int i=0; i<lf->height(); i++) {
        OpenLF::operators::ST st = OpenLF::operators::Structure_Tensor::vigra_structure_tensor(channel, i, 0, direction, inner_scale, outer_scale);
        array_2D orientation = OpenLF::operators::Structure_Tensor::orientation(st, coherence, coh_threshold, max_slope);
        orientations[channel].push_back(orientation);
    }
    // restore images
    std::vector<array_2D> images = OpenLF::operators::Structure_Tensor::images_from_orientations(channel, direction);
    return images;
}


