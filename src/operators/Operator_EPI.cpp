/* 
 * File:   Operator_EPI.cpp
 * Author: swanner
 * 
 * Created on May 15, 2014, 2:03 PM
 */

#include "OpenLF/operators/Operator_EPI.hpp"

OpenLF::operators::Operator_EPI::Operator_EPI() : Operator() {
    global_shifts.push_back(0);
}

OpenLF::operators::Operator_EPI::~Operator_EPI() {
}

void OpenLF::operators::Operator_EPI::set_global_shifts(std::vector<int> global_shifts)
{
    this->global_shifts = global_shifts;
}


void OpenLF::operators::Operator_EPI::process() 
{
    if(lf!=NULL) {
        if(lf->type()==LF_4D) {
            
            allocate();
            
            OpenLF::lightfield::EpiIterator *iter_h = lf->createEpiIterator(HORIZONTAL);

            for(iter_h->first(); !iter_h->end(); iter_h->next())
            {
                if(lf->hasRGB())
                {
                    data["r"] = &iter_h->get("r",1);
                    data["g"] = &iter_h->get("g",1);
                    data["b"] = &iter_h->get("b",1);
                }
                if(lf->hasBW())
                {
                    data["bw"] = &iter_h->get("bw",1);
                }
                for(int i=0; i<allocated_channel_names.size(); i++)
                    data[allocated_channel_names[i]] = &iter_h->get(allocated_channel_names[i],1);
                
                precompute();
                compute();
                postcompute();
            }
            
            cleanup();
        }
        else if(lf->type()==LF_3DH) {
            
            allocate();
            precompute();
            compute();
            postcompute();
            cleanup();
        }
        else if(lf->type()==LF_3DV) {
            
            allocate();
            precompute();
            compute();
            postcompute();
            cleanup();
        }
        else if(lf->type()==LF_CROSS) {
            
            allocate();
            precompute();
            compute();
            postcompute();
            cleanup();
        }
        else throw OpenLF_Exception("Wrong lightfield input type exception!");
    }   
    else throw OpenLF_Exception("missing lightfield exception!");
}


void OpenLF::operators::Operator_EPI::cleanup() 
{
    tmp_memory.clear();
}