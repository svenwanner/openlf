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

#include "OpenLF/lightfield/Lightfield_4D.hpp"

OpenLF::lightfield::Lightfield_4D::Lightfield_4D() : Lightfield() 
{
    print(1,"lightfield::Lightfield_4D() called...");
    
}

OpenLF::lightfield::Lightfield_4D::Lightfield_4D(const std::string filename) : Lightfield(filename)
{
    print(1,"lightfield::Lightfield_4D(filename) called...");
}

OpenLF::lightfield::Lightfield_4D::~Lightfield_4D()
{
    print(1,"lightfield::~Lightfield_4D() called...");
}

/*!
This is the efficient variant of accessing epipolar plane images due to the concatenated memory access.
Accessing the vertical epipolar plane images using _getVerticalEpiChannel_4D is inefficient compared to this
due to the column accessing. To achieve the same efficiency for vertical access transpose the data and use
the horizontal access. 

\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::Lightfield_4D::_getHorizontalEpiChannel_4D(int v, int y, std::string channel_name, int focus) 
{
    // if channel exist
    if (hasChannel(channel_name)) {
        
        int offset = (cams_h()-1)*focus;
        vigra::MultiArrayView<1, float> row = m_channels[channel_name].viewToRow(v * imgHeight() + y);
        shape epi_shape = shape(imgWidth()-(cams_h()-1)*focus,cams_h());
        strideTag stride = strideTag(1, imgWidth() - focus);
        return view_2D(epi_shape, stride, row.data() + offset);
        
    } else
        throw OpenLF_Exception("Lightfield::_getHorizontalEpi_4D -> channel not available!");
}

/*!
This is the inefficient variant of accessing epipolar plane images due to the unstrided memory access.
For optimal performance during computation transpose the whole lightfield and use horizontal access. 

\author Sven Wanner (sven.wanner@iwr.uni-heidelberg.de)
*/
view_2D OpenLF::lightfield::Lightfield::_getVerticalEpiChannel_4D(int h, int x, const std::string channel_name, int focus)
{
    // if channel exist
    if (hasChannel(channel_name)) {
        
        int offset = (cams_v()-1)*focus*width();
        vigra::MultiArrayView<1, float> col = m_channels[channel_name].viewToColumn(h * imgWidth() + x);
        shape epi_shape = shape(cams_v(),imgHeight()-(cams_v()-1)*focus);
        strideTag stride = strideTag((imgHeight()-focus)*width(),col.stride()[0]);
        return view_2D(epi_shape, stride, col.data() + offset).transpose();
        
    } else
        throw OpenLF_Exception("Lightfield::_getHorizontalEpi_4D -> channel not available!");
}
