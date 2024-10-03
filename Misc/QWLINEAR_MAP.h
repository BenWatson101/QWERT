//
// Created by bwats on 2024-09-19.
//

#ifndef QWLINEAR_MAP_H
#define QWLINEAR_MAP_H
#include "../LinkedList/QWLINKEDLIST.h"

namespace QWERT {
    template<typename a, typename b>
    struct Pair {
        //l is left, r is right
        a l;
        b r;
    };

    //WIP, not to be confused with EHashMap
    template<typename A, typename B>
    class LinearMap {
        LinkedList<Pair<A,B>> pairs;

        Pair<A,B>* temp = nullptr;

        LinearMap() = default;

        void forceAdd(Pair<A,B>& in) {
            pairs.add(in);
        }

        bool add(Pair<A,B>& in) {
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

        Pair<A,B>& recentPair() {
            if(temp != nullptr) {
                return *temp;
            }
            return Pair<A,B>();
        }

        void resetRecent() {
            temp = nullptr;
        }

        // ReSharper disable once CppMemberFunctionMayBeStatic
        [[nodiscard]] bool isSurjective() const {
            return true;
        }

        [[nodiscard]] bool isInjective() const {
            for(auto h = pairs.begin(); h != pairs.end();) {
                auto temp = (*h).r;
                ++h;
                for(auto k = h; k != pairs.end(); ++k) {
                    if((*k).r == temp) {
                        return false;
                    }
                }

            }

            return true;
        }

        [[nodiscard]] bool isBijective() const {
            return isInjective() && isSurjective();
        }
    };
}

#endif //QWLINEAR_MAP_H
