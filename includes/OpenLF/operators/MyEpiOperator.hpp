#ifndef MYEPIOPERATOR_HPP
#define	MYEPIOPERATOR_HPP

#include <iostream>
#include "OpenLF/operators/Operator_EPI.hpp"


namespace OpenLF {
    namespace operators {



class MyEpiOperator : public OpenLF::operators::Operator_EPI {
public:
    MyEpiOperator(std::vector<std::string> inslots, std::vector<std::string> outslots) : Operator_EPI(inslots,outslots) {};
    //My4DOperator(const My4DOperator& orig);
    virtual ~MyEpiOperator();

    
protected:
    void allocate();
    void precompute();
    void compute();
    void postcompute();
    
    
};

}}
#endif	/* MYEPIOPERATOR_HPP */

