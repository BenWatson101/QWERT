//
// Created by bwats on 2024-08-22.
//

#ifndef QWMATH_H
#define QWMATH_H
#include <cmath>

#include "QWMATHINTERFACES.h"

namespace QWERT {

    //
    // Functions
    //

    struct Linear : Function {
        static double f(double const a) {
            return a;
        }
    };

    struct Squared : Function {
        static double f(double const a) {
            return a * a;
        }
    };

    struct Sigmoid : Function {
        static double f(double const a) {
            return 1 / (1 + exp(-a));
        }
    };

    //
    //Operators
    //

    struct Add final : Operator {
        static double g(const double a, const double b) {
            return a + b;
        }
    };


    struct Multiply final : Operator {
        static double g(const double a, const double b) {
            return a * b;
        }
    };

    //
    //Group Commutators
    //

    struct Sum : GroupCommutator {
        template<typename k>
        static double h(ArrayTemplate<k, double>& arr) {
            double j = 0;
            for(const double i: arr) {
                j += i;
            }
            return j;
        }
    };

    struct Average : GroupCommutator {
        template<typename k>
        static double h(ArrayTemplate<k, double>& arr) {
            return Sum::h(arr) / static_cast<double>(arr.getSize());
        }
    };

}



#endif //QWMATH_H
