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

#include "OpenLF/operators/Operator.hpp"

OpenLF::operators::Operator::Operator(std::vector<std::string> inslots, std::vector<std::string> outslots) 
{
    this->inslots = inslots;
    this->outslots = outslots;
    cleanup();
}

//OpenLF::operators::Operator::Operator(const Operator& orig) 
//{
//}

OpenLF::operators::Operator::~Operator() 
{
    cleanup();
}

void OpenLF::operators::Operator::cleanup() 
{
    lf = NULL;
    properties = NULL;
    m_tmp_memory.clear();
}

vigra::MultiArrayView<2, float> OpenLF::operators::Operator::lf_channel(std::string channel) 
{
    if (lf->hasChannel(channel)) {
        return *(lf->data(channel)->image());
    }
    else {
       throw OpenLF_Exception("Channel doesn't exist!");
    }
}

vigra::MultiArrayView<2, float> * OpenLF::operators::Operator::memory_ptr(std::string channel) 
{
    if (m_tmp_views.find(channel) != m_tmp_views.end()) {
        return &(m_tmp_views[channel]);
    }
    else {
       throw OpenLF_Exception("Channel doesn't exist!");
    }
}
/*
OpenLF::image::ImageChannel * tmp_channels_ptr(std::string channel) 
{
    if (tmp_memory.find(channel) != tmp_memory.end()) {
        return &(m_tmp_memory[channel]);
    }
    else {
       throw OpenLF_Exception("Channel doesn't exist!");
    }
}
*/
void OpenLF::operators::Operator::process() 
{
    allocate();
    precompute();
    compute();
    postcompute();
}

/*!
 * This function initializes the internal lf variable with the address of the
 * lf instance passed. If in advance an additional Properties instance was set
 * the lf properties are updated with the additional properties passed.
 * If both property instances share the same fields the lf internal are overwritten 
 * with the values of the additional properties instance. This enables to update 
 * computation parameter during runtime.   
 */
void OpenLF::operators::Operator::set(OpenLF::lightfield::Lightfield *lf) 
{
    // set internal lf pointer 
    this->lf = lf;
    
    if(this->properties != NULL) {
        this->lf->appendProperties(*properties);
    }
}


/*!
 * This function initializes the internal properties variable with the address of 
 * the properties instance passed. If in advance a Lightfield instance was set
 * the lf properties are updated with the additional properties passed.
 * If both property instances share the same fields the lf internal are overwritten 
 * with the values of the additional properties instance. This enables to update 
 * computation parameter during runtime.   
 */
void OpenLF::operators::Operator::set(OpenLF::lightfield::Properties *properties) 
{
    // set internal properties pointer 
    this->properties=properties;
    if(this->lf != NULL) {
        this->lf->appendProperties(*this->properties);
    }
}
