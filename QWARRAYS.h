//
// Created by bwats on 2024-08-23.
//

#ifndef QWARRAYS_H
#define QWARRAYS_H
#include <sstream>

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

    void set(size_t index, type to){
        arr[index] = to;
    }

    type& get(size_t index) {
        return arr[index];
    }

    type* getP(size_t index) const {
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
