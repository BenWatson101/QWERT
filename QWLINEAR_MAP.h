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
    class LinearMap {
        LinkedList<T<A,B>> pairs;

        T<A,B>* temp = nullptr;

        LinearMap() = default;

        void forceAdd(T<A,B>& in) {
            pairs.add(in);
        }

        bool add(T<A,B>& in) {
            if(!this->in(in.l)) {
                pairs.add(in);
                return true;
            }
            return false;
        }

        bool in(A& find) {
            for(auto i: pairs) {
                if(i.l == find) {
                    temp = &i;
                    return true;
                }
            }
            return false;
        }

        A& recent() {
            if(temp != nullptr) {
                return temp->l;
            }
            return A();
        }

        T<A,B>& recentPair() {
            if(temp != nullptr) {
                return *temp;
            }
            return T<A,B>();
        }

        void resetRecent() {
            temp = nullptr;
        }
    };
}

#endif //QWLINEAR_MAP_H
