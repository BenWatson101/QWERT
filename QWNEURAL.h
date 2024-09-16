//
// Created by bwats on 2024-09-01.
//

#ifndef QWNEURAL_H
#define QWNEURAL_H
#include "QWARRAYS.h"

template
<size_t previousSize,
typename function, typename operand, typename commutator,
double verticalStretch, double horizontalStretch>
struct QWNODE {
    QWERT::SizedArray<double, previousSize> biases;

    //Neural hash function babyyyyyyyyyy
    void push(QWERT::PointerArray<double>& from, double* to) {
    }

};

#endif //QWNEURAL_H
