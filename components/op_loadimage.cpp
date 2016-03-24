/*
 * Copyright (c) 2015 Heidelberg Collaboratory for Image Processing
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
 *
 * Author Sven Wanner, Maximilian Diebold, Hendrik Siedelmann
 *
 */
#include <vigra/imageinfo.hxx>
#include <vigra/impex.hxx>
#include "openlf/operator_macro.hpp"

#define OUTDIM 3

using namespace vigra;
using namespace clif;

class OP_LoadImage : public DspComponent {
public:
	OP_LoadImage();
	DSPCOMPONENT_TRIVIAL_CLONE(OP_LoadImage);
protected:
	virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
	virtual bool ParameterUpdating_(int index, DspParameter const& param);
private:
	clif::Mat _output_image;
};

OP_LoadImage::OP_LoadImage() {
	// add inputs
	setTypeName_("OP_LoadImage");
	AddOutput_("ImgOut");
	// add parameter
	AddParameter_("filename", DspParameter(DspParameter::String, ""));
}

template<typename T> vigra::MultiArray<2, T> read_vigra_image(vigra::ImageImportInfo *imageInfo)
{
			vigra::MultiArray<2, T> img2D(imageInfo->shape());
		    vigra::importImage(*imageInfo, img2D);
		    return img2D;
}

template<typename T> class OP_LoadImage_dispatcher {
public:
	void operator()(vigra::ImageImportInfo *imageInfo, clif::Mat **out_mat, DspSignalBus *inputs, DspSignalBus *outputs) {
		out_mat[0]->create(toBaseType<T>(), Idx({ imageInfo->width(), imageInfo->height(), OUTDIM }));
		vigra::MultiArrayView<OUTDIM, T> out;
		out = vigraMAV<OUTDIM, T>(*out_mat[0]);

		if (imageInfo->isColor()) {
			vigra::MultiArray<2, RGBValue<T> > img2D = read_vigra_image< RGBValue<T> >(imageInfo);
			for(int c=0; c<3; c++)
				out.bindAt(2, c) = img2D.bindElementChannel(c);
		} else {
			out.bindAt(2, 0) = read_vigra_image<T>(imageInfo);
		}
	}
	;
};

namespace {
template <class FROM> struct _is_valid : public std::integral_constant<bool, std::is_convertible<FROM,float>::value && !std::is_same<FROM,char>::value> {};
}

void OP_LoadImage::Process_(DspSignalBus& inputs, DspSignalBus& outputs) {
	bool stat;
	clif::Mat *out_ptr;
	out_ptr = &_output_image;

	stat = outputs.SetValue(0, out_ptr);
	if (!stat) {
		printf("OP_LoadImage: output %d set failed\n", 0);
		abort();
	}

	if (configOnly())
		return;

//	std::string path = *GetParameter(0)->GetString();
//	const char *filename = path.c_str();
	ImageImportInfo imageInfo(GetParameter(0)->GetString()->c_str());
	BaseType type;
	switch (imageInfo.pixelType()) {
	case ImageImportInfo::PixelType::UINT8:
		type = BaseType::UINT8;
		break;
	case ImageImportInfo::PixelType::INT16:
		type = BaseType::INT;
		break;
	case ImageImportInfo::PixelType::UINT16:
		type = BaseType::UINT16;
		break;
	case ImageImportInfo::PixelType::INT32:
		type = BaseType::INT;
		break;
	case ImageImportInfo::PixelType::UINT32:
		type = BaseType::UINT32;
		break;
	case ImageImportInfo::PixelType::FLOAT:
		type = BaseType::FLOAT;
		break;
	case ImageImportInfo::PixelType::DOUBLE:
		type = BaseType::DOUBLE;
		break;
	default:
		type = BaseType::INVALID;
	}
	if (type == BaseType::INVALID) {
		printf("OP_LoadImage: image has unrecognized type\n");
		abort();
	}

	std::cout << "Loaded image: ";
	std::cout << imageInfo.width() << "x" << imageInfo.height() << "x"
			<< imageInfo.numBands() << " " << imageInfo.getPixelType() << " "
			<< imageInfo.getFileType() << std::endl;

	clif::callIf<OP_LoadImage_dispatcher,_is_valid>(type, &imageInfo, &out_ptr, &inputs, &outputs);

}

bool OP_LoadImage::ParameterUpdating_(int i, DspParameter const &p) {
	SetParameter_(i, p);
	return true;
}



EXPORT_DSPCOMPONENT(OP_LoadImage)

