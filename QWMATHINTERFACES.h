//
// Created by bwats on 2024-08-12.
//

#ifndef QUICKTOOLS_H
#define QUICKTOOLS_H
#include "QWARRAYS.h"


namespace QWERT {


    struct Operator {
        static double g(double a, double b) {return 0;}
    };



    struct Function {
        static double f(double a){return 0;};
    };



    struct GroupCommutator {
        template<typename k>
        static double h(ArrayTemplate<k, double>& arr) {return 0;}
    };




}
#endif //QUICKTOOLS_H
