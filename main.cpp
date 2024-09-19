#include <iostream>

#include "QWERT.h"
#include "QWLINKEDLIST.h"
#include "QWMATH.h"
#include "QWSAFE_ARRAYS.h"



int main() {

    using namespace QWERT;

    auto b = LinkedList<int>();

    for(int i = 0; i < 10; i++) {
        b.add(i);
    }

    return 0;
}
