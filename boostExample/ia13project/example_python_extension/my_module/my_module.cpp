#define PY_ARRAY_UNIQUE_SYMBOL my_module_PyArray_API
//#define NO_IMPORT_ARRAY


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



// EVERYTHING WHICH IS IN SRC (but only hxx files)
#include "src/pyHelloWorld.hxx"






// export my module
BOOST_PYTHON_MODULE_INIT(_my_module) {

    // Do not change next 4 lines
    import_array(); 
    vigra::import_vigranumpy();
    boost::python::numeric::array::set_module_and_type("numpy", "ndarray");
    boost::python::docstring_options docstringOptions(true,true,false);
    // No not change 4 line above


    // call all the "export_***" functions from files in src

    // (this will export the functions from pyHelloWorld.cxx)
    export_HelloWorld();

}