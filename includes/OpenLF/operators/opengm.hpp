/*
* Copyright (c) 2014 Joerg Hendrik Kappes
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

#ifndef OPENLF_OPENGM_HPP
#define	OPENLF_OPENGM_HPP
#include <iostream>
#include <opengm/graphicalmodel/graphicalmodel.hxx>
#include <opengm/graphicalmodel/graphicalmodel_hdf5.hxx>
#include <opengm/operations/adder.hxx>
#include <opengm/functions/explicit_function.hxx>
#include <opengm/functions/potts.hxx>
#include "OpenLF/operators/Operator_4D.hpp"

template <bool FLAG = true>
class OpenGM : public OpenLF::operators::Operator_4D {
public:

  typedef double ValueType;
  typedef size_t IndexType;
  typedef size_t LabelType;
  typedef opengm::Adder OperatorType;
  typedef opengm::DiscreteSpace<IndexType, LabelType> SpaceType;
  typedef typename opengm::meta::TypeListGenerator<
    opengm::ExplicitFunction<ValueType, IndexType, LabelType>,
    opengm::PottsFunction<ValueType, IndexType, LabelType>
    >::type FunctionTypeList;
  typedef opengm::GraphicalModel<
    ValueType,
    OperatorType,
    FunctionTypeList,
    SpaceType
    > GmType;


  OpenGM() : Operator_4D() {};
  ~OpenGM() {};    
protected:
  void allocate(){};
  void precompute(){};
  void compute(){buildModel();};
  void postcompute(){};
  void buildModel();
private:  
  size_t getID(int x, int y, int h, int v){
    return  x + lf->width()*(y + lf->height()*(h*lf->cams_v() + v));
  };
    
};


template <bool FLAG> void OpenGM<FLAG>::buildModel() {
 
  IndexType numVar = lf->width()*lf->height()*lf->cams_h()*lf->cams_v();
  LabelType numL   = 2;


  std::vector<LabelType> numbersOfLabels(numVar,numL);
  GmType gm(opengm::DiscreteSpace<>(numbersOfLabels.begin(), numbersOfLabels.end()));
  opengm::PottsFunction<ValueType> potts(numL, numL, 0.0, 1.0);
  GmType::FunctionIdentifier pottsid = gm.addFunction(potts);
  std::string channel = "r";
  size_t shape[] = {2};
  opengm::ExplicitFunction<ValueType> f(shape, shape + 1);
  //float* r_ptr = lf->channel_ptr("r");
  //float* g_ptr = lf->channel_ptr("g");
  //float* b_ptr = lf->channel_ptr("b");
  IndexType var[2] = {0,0};
  for(int x=0; x<lf->width(); ++x){
    for(int y=0; y<lf->height(); ++y){
      for(int h=0; h<lf->cams_h(); ++h){
	for(int v=0; v<lf->cams_v(); ++v){
	  float val = lf->getLoxel(v,h,x,y,channel); 
	  var[0] = getID(x,y,h,v);
	  f(0) = ValueType(val);
	  f(1) = ValueType(1-val);
	  GmType::FunctionIdentifier idExplicit = gm.addFunction(f);
	  gm.addFactor(idExplicit, var, var + 1);
	  if(x<lf->width()-1){
	    var[1] = getID(x+1,y,h,v);
	    gm.addFactor(pottsid, var, var + 2);
	  }
	  if(y<lf->height()-1){
	    var[1] = getID(1,y+1,h,v);
	    gm.addFactor(pottsid, var, var + 2);
	  }  
	  if(h<lf->cams_h()-1){
	    var[1] = getID(1,y,h+1,v);
	    gm.addFactor(pottsid, var, var + 2);
	  }
	  if(v<lf->cams_v()-1){
	    var[1] = getID(1,y,h,v+1);
	    gm.addFactor(pottsid, var, var + 2);
	  }
	}	
      }
    }
  }  
  std::cout << "store" <<std::endl;
  // save graphical model into an hdf5 dataset named "toy-gm"
  opengm::hdf5::save(gm, "/tmp/gm.h5", "gm");
  
}


#endif	/* OPENLF_OPENGM_HPP */

