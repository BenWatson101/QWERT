//
// Created by bwats on 2024-08-14.
//

#ifndef QWERT_H
#define QWERT_H
#include <chrono>
#include <iostream>
#include <thread>

#include "QWARRAYS.h"

//Quick Working Enterprise Tools
namespace QWERT {

    inline unsigned long version = 0;

    inline void isAwesome() {
        std::cout << "Yes, QWERT is awesome and cool!\n";
    }

    template<typename type>
    void swap(type *a, type *b) {
        type temp = *b;
        *b = *a;
        *a = temp;
    }

    template<typename T>
    T* array(std::initializer_list<T> initList) {
        T* arr = new T[initList.size()];
        size_t index = 0;
        for(auto i: initList) {
            arr[index] = i;
            index++;
        }
        return arr;
    }

    template <typename... Args>
    std::string concat(Args... args) {
        std::ostringstream oss;
        (oss << ... << args);
        return oss.str();
    }

    inline std::string input() {
        std::string temp;
        std::cin >> temp;
        return temp;
    }

    inline std::string input(const std::string& message) {
        std::cout << message;
        return input();
    }

    inline PointerArray<long long> range(long long a, long long b) {
        if(a > b) {
            swap(&a, &b);
        }
        auto arr = PointerArray<long long>(b - a);
        auto p = arr.getP(0);
        for(long long i = a; i < b; i++) {
            *p = i;
            p++;
        }
        return arr;
    }

    inline PointerArray<long long> range(const long long l) {
        return range(0, l);
    }


    inline void sleep(const long long milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    struct Timer final {

        std::chrono::time_point<std::chrono::system_clock> s;
        std::chrono::time_point<std::chrono::system_clock> e;

        Timer& start() {
            s = std::chrono::high_resolution_clock::now();
            //for one-liners
            return *this;
        }

        void end() {
            e = std::chrono::high_resolution_clock::now();
        }

        //returns in microseconds
        [[nodiscard]] long long result() const {
            return std::chrono::duration_cast<std::chrono::microseconds>(e - s).count();
        }
    };

}



#endif //QWERT_H
