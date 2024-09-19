//
// Created by bwats on 2024-09-19.
//

#ifndef QWLINEAR_MAP_H
#define QWLINEAR_MAP_H
#include "QWLINKEDLIST.h"

namespace QWERT {
    template<typename a, typename b>
    struct Pair {
        //l is left, r is right
        a l;
        b r;
    };

    //WIP, not to be confused with EHashMap
    template<template<typename, typename> class T, typename A, typename B>
    class LinearHashMap {
        LinkedList<T<A,B>> pairs;

        void forceAdd(T<A,B>& in) {
            pairs.add(in);
        }
    };
}

#endif //QWLINEAR_MAP_H
