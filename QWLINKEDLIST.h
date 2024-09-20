//
// Created by bwats on 2024-08-21.
//

#ifndef QWLINKEDLIST_H
#define QWLINKEDLIST_H
#include <sstream>
#include <stdexcept>
#include "QWERT.h"
#include "QWLINKEDNODE.h"

namespace QWERT {

//not to be confused with ELinkedList
template<typename type>
    class LinkedList
    {
    protected:

    class LinkedListIterableObject final {
    protected:
        Node<type>* pointer = nullptr;
        size_t counter = 0;
    public:
        explicit LinkedListIterableObject(Node<type>* pointer, const size_t index) : pointer(pointer), counter(index) {}

        type & operator*() {
            return pointer->data;
        }

        LinkedListIterableObject & operator++() {
            pointer = pointer->p;
            counter++;
            return *this;
        }

        bool operator!=(const LinkedListIterableObject &other) {
            return pointer != other.pointer &&  counter < other.counter;
        }
    };

    Node<type> start;
    Node<type> *last = &start;
    size_t size = 0;
    size_t sizeAndFizz = 0;

    public:
    LinkedList() = default;

    LinkedList(std::initializer_list<type> initList) {
        alloc(initList.size());
        for(type i : initList) {
            add(i);
        }
    }

    [[nodiscard]] size_t getSize() const {
        return this->size;
    };

    type get(size_t index) {
        if(index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return start.get(index, 0);
    }

    void set(size_t index, type to) {
        if(index >= size) {
            throw std::out_of_range("Index out of range");
        }
        last.set(index, 0, to);
    }

    void add(type thing) {
        if(size == 0) {
            if(start.p == nullptr) {
                start = Node<type>(thing, nullptr);
            } else {
                start.data = thing;
            }
            last = &start;
            size = 1 ;
            sizeAndFizz = 1;
        } else {
            if(last->p == nullptr) {
                last->p = new Node<type>(thing, nullptr);
                //std::cout << "actually alocated new space\n";
            } else {
                last->p->data = thing;
            }
            last = last->p;
            size++;
            sizeAndFizz++;
        }
    }

    //*untested*
    void remove(size_t const index) {
        remove(index, index);
    }

    //*untested* welcome to hell, by hell, lets just say a trillion if statements, will break because of alloc
    void remove(size_t from, size_t to) {
        if(from >= this->size || to >= this->size) {
            throw std::out_of_range("Index of range");
        }
        if(this->size == 1) {
            start = Node<type>();
        } else if(from > to) {
            swap(&from, &to);
        } else {
            if(from == 0 && to == this->sizeAndFizz - 1) {
                delete start.p;
                start = Node<type>();
                last = &start;
            } else if(from != 0 && to == this->sizeAndFizz - 1) {
                delete start.getNode(from - 1, 0)->p;
            } else if(from == 0 && to != this->sizeAndFizz - 1) {
                //std::cout << "case 3";
                Node<type> *temp = start.getNode(to + 1, 0);
                //std::cout << "past 1";
                start.getNode(to, 0)->p = nullptr;
                //std::cout << "past 2";
                //im too tired to debux this

                delete start.p;
                //std::cout << "past 3";
                start = *temp;
            } else {
                Node<type> *temp = start.getNode(to + 1, 0);
                start.getNode(to, 0)->p = nullptr;
                delete start.getNode(from - 1, 0)->p;
                start.getNode(from - 1, 0)->p = temp;
            }
        }
        size -= to - from + 1;
        sizeAndFizz -= to - from + 1;
    }

    LinkedListIterableObject begin() {
        return LinkedListIterableObject(&start, 0);
    }

    LinkedListIterableObject end() {
        return LinkedListIterableObject(nullptr, size);
    }

    //returns a string of the array in array format: [1, 2, 3]
    std::string toString() {
        if(size == 0) {
            return "[]";
        }

        std::ostringstream oss;
        oss << "[";
        size_t j = 0;
        for(type i : *this) {
            if(j < size - 1) {
                oss << i << ", ";
            } else {
                oss << i;
            }
            j++;
        }
        oss << "]";
        return oss.str();
    }



    };

    template<typename T>
        std::ostream& operator<<(std::ostream& os, LinkedList<T> &list) {
        os << list.toString();
        return os;
    }



} // QWERT

#endif //QWLINKEDLIST_H
