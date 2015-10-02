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

/* this is the vector of epis */
typedef std::vector<array_2D> epi_vector;
typedef std::vector<view_2D> epi_view_vector;

/* this is the map of epis */
typedef std::map < std::string, std::vector<array_2D> > epi_map;
typedef std::map < std::string, std::vector<view_2D> > epi_view_map;

/* this is the refocused epi view container */
struct epi_view {
    view_2D EPI;
    int focus;
    //int height() { return EPI.height(); }
    //int width() { return EPI.width(); }
    //vigra::Shape2 shape() { return EPI.shape(); }
};

/* this is the refocused epi container */
struct epi {
    array_2D EPI;
    //int focus=-pow(10,6);
    int focus;
    //int height() { return EPI.height(); }
    //int width() { return EPI.width(); }
    //vigra::Shape2 shape() { return EPI.shape(); }
};

/* stores refocused epis */
typedef std::vector<epi_view> refocused_epi_vector;
/* map of refocused epis */
typedef std::map < std::string, epi_vector > refocused_epi_map;

/* this class is the parent class for all operations on epis. It implements two kinds of refocusing for epis, individually or as a whole channel. Furthermore the class is providing a storage in form of epi maps. */
class Operator_EPI : public Operator {
public:
    Operator_EPI(std::vector<std::string> inslots, std::vector<std::string> outslots) : Operator(inslots,outslots) {};
    virtual ~Operator_EPI();
     
    /* Loads epis into a map for a given channel. Not always necessary, since cumbersome.*/
    void load_epi_containers(std::string channel);
    
    /* this function refocuses a given epi, saving only the central straight region */ 
    view_2D refocus(int focus, view_2D epi);

    /* this function refocuses a given epi, without loss of information */
    epi refocus_uncut(int focus, epi_view epi);
    epi refocus_uncut(int focus, epi epi);

    /* only for internal use with original (not previously refocused) epis with focus 0 */
    array_2D refocus_uncut(int focus, view_2D epi);
   
    /* this function makes a backfocus to f=0 */
    epi backfocus(epi epi);

    /* set a lightfield */
    void set(OpenLF::lightfield::Lightfield *lf);

    
    epi_vector * horizontal_epis_ptr(std::string channel);
    epi_vector * vertical_epis_ptr(std::string channel);

    array_2D get_horizontal_epi(std::string channel, int where);
    array_2D get_vertical_epi(std::string channel, int where);

    /* this function refocuses_uncut the member maps m_horizontal_refocused and m_vertical_refocused */
    void refocus(int focus, std::string channel);
    /* get the focus of a channel */
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

