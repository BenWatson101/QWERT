cmake_minimum_required(VERSION 3.29)
project(gitQWERT)

set(CMAKE_CXX_STANDARD 20)

add_executable(gitQWERT main.cpp
        Arrays/QWARRAYS.h
        QWERT.h
        Math/QWMATH.h
        Arrays/QWSAFE_ARRAYS.h
        Misc/QWLINEAR_MAP.h
        LinkedList/QWLINKEDLIST.h
        Math/QWMATHINTERFACES.h
        LinkedList/QWLINKEDNODE.h
)
