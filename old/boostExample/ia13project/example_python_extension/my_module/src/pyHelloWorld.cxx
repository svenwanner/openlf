// boost python related
#include <boost/python/detail/wrap_python.hpp>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/exception_translator.hpp>
#include <numpy/arrayobject.h>
#include <numpy/noprefix.h>

// vigra numpy array converters
#include <vigra/numpy_array.hxx>
#include <vigra/numpy_array_converters.hxx>

// standart c++ headers (whatever you need (string and vector are just examples))
#include <string>
#include <vector>

// my headers  ( in my_module/include )
#include <my_include.hxx>


// this functions show how to loop over an 
// entire image and do something with each pixel
// and store the result in a new image

vigra::NumpyAnyArray  imageLoop(

    vigra::NumpyArray<2,float> inputImage
){

    // allocate output image (also a float image in this case)
    typedef vigra::NumpyArray<2,float> ArrayType;
    typedef ArrayType::difference_type ArrayShape;
    size_t dimX=inputImage.shape(0);
    size_t dimY=inputImage.shape(1);

    ArrayType resultArray(ArrayShape(dimX,dimY));

    for(size_t y=0;y<dimY;++y){
        for(size_t x=0;x<dimX;++x){
            
            // do *something* a pixel  and store in in the result array
            resultArray(x,y)=2*inputImage(x,y)+1;
        }   
    }

    return resultArray;
}


void export_HelloWorld(){
    // Do not change next 4 lines
    import_array(); 
    vigra::import_vigranumpy();
    boost::python::numeric::array::set_module_and_type("numpy", "ndarray");
    boost::python::docstring_options docstringOptions(true,true,false);
    // No not change 4 line above


    // export the function to python
    boost::python::def("imageLoop", vigra::registerConverters(&imageLoop) ,
        (
            boost::python::arg("image")
        ),
        "loop over an image and do something with each pixels\n\n"
        "Args:\n\n"
        "   image : input image\n\n"
        "returns an an image with the same shape as the input image"
    );
}