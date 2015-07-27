/* 
 * File:   MyEpiOperator.cpp
 * Author: swanner
 * 
 * Created on May 15, 2014, 2:03 PM
 */

#include "OpenLF/operators/MyEpiOperator.hpp"

OpenLF::operators::MyEpiOperator::~MyEpiOperator() {
}

void OpenLF::operators::MyEpiOperator::allocate()
{
    m_tmp_memory["aTmpStorage"] = OpenLF::image::ImageChannel();
    m_tmp_memory["aTmpStorage"].init(lf->width(),lf->height(),0.0f);
}

void OpenLF::operators::MyEpiOperator::precompute()
{
    
    
}

void OpenLF::operators::MyEpiOperator::compute()
{   
    //int number = lf->cams_v()*lf->height();
    //*************************************
    //** a performance test of omp iterator
    //** 
    //*************************************

//    std::vector<view_2D> refocused;
//    for(auto it = horizontal_epis_ptr()->begin(); it<horizontal_epis_ptr()->end(); it++) {
//        refocused.push_back(refocus(1, *it));
//    }
//
//    #pragma omp parallel for
//    for(auto it = horizontal_epis_ptr()->begin(); it<horizontal_epis_ptr()->end(); it++) {
//        for(int i=0; i<5000; i++) {
//        *it *=10.0;
//        *it -=10.0;
//        *it +=10.0;
//        *it /=10.0;
//        }
//    }
}   

void OpenLF::operators::MyEpiOperator::postcompute()
{

}
