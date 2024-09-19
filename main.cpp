#include <iostream>

#include "QWERT.h"
#include "QWMATH.h"
#include "QWSAFE_ARRAYS.h"



int main() {

    using namespace QWERT;

    auto k = QWERT::SafeSizedArray<int, 100>();

    auto g = range(10,20);

    auto l = range(0,10);

    l.g<Multiply>(g);

    std::cout << l;

    return 0;
}
