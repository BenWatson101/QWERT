//
// Created by bwats on 2024-08-23.
//

#ifndef QWARRAYS_H
#define QWARRAYS_H
#include <cstdint>
#include <sstream>

#include "QWMATHINTERFACES.h"

namespace QWERT {
//
//interface for arrays
//
template <typename type>
struct ArrayIterable {

    type *pointer = nullptr;

    explicit ArrayIterable(type* pointer) : pointer(pointer) {}

    type & operator*() {
        return *pointer;
    }

    ArrayIterable & operator++() {
        ++pointer;
        return *this;
    }


    bool operator!=(const ArrayIterable &other) {
        return pointer != other.pointer;
    }
};

template<typename arrayType, typename type>
class ArrayTemplate {
protected:
    arrayType arr;
public:
    virtual ~ArrayTemplate() = default;

    virtual size_t getSize() = 0;

    virtual void set(const size_t index, type to){
        arr[index] = to;
    }

    virtual type& get(const size_t index) {
        return arr[index];
    }

    virtual type* getP(const size_t index) {
        return arr + index;
    }

    //depricated
    template<typename T>
    void byteCopy(T& thing) {
        auto e = new uint8_t(sizeof(T));
        memcpy(e, &thing, sizeof(T));

        for(unsigned long long i = 0; i < sizeof(T); i++) {
            memcpy(getP(i), e, 1);
            ++e;
        }
    }

    ArrayIterable<type> begin() {
        return ArrayIterable<type>(arr);
    }

    ArrayIterable<type> end() {
        return ArrayIterable<type>(arr + getSize());
    }

    std::string toString() {
        std::ostringstream oss;
        oss << "[";
        size_t j = 0;
        for(type i: *this) {
            oss << i;
            if(j < getSize() - 1) {
                oss << ", ";
            } else {
                oss << "]";
            }
            j++;
        }
        return oss.str();
    }

    //
    //Array math
    //

    template<typename T>
    void ensureNumeric() const {
        static_assert(std::is_arithmetic_v<T>, "Template argument must be a numeric type");
    }

    template<typename base, typename derived>
    void checkInheritance() const {
        static_assert(std::is_base_of_v<base, derived>, "T must derive from Base");
    }

    template<typename function>
    ArrayTemplate& f() {
        ensureNumeric<type>();
        checkInheritance<Function, function>();
        for(auto &i: *this) {
            i = function::f(i);
        }
        return *this;
    }

    template<typename operate, typename type1, typename type2>
    ArrayTemplate& g(ArrayTemplate<type1, type2>& other) {

        ensureNumeric<type>();
        ensureNumeric<type2>();
        checkInheritance<Operator, operate>();
        if(this->getSize() != other.getSize()) {
            throw std::out_of_range("Sizes aren't matched for operation");
        }

        ArrayIterable<type> iterate = other.begin();

        for(auto &i: *this) {
            i = operate::g(i, *iterate);
            ++iterate;
        }
        return *this;
    }

    template<typename grouper>
    double h() {
        ensureNumeric<type>();
        checkInheritance<GroupCommutator, grouper>();
        return grouper::h(*this);
    }
};






//
//array implementation
//
template<typename type, size_t size>
class SizedArray : public ArrayTemplate<type[size], type>{
public:

    size_t getSize() override {
        return size;
    }
};

template<typename T, size_t size>
std::ostream& operator<<(std::ostream& os, SizedArray<T, size> &arr) {
    os << arr.toString();
    return os;
}


template<typename type>
class PointerArray : public ArrayTemplate<type*, type>{
protected:
    size_t size = 0;
public:
    PointerArray() {
        this->arr = nullptr;
    }

    ~PointerArray() override {
        delete[] (*this).arr;
    }

    explicit PointerArray(const size_t size) : size(size){
        this->arr = new type[size];
    }

    size_t getSize() override {
        return size;
    }

    PointerArray& operator=(const PointerArray& other) {
        if(this != &other) {
            delete[] this->arr;
            this->size = other.size;
            this->arr = new type[size];
            for(unsigned long long i = 0; i < size; i++) {
                this->arr[i] = other.arr[i];
            }
        }
        return *this;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, PointerArray<T> &arr) {
    os << arr.toString();
    return os;
}
}





#endif //QWARRAYS_H
