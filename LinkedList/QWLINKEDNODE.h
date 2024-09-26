//
// Created by bwats on 2024-08-22.
//

#ifndef QWNODE_H
#define QWNODE_H

namespace QWERT {

    template<typename type>
    struct Node {

        type data = type();
        Node *p = nullptr;

        Node() = default;
        Node(type data, Node* ptr) : data(data), p(ptr) {}

         ~Node() {
            delete p;
         }

        Node* getNode(const size_t to, const size_t from) {
            if(from == to) {
                return this;
            }
            return p->getNode(to, from + 1);
        }

        type get(const size_t to, const size_t from) {
            return getNode(to, from)->data;
        }

        void set(const size_t to, const size_t from, type thing) {
            getNode(to, from)->data = thing;
        }

    };

}

#endif //QWNODE_H
