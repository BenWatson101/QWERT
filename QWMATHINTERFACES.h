//
// Created by bwats on 2024-08-12.
//

#ifndef QWMATHINTERFACES_H
#define QWMATHINTERFACES_H
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

    template<typename arrayType, typename type>
    template<typename function>
    ArrayTemplate<arrayType, type> & ArrayTemplate<arrayType, type>::f() {
        ensureNumeric<type>();
        checkInheritance<Function, function>();
        for(auto &i: *this) {
            i = function::f(i);
        }
        return *this;
    }

    template<typename arrayType, typename type>
    template<typename operate, typename type1, typename type2>
    ArrayTemplate<arrayType, type> & ArrayTemplate<arrayType, type>::g(ArrayTemplate<type1, type2> &other) {

        ensureNumeric<type>();
        ensureNumeric<type2>();
        checkInheritance<Operator, operate>();
        if(this->getSize() != other.getSize()) {
            throw std::out_of_range("Sizes aren't matched for operation");
        }

        ArrayIterable<type> iterate = other.begin();

        for(auto &i: *this) {
            i = operate::g(i, *iterate);
            ++iterate;
        }
        return *this;
    }

    template<typename arrayType, typename type>
    template<typename grouper>
    double ArrayTemplate<arrayType, type>::h() {
        ensureNumeric<type>();
        checkInheritance<GroupCommutator, grouper>();
        return grouper::h(*this);
    }

}
#endif //QWMATHINTERFACES_H
