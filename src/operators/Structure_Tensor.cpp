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
    if (!lf->hasChannel(channel)) {
        throw OpenLF_Exception("OpenLF::operators::Structure_Tensor::vigra_structure_tensor : Channel doesn't exist!");
    } 

    if (focus != get_focus(channel) && focus != 0) {
        refocus(focus, channel);
    }

    OpenLF::operators::ST tensor;

    if (direction == HORIZONTAL) {
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

    up = sqrt(pow(st.yy-st.xx, 2.0) + 4.0*pow(st.xy,2.0));
    down = st.yy+st.xx;

    for(auto it = down.begin(); it<down.end(); it++) {
        if(*it < pow(10.0,-9)) {
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

    scharr_y.initExplicitly(vigra::Diff2D(-2,-2), vigra::Diff2D(2,2)) =
    -1.0, -2.0, -3.0, -2.0, -1.0,
    -1.0, -2.0, -6.0, -2.0, -1.0,
     0.0,  0.0,  0.0,  0.0,  0.0,
     1.0,  2.0,  6.0,  2.0,  1.0,
     1.0,  2.0,  3.0,  2.0,  1.0;

    for (int i=-2; i<3; i++) {
        for (int j=-2; j<3; j++) {
            scharr_x(i,j) /= 60.0;
            scharr_y(i,j) /= 60.0;
        }
    }
/*    float norm = scharr_x.norm()/60.0;
    scharr_x.normalize(norm);
    scharr_y.normalize(norm);
*/
    vigra::MultiArray<2, float> destination_x(source.shape());
    vigra::MultiArray<2, float> destination_y(source.shape());

    vigra::convolveImage(source, destination_x, scharr_x);
    vigra::convolveImage(source, destination_y, scharr_y);

    OpenLF::operators::ST st;

    st.xx = destination_x*destination_x;
    st.xy = destination_x*destination_y;
    st.yy = destination_y*destination_y;

    vigra::gaussianSmoothing(st.xx, st.xx, scale);
    vigra::gaussianSmoothing(st.xy, st.xy, scale);
    vigra::gaussianSmoothing(st.yy, st.yy, scale);

    vigra::MultiArray<2, float> up(source.shape());
    vigra::MultiArray<2, float> down(source.shape());

    up = sqrt(pow(st.yy-st.xx, 2.0) + 4.0*pow(st.xy,2.0));
    down = st.yy+st.xx;

    for(auto it = down.begin(); it<down.end(); it++) {
        if(*it < pow(10.0,-9)) {
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

    if (focus != get_focus(channel) && focus != 0) {
        refocus(focus, channel);
    }

    OpenLF::operators::ST st;

    if (direction == HORIZONTAL) {
        if (epi > lf->height()) {
            throw OpenLF_Exception("OpenLF::operators::Structure_Tensor:Scharr5x5_structure_tensor : epi out of range!");
        }
        if (focus == 0) {
            st = OpenLF::operators::Structure_Tensor::Scharr5x5_structure_tensor_from_source(m_horizontal_epis[channel][epi], scale);
        }
        else {
            st = OpenLF::operators::Structure_Tensor::Scharr5x5_structure_tensor_from_source(m_horizontal_refocused[channel][epi], scale); 
        }
    }
    if (direction == VERTICAL) {
        if (epi > lf->width()) {
            throw OpenLF_Exception("OpenLF::operators::Structure_Tensor::Scharr5x5_structure_tensor : epi out of range!");
        } 
        if (focus == 0) {
            st = OpenLF::operators::Structure_Tensor::Scharr5x5_structure_tensor_from_source(m_vertical_epis[channel][epi], scale);
        }
        else {
            st = OpenLF::operators::Structure_Tensor::Scharr5x5_structure_tensor_from_source(m_vertical_refocused[channel][epi], scale);
        }
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

        // TODO Can we combine these two while-loops ???

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
    std::vector<array_2D> slopes(int(f.size()));
    std::vector<array_2D> coherences(int(f.size()));
    /*std::vector<array_2D>::iterator it1;
    std::vector<array_2D>::iterator it2;
    it1 = slopes.begin();
    it2 = coherences.begin();*/
    
    for (int i=0; i<int(f.size()); i++) {
        array_2D s;
        s = refocus_uncut(f[i], source);

        if (st_type == "vigra") {
            st = OpenLF::operators::Structure_Tensor::vigra_structure_tensor_from_source(s, inner_scale, outer_scale, smoothing_scale);
        }
   
        if (st_type == "scharr_5x5") {
            st = Scharr5x5_structure_tensor_from_source(s, smoothing_scale);
        }

        if (st_type == "scharr_3x3") {
            st = Scharr3x3_structure_tensor_from_source(s, smoothing_scale);
        }
        
        OpenLF::operators::epi orientation;
        orientation.focus = f[i];

        orientation.EPI = OpenLF::operators::Structure_Tensor::orientation(st, "yes", coh_threshold, max_slope);
        orientation.EPI += f[i]; //?
        
        orientation = refocus_uncut(0, orientation);

        OpenLF::operators::epi coherence;
        coherence.EPI = st.coherence;
        coherence.focus = f[i];
        
        coherence = refocus_uncut(0, coherence);

        for (auto it = coherence.EPI.begin(); it != coherence.EPI.end(); it++) {
            if (*it < coh_threshold) {
                *it = 0.0;
            }
        }
  
        slopes[i] = orientation.EPI;
        coherences[i] = coherence.EPI;
    }

    array_2D coherences_sum(source.shape());

    for(auto it = coherences.begin(); it < coherences.end(); it++) {
        coherences_sum += *it;
    }

    for(auto it = coherences_sum.begin(); it < coherences_sum.end(); it++) {
        if (*it < pow(10,-9)) {
            *it = 1.0;
        }
    }

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

    for(auto it = coherences.begin(); it < coherences.end(); it++) {
        *it /= coherences_sum;
    }
    
    array_2D coh_final_sum(source.shape(), 0.0); 
    array_2D ori_final_sum(source.shape(), 0.0);

    for(auto it = coherences.begin(); it < coherences.end(); it++) {
        coh_final_sum += *it;
    }

    for(auto it = slopes.begin(); it < slopes.end(); it++) {
        ori_final_sum += *it;
    }

    OpenLF::operators::orientation ori;
    ori.ori = ori_final_sum;
    ori.coh = coh_final_sum;
/*
    OpenLF::operators::orientation ori;
    ori.ori = ori_sum;
    ori.coh = coh_sum;
*/

/*
    OpenLF::operators::orientation ori;
    ori.ori = slopes[5];
    ori.coh = coherences[5];
*/
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

    if (direction == HORIZONTAL) {
        //loop over rows in epis 
        for(int k=0; k<cams_v; k++) {
            for(int j=0; j<cams_h; j++) {
        
                std::vector<float> data; 
                //loop over epis
                for(int i=0; i<height; i++) {
                    view_1D line = m_horizontal_epis[channel][i+k*height].bind<1>(j);
                    data.insert(data.end(),line.begin(),line.end());
                }
                array_2D img(shape(width,height));
                for(int i=0; i<size; i++) {
                    img.data()[i] = data[i];
                }
                images.push_back(img);
            }
        }
    }
    if (direction == VERTICAL) {
        //loop over rows in epis 
        for(int k=0; k<cams_h; k++) {
            for(int j=0; j<cams_v; j++) {
        
                std::vector<float> data;
                //loop over epis
                for(int i=0; i<width; i++) {
                    view_1D line = m_vertical_epis[channel][i+k*width].bind<1>(j);
                    data.insert(data.end(), line.begin(),line.end());
                }
                array_2D img(shape(height,width));
                for(int i=0; i<size; i++) {
                    img.data()[i] = data[i];
                }
                images.push_back(img);
            }
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

    if (direction == HORIZONTAL) {
        //loop over rows in epis 
        for(int k=0; k<cams_v; k++) {
           for(int j=0; j<cams_h; j++) {
        
                std::vector<float> data;
                //loop over epis
                for(int i=0; i<height; i++) {
                    view_1D line = orientations_horizontal[channel][i+k*height].bind<1>(j);
                    data.insert(data.end(),line.begin(),line.end());
                }
                array_2D img = array_2D(shape(width,height));
                for(int i=0; i<size; i++) {
                    img.data()[i] = data[i];
                }
                images.push_back(img);
            }
        }
    }
    if (direction == VERTICAL) {
        //loop over rows in epis 
        for(int k=0; k<cams_h; k++) {
           for(int j=0; j<cams_v; j++) {
        
                std::vector<float> data;
                //loop over epis
                for(int i=0; i<width; i++) {
                    view_1D line = orientations_vertical[channel][i+k*width].bind<1>(j);
                    data.insert(data.end(),line.begin(),line.end());
                }
                array_2D img = array_2D(shape(height,width));
                for(int i=0; i<size; i++) {
                    img.data()[i] = data[i];
                }
                images.push_back(img);
            }
        }
    }
    return images;
}


std::vector<array_2D> OpenLF::operators::Structure_Tensor::reconstruct_depth(std::string channel, std::string method, std::string coherence, int focus, DIRECTION direction, double inner_scale, double outer_scale, double smoothing_scale, double coh_threshold, double max_slope, focuses f) {

    if (direction == HORIZONTAL) {
    
        orientations_horizontal[channel].clear();
        array_2D ori;
        //#pragma omp parallel for
        for(int i=0; i<lf->height(); i++) {
            if (method == "vigra") {
                OpenLF::operators::ST st = OpenLF::operators::Structure_Tensor::vigra_structure_tensor(channel, i, focus, direction, inner_scale, outer_scale);
                ori = OpenLF::operators::Structure_Tensor::orientation(st, coherence, coh_threshold, max_slope);
            }
            if (method == "                    if (method == \"focused_scharr5x5\") {\n"
                                  "                        OpenLF::operators::orientation ori_ = OpenLF::operators::Structure_Tensor::focused_orientation(epi, f, inner_scale, outer_scale, smoothing_scale, max_slope, coh_threshold, \"scharr_5x5\");\n"
                                  "                        ori = ori_.ori;\n"
                                  "                    }5x5") {
                OpenLF::operators::ST st = Scharr5x5_structure_tensor(channel, i, focus, direction, smoothing_scale);
                ori = OpenLF::operators::Structure_Tensor::orientation(st, coherence, coh_threshold, max_slope);
            }  
            if (method == "focused_vigra") {
                OpenLF::operators::orientation ori_ = OpenLF::operators::Structure_Tensor::focused_orientation(m_horizontal_epis[channel][i], f, inner_scale, outer_scale, smoothing_scale, max_slope, coh_threshold, "vigra");
                ori = ori_.ori;
        }
            if (method == "focused_scharr5x5") {
                OpenLF::operators::orientation ori_ = OpenLF::operators::Structure_Tensor::focused_orientation(m_horizontal_epis[channel][i], f, inner_scale, outer_scale, smoothing_scale, max_slope, coh_threshold, "scharr_5x5");
                ori = ori_.ori;
            }
            orientations_horizontal[channel].push_back(ori);
        }
    }
    
    if (direction == VERTICAL) {
    
        orientations_vertical[channel].clear();
        array_2D ori;
        //#pragma omp parallel for
        for(int i=0; i<lf->width(); i++) {
            if (method == "vigra") {
                OpenLF::operators::ST st = OpenLF::operators::Structure_Tensor::vigra_structure_tensor(channel, i, focus, direction, inner_scale, outer_scale);
                ori = OpenLF::operators::Structure_Tensor::orientation(st, coherence, coh_threshold, max_slope);
            }
            if (method == "scharr5x5") { 
                OpenLF::operators::ST st = Scharr5x5_structure_tensor(channel, i, focus, direction, smoothing_scale);
                ori = OpenLF::operators::Structure_Tensor::orientation(st, coherence, coh_threshold, max_slope);
            }  
            if (method == "focused_vigra") {
                OpenLF::operators::orientation ori_ = OpenLF::operators::Structure_Tensor::focused_orientation(m_vertical_epis[channel][i], f, inner_scale, outer_scale, smoothing_scale, max_slope, coh_threshold, "vigra");
                ori = ori_.ori;
        }
            if (method == "focused_scharr5x5") {
                OpenLF::operators::orientation ori_ = OpenLF::operators::Structure_Tensor::focused_orientation(m_vertical_epis[channel][i], f, inner_scale, outer_scale, smoothing_scale, max_slope, coh_threshold, "scharr_5x5");
                ori = ori_.ori;
            }
            orientations_vertical[channel].push_back(ori);
        }
    }
    // restore images
    std::vector<array_2D> images = OpenLF::operators::Structure_Tensor::images_from_orientations(channel, direction);
    return images;
}


std::vector<array_2D> OpenLF::operators::Structure_Tensor::reconstruct_depth_lightweight(std::string channel, std::string method, std::string coherence,  DIRECTION direction, double inner_scale, double outer_scale, double smoothing_scale, double coh_threshold, double max_slope, focuses f) {

    if (direction == HORIZONTAL) {
     
        orientations_horizontal[channel].clear();
        array_2D ori;
        //shape epi_shape = shape(lf->imgWidth(),lf->cams_h());
        //#pragma omp parallel for 
/*
        for(int j=0; j<lf->cams_v()*lf->imgHeight(); j++) {
	        view_1D row = lf->data()->find(channel)->second.viewToRow(j);
                array_2D epi = array_2D(epi_shape,row.data());
                array_2D orientation(epi.shape());
                //view_2D epi = getHorizontalEpiChannel(channel, y, v);
		for(focuses::iterator it = f.begin() ; it != f.end(); ++it) {

                    if (method == "vigra") {
                        OpenLF::operators::ST st = vigra_structure_tensor_from_source(epi, inner_scale, outer_scale, smoothing_scale);
                        ori = OpenLF::operators::Structure_Tensor::orientation(st, coherence, coh_threshold, max_slope);
                    }
                    if (method == "scharr5x5") { 
                        OpenLF::operators::ST st = Scharr5x5_structure_tensor_from_source(epi, smoothing_scale);
                        ori = OpenLF::operators::Structure_Tensor::orientation(st, coherence, coh_threshold, max_slope);
                    }  
                    if (method == "focused_vigra") {
                        OpenLF::operators::orientation ori_ = OpenLF::operators::Structure_Tensor::focused_orientation(epi, f, inner_scale, outer_scale, smoothing_scale, max_slope, coh_threshold, "vigra");
                        ori = ori_.ori;
                    }
                    if (method == "focused_scharr5x5") {
                        OpenLF::operators::orientation ori_ = OpenLF::operators::Structure_Tensor::focused_orientation(epi, f, inner_scale, outer_scale, smoothing_scale, max_slope, coh_threshold, "scharr_5x5");
                        ori = ori_.ori;
                    }
                    orientation += ori;
                }
                orientations_horizontal[channel].push_back(orientation);
            }
            
	
    }*/

     for(int i=0; i<lf->cams_v(); i++) {
         for(int j=0; j<lf->imgHeight(); j++) {
                array_2D epi = array_2D(lf->getHorizontalEpiChannel(channel, j, i)); 
                    if (method == "vigra") {
                        OpenLF::operators::ST st = vigra_structure_tensor_from_source(epi, inner_scale, outer_scale, smoothing_scale);
                        ori = OpenLF::operators::Structure_Tensor::orientation(st, coherence, coh_threshold, max_slope);
                    }
                    if (method == "scharr5x5") {
                        OpenLF::operators::ST st = Scharr5x5_structure_tensor_from_source(epi, smoothing_scale);
                        ori = OpenLF::operators::Structure_Tensor::orientation(st, coherence, coh_threshold, max_slope);
                    }
                    if (method == "scharr3x3") {
                        OpenLF::operators::ST st = Scharr3x3_structure_tensor_from_source(epi, smoothing_scale);
                        ori = OpenLF::operators::Structure_Tensor::orientation(st, coherence, coh_threshold, max_slope);
                    }
                    if (method == "focused_vigra") {
                        OpenLF::operators::orientation ori_ = OpenLF::operators::Structure_Tensor::focused_orientation(epi, f, inner_scale, outer_scale, smoothing_scale, max_slope, coh_threshold, "vigra");
                        ori = ori_.ori;
                    }
                    if (method == "focused_scharr5x5") {
                        OpenLF::operators::orientation ori_ = OpenLF::operators::Structure_Tensor::focused_orientation(epi, f, inner_scale, outer_scale, smoothing_scale, max_slope, coh_threshold, "scharr_5x5");
                        ori = ori_.ori;
                    }
                    if (method == "focused_scharr3x3") {
                        OpenLF::operators::orientation ori_ = OpenLF::operators::Structure_Tensor::focused_orientation(epi, f, inner_scale, outer_scale, smoothing_scale, max_slope, coh_threshold, "scharr_3x3");
                        ori = ori_.ori;
                    }
                orientations_horizontal[channel].push_back(ori);
            }
            
        }
    }

    if (direction == VERTICAL) {
        
        orientations_vertical[channel].clear();
        array_2D ori;
        //shape epi_shape = shape(lf->imgHeight(),lf->cams_v());
        //#pragma omp parallel for
        for(int i=0; i<lf->cams_h(); i++) {
	    for(int j=0; j<lf->imgWidth(); j++) {
                array_2D epi = array_2D(lf->getVerticalEpiChannel(channel, j, i));
                    if (method == "vigra") {
                        OpenLF::operators::ST st = vigra_structure_tensor_from_source(epi, inner_scale, outer_scale, smoothing_scale);
                        ori = OpenLF::operators::Structure_Tensor::orientation(st, coherence, coh_threshold, max_slope);  
                    }
                    if (method == "scharr5x5") { 
                        OpenLF::operators::ST st = Scharr5x5_structure_tensor_from_source(epi, smoothing_scale);
                        ori = OpenLF::operators::Structure_Tensor::orientation(st, coherence, coh_threshold, max_slope);
                    }
                    if (method == "scharr3x3") {
                        OpenLF::operators::ST st = Scharr3x3_structure_tensor_from_source(epi, smoothing_scale);
                        ori = OpenLF::operators::Structure_Tensor::orientation(st, coherence, coh_threshold, max_slope);
                    }
                    if (method == "focused_vigra") {
                        OpenLF::operators::orientation ori_ = OpenLF::operators::Structure_Tensor::focused_orientation(epi, f, inner_scale, outer_scale, smoothing_scale, max_slope, coh_threshold, "vigra");
                        ori = ori_.ori;
                    }
                    if (method == "focused_scharr5x5") {
                        OpenLF::operators::orientation ori_ = OpenLF::operators::Structure_Tensor::focused_orientation(epi, f, inner_scale, outer_scale, smoothing_scale, max_slope, coh_threshold, "scharr_5x5");
                        ori = ori_.ori;
                    }
                    if (method == "focused_scharr3x3") {
                        OpenLF::operators::orientation ori_ = OpenLF::operators::Structure_Tensor::focused_orientation(epi, f, inner_scale, outer_scale, smoothing_scale, max_slope, coh_threshold, "scharr_3x3");
                        ori = ori_.ori;
                    }
                orientations_vertical[channel].push_back(ori);
            }
        }
    }
    // restore images
    std::vector<array_2D> images = OpenLF::operators::Structure_Tensor::images_from_orientations(channel, direction);
    return images;
}


/*
array_2D OpenLF::operators::Structure_Tensor::get_depth_image(std::string channel, std::string method, std::string coherence, int focus, double inner_scale, double outer_scale, double smoothing_scale, double coh_threshold, double max_slope, focuses f) 
{

    std::vector<array_2D> h = OpenLF::operators::Structure_Tensor::reconstruct_depth(channel, method, coherence, focus, HORIZONTAL, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);

    array_2D overlay_h(shape(lf->imgWidth(),lf->imgHeight()),0.0);

    for(int i=0;i<lf->cams_h()*lf->cams_v();i++) {
        overlay_h += h[i];
    }

    std::vector<array_2D> v = OpenLF::operators::Structure_Tensor::reconstruct_depth(channel, method, coherence, focus, VERTICAL, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);

    array_2D overlay_v(shape(lf->imgHeight(),lf->imgWidth()),0.0);

    for(int i=0;i<lf->cams_h()*lf->cams_v();i++) {
        overlay_v += v[i];
    }

    array_2D rotated_overlay_v(lf->imgWidth(),lf->imgHeight());
    vigra::rotateImage(overlay_v,rotated_overlay_v,-90);
    
    overlay_h += rotated_overlay_v;

    return overlay_h;
}
*/

array_2D OpenLF::operators::Structure_Tensor::get_depth_image(std::string channel, std::string method, std::string coherence, int focus, double inner_scale, double outer_scale, double smoothing_scale, double coh_threshold, double max_slope, focuses f) 
{

    std::vector<array_2D> h = OpenLF::operators::Structure_Tensor::reconstruct_depth(channel, method, coherence, focus, HORIZONTAL, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);

    array_2D overlay_h(shape(lf->imgWidth(),lf->imgHeight()),0.0);

    int size = lf->cams_h()*lf->cams_v();
    int index = 0;
    if (size % 2 == 1) {
        index = (size-1)/2+1;
    }
    if (size % 2 == 0) {
        index = (size)/2;
    }
    overlay_h += h[index];


    std::vector<array_2D> v = OpenLF::operators::Structure_Tensor::reconstruct_depth(channel, method, coherence, focus, VERTICAL, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);

    array_2D overlay_v(shape(lf->imgHeight(),lf->imgWidth()),0.0);


    overlay_v += v[index];

    array_2D rotated_overlay_v(lf->imgWidth(),lf->imgHeight());
    vigra::rotateImage(overlay_v,rotated_overlay_v,95);
    
    overlay_h += rotated_overlay_v;

    return overlay_h;
}

array_2D OpenLF::operators::Structure_Tensor::get_depth_image_lightweight(std::string channel, std::string method, std::string coherence, double inner_scale, double outer_scale, double smoothing_scale, double coh_threshold, double max_slope, focuses f) 
{

    std::vector<array_2D> h = OpenLF::operators::Structure_Tensor::reconstruct_depth_lightweight(channel, method, coherence, HORIZONTAL, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);

    int size = h.size();
    int index = (size-1)/2+1;

    array_2D overlay_h(h[index-1]);

    std::vector<array_2D> v = OpenLF::operators::Structure_Tensor::reconstruct_depth_lightweight(channel, method, coherence, VERTICAL, inner_scale, outer_scale, smoothing_scale, coh_threshold, max_slope, f);


    array_2D overlay_v_rotated(overlay_h.shape());
    vigra::rotateImage(v[index-1],overlay_v_rotated,90);
    array_2D overlay_v_reflected(overlay_v_rotated.shape());
    vigra::reflectImage(overlay_v_rotated,overlay_v_reflected,vigra::horizontal);

    overlay_h += overlay_v_reflected;

    return overlay_h;
}


OpenLF::operators::ST OpenLF::operators::Structure_Tensor::Scharr3x3_structure_tensor(std::string channel, int epi,
                                                                                      int focus, DIRECTION direction,
                                                                                      double scale) {
    /*
     * So far, this function is a mere copy of Scharr5x5_structure_tensor, except for the respective name adjustments.
     * It might be possible to completely combine the 3x3 and 5x5 functions and simply let the user choose which kernel to use.
     */
    if (!lf->hasChannel(channel)) {
        throw OpenLF_Exception("OpenLF::operators::Structure_Tensor::Scharr3x3_structure_tensor : Channel doesn't exist!");
    }

    if (focus != get_focus(channel) && focus != 0) {
        refocus(focus, channel);
    }

    OpenLF::operators::ST st;

    if (direction == HORIZONTAL) {
        if (epi > lf->height()) {
            throw OpenLF_Exception("OpenLF::operators::Structure_Tensor:Scharr3x3_structure_tensor : epi out of range!");
        }
        if (focus == 0) {
            st = OpenLF::operators::Structure_Tensor::Scharr3x3_structure_tensor_from_source(m_horizontal_epis[channel][epi], scale);
        }
        else {
            st = OpenLF::operators::Structure_Tensor::Scharr3x3_structure_tensor_from_source(m_horizontal_refocused[channel][epi], scale);
        }
    }
    if (direction == VERTICAL) {
        if (epi > lf->width()) {
            throw OpenLF_Exception("OpenLF::operators::Structure_Tensor::Scharr3x3_structure_tensor : epi out of range!");
        }
        if (focus == 0) {
            st = OpenLF::operators::Structure_Tensor::Scharr3x3_structure_tensor_from_source(m_vertical_epis[channel][epi], scale);
        }
        else {
            st = OpenLF::operators::Structure_Tensor::Scharr3x3_structure_tensor_from_source(m_vertical_refocused[channel][epi], scale);
        }
    }
    return st;
}

OpenLF::operators::ST OpenLF::operators::Structure_Tensor::Scharr3x3_structure_tensor_from_source(
        vigra::MultiArrayView<2, float> &source, double scale) {

    // Setting up the Scharr3x3-Kernel
    vigra::Kernel2D<float> scharr_x = vigra::Kernel2D<float>();
    scharr_x.initExplicitly(vigra::Diff2D(-1,-1), vigra::Diff2D(1,1)) =
            -3.0/32.0, 0.0, 3.0/32.0,
            -10.0/32.0,0.0, 10.0/32.0,
            -3.0/32.0, 0.0, 3.0/32.0;
    scharr_x.setBorderTreatment(vigra::BORDER_TREATMENT_REFLECT);

    vigra::Kernel2D<float> scharr_y = vigra::Kernel2D<float>();
    scharr_y.initExplicitly(vigra::Diff2D(-1,-1), vigra::Diff2D(1,1)) =
            -3.0/32.0, -10.0/32.0, -3.0/32.0,
            0.0,       0.0,        0.0,
            3.0/32.0,  10.0/32.0,  3.0/32.0;
    scharr_y.setBorderTreatment(vigra::BORDER_TREATMENT_REFLECT);

    vigra::MultiArray<2,float> destination_x = vigra::MultiArray<2,float>(source.shape());
    vigra::MultiArray<2,float> destination_y = vigra::MultiArray<2,float>(source.shape());
    OpenLF::operators::ST st;

    //TODO Do we need to gaussian smooth the source before convolution?

    // Convolution
    vigra::convolveImage(source, destination_x, scharr_x);
    vigra::convolveImage(source, destination_y, scharr_y);

    //Calculating and smoothing the three structure tensor components xx, xy, yy
    st.xx = destination_x*destination_x;
    st.xy = destination_x*destination_y;
    st.yy = destination_y*destination_y;

    vigra::gaussianSmoothing(st.xx, st.xx, scale);
    vigra::gaussianSmoothing(st.xy, st.xy, scale);
    vigra::gaussianSmoothing(st.yy, st.yy, scale);

    // Computing the coherence for each pixel
    vigra::MultiArray<2, float> up(source.shape());
    vigra::MultiArray<2, float> down(source.shape());

    up = sqrt(pow(st.yy-st.xx, 2.0) + 4.0*pow(st.xy,2.0));
    down = st.yy+st.xx;

    //TODO Is this really correct???
    for(auto it = down.begin(); it<down.end(); it++) {
        if(*it < pow(10.0,-9)) {
            *it = 1.0;
        }
    }

    vigra::MultiArray<2, float> coherence(source.shape());
    st.coherence = up/down;

    return st;


}
