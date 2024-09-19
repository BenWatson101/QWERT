//
// Created by bwats on 2024-09-19.
//

#ifndef QWLINEAR_HASHMAP_H
#define QWLINEAR_HASHMAP_H

namespace QWERT {
    template<typename a, typename b>
    struct Pair {
        //l is left, r is right
        a l;
        b r;
    };

    //WIP, not to be confused with EHashMap
    template<typename a, typename b>
    template<Pair<a,b>>
    class LinearHashMap {

    };
}

#endif //QWLINEAR_HASHMAP_H
