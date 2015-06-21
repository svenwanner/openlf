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

#ifndef OPERATOR_EPI_HPP
#define	OPERATOR_EPI_HPP

//#include "OpenLF/debug.hpp"
//#include "OpenLF/global.hpp"
#include "OpenLF/operators/Operator.hpp"

namespace OpenLF {
    namespace operators {

typedef std::vector<array_2D> epi_vector;
typedef std::vector<view_2D> epi_view_vector;
//typedef std::vector<epi_view> epi_vector;
typedef std::map < std::string, std::vector<array_2D> > epi_map;
typedef std::map < std::string, std::vector<view_2D> > epi_view_map;

struct epi_view {
    view_2D EPI;
    int focus;
    //int height() { return EPI.height(); }
    //int width() { return EPI.width(); }
    //vigra::Shape2 shape() { return EPI.shape(); }
};

struct epi {
    array_2D EPI;
    //int focus=-pow(10,6);
    int focus;
    //int height() { return EPI.height(); }
    //int width() { return EPI.width(); }
    //vigra::Shape2 shape() { return EPI.shape(); }
};

//to use with different focuses for each epi 
typedef std::vector<epi_view> refocused_epi_vector;
typedef std::map < std::string, epi_vector > refocused_epi_map;

class Operator_EPI : public Operator {
public:
    Operator_EPI(std::vector<std::string> inslots, std::vector<std::string> outslots) : Operator(inslots,outslots) {};
    virtual ~Operator_EPI();

    //void load_epi_containers();
    void load_epi_containers(std::string channel);
    view_2D refocus(int focus, view_2D epi);
    // refocuses leaving the pixels uncut
    epi refocus_uncut(int focus, epi_view epi);
    epi refocus_uncut(int focus, epi epi);
    array_2D refocus_uncut(int focus, view_2D epi);
    epi backfocus(epi epi);
    //epi backfocus(epi_view epi);
    //epi_vector refocus(int focus);
    void set(OpenLF::lightfield::Lightfield *lf);
    epi_vector * horizontal_epis_ptr(std::string channel);
    epi_vector * vertical_epis_ptr(std::string channel);
    array_2D get_horizontal_epi(std::string channel, int where);
    array_2D get_vertical_epi(std::string channel, int where);
    void refocus(int focus, std::string channel);
    double get_focus(std::string channel);

//private:
    // privides storage for many simulaneously refocused epis of the channels 
    epi_map m_horizontal_epis; 
    epi_map m_vertical_epis;
    epi_map m_horizontal_refocused; 
    epi_map m_vertical_refocused;
    std::map <std::string, int> m_focuses;
    int nr_epis(std::string channel, DIRECTION direction);

};

}}
#endif	/* OPERATOR_EPI_HPP */

