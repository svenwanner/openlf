Tutorial 2 - Simple Image Processing
======

[TOC]

# Tutorial 2 - Simple Image Processing {#timg}

This tutorial shows how to use several shortcuts to write an image (or any multidimensional array) processing component in less than 10 in lines of code. 

### Prerequisites

If you haven't done so, set up clif and openlf according to [the readme](@ref install). Generate a new source file as specified in [tutorial 1](@ref tut_new).

### Next Steps

See [advanced topics](@ref adv) for api and programming topics, or the [architecture overview](@ref architecture) for more insight in the openlf design, or return to the [main index](@ref doc).

## An Image Processing Component {#timg_comp}

The following code specifies a component which takes two inputs and blends them to generate a single output:

~~~~~~~~~~~~~~~{.cpp}
#include <vigra/multi_math.hxx>
#include "openlf/operator_macro.hpp"

using namespace vigra::multi_math;

#define OPENLF_OP_CONSTRUCT_PARAMS \
  AddParameter_("weight", DspParameter(DspParameter::ParamType::Float, 0.0f));
    
OPENLF_VIGRA_OP_START(OP_Blend, 2, 1, 3, 3)

  float weight = *op->GetParameter(0)->GetFloat();

  out[0] = in[0]*weight + in[1]*1.0-weight;

OPENLF_OP_END

#undef OPENLF_OP_CONSTRUCT_PARAMS
~~~~~~~~~~~~~~~

Thats it. Now for some more details:
~~~~~~~~~~~~~~~{.cpp}
#include <vigra/multi_math.hxx>
#include "openlf/operator_macro.hpp"

using namespace vigra::multi_math;
~~~~~~~~~~~~~~~
The file *openlf/operator_macro.hpp* contains the magic macros that make this code possible, while *vigra/multi_math.hxx* contains operators for the VigraMultiArrayView class, the using directive pulls these operators into our local namespace. It is **very important** that any vigra include always comes first, else compilation can break with undecipherable complaints!

~~~~~~~~~~~~~~~{.cpp}
#define OPENLF_OP_CONSTRUCT_PARAMS \
  AddParameter_("weight", DspParameter(DspParameter::ParamType::Float, 0.0f));
~~~~~~~~~~~~~~~
This preprocessor define specifies the parameters which are inserted into the constructor of our class, don't forget to extent the macro over newlines with "\" when adding more parameters.

~~~~~~~~~~~~~~~{.cpp}
OPENLF_VIGRA_OP_START(OP_Blend, 2, 1, 3, 3)
~~~~~~~~~~~~~~~
This marks the beginning of our code. The arguments are, in order: Component name, number of inputs, number of outputs, input dimensionality and output dimensionality. Inputs and outputs all have to be of the same size and type, dimensionality is fixed as the macro will pass us arrays of VigraMultiArrayView which have a fixed type and dimension. If you are wondering why the dimensionality is 3, this is a convention used within %OpenLF and CLIF, images are regarded as 3D array with color being the third dimension. This means an RGB image as a 3rd dimension of size 3 and a grayscale image of size 1 but still has a third dimension. This abstraction allows image processing to handle any color image type the same by simply looping over the third dimension or (as is the case here) by simply disregarding the size of the image.

~~~~~~~~~~~~~~~{.cpp}
  float weight = *op->GetParameter(0)->GetFloat();
~~~~~~~~~~~~~~~
Read our single parameter, op is a pointer to the actual component instance, a class derived from DspComponent.

~~~~~~~~~~~~~~~{.cpp}
  out[0] = in[0]*weight + in[1]*1.0-weight;
~~~~~~~~~~~~~~~
This is the actual processing - operations on VigraMultiArrayView.
The inputs and outputs specified above are available via the in and out arrays which are specified as follows:
~~~~~~~~~~~~~~~{.cpp}
VigraMultiArrayView<3,T> in[2];
VigraMultiArrayView<3,T> in[1];
~~~~~~~~~~~~~~~
The numbers are the dimensions and input/output counts specified by our call to `OPENLF_VIGRA_OP_START`. While `T` is a template type. Under the hood the code we just wrote will be compiled to a number of types and the actual code path is decided at runtime depending on the content passed to the component.

Thats it, the last line, which completes our component:
~~~~~~~~~~~~~~~{.cpp}
OPENLF_OP_END
~~~~~~~~~~~~~~~
