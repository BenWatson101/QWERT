#include <iostream>

#include "QWSAFE_ARRAYS.h"

int main() {

    auto k = QWERT::SizedArray<int, 100>();

    std::cout << sizeof(k);

    return 0;
}
