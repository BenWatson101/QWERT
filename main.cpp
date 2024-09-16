#include <iostream>

#include "QWSAFE_ARRAYS.h"

int main() {

    auto k = QWERT::SafeSizedArray<int, 100>();

    std::cout << sizeof(k);

    return 0;
}
