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

#include "OpenLF/lightfield/Lightfield_3D.hpp"

OpenLF::lightfield::Lightfield_3D::Lightfield_3D() : Lightfield() 
{
    print(1,"lightfield::Lightfield_3D() called...");
    
}

OpenLF::lightfield::Lightfield_3D::Lightfield_3D(const std::string filename) : Lightfield(filename)
{
    print(1,"lightfield::Lightfield_3D(filename) called...");
}

OpenLF::lightfield::Lightfield_3D::~Lightfield_3D()
{
    print(1,"lightfield::~Lightfield_3D() called...");
}

/*!
This is the efficient variant of accessing epipolar plane images due to the concatenated memory access.
Accessing the vertical epipolar plane images using _getVerticalEpiChannel_4D is inefficient compared to this
due to the column accessing. To achieve the same efficiency for vertical access transpose the data and use
the horizontal access. 

\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::Lightfield_3D::_getVerticalEpiChannel_3DV(int x, std::string channel_name, int focus) 
{
    // if channel exist
    if (hasChannel(channel_name)) {
        
        int offset = (cams_v()-1)*focus;
        vigra::MultiArrayView<1, float> row = m_channels[channel_name].viewToRow(x);
        shape epi_shape = shape(imgHeight()-(cams_v()-1)*focus,cams_v());
        strideTag stride = strideTag(1, imgHeight() - focus);
        return view_2D(epi_shape, stride, row.data() + offset);        
    } else
        throw OpenLF_Exception("Lightfield::_getHorizontalEpi_3DV -> channel not available!");
}
