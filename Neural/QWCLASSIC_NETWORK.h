//
// Created by bwats on 2024-10-15.
//

#ifndef QWCLASSIC_NETWORK_H
#define QWCLASSIC_NETWORK_H
#include "../Arrays/QWARRAYS.h"
#include "../Math/QWMATH.h"

namespace QWERT {

    template<
        typename weightOperator,
        typename squeezeFunction,
        typename commutator
        >
    class HomogenousNetwork {
        static_assert(std::is_base_of_v<Operator, weightOperator>,
        "The weight operator must be derived from the Operator class");

        static_assert(std::is_base_of_v<Function, squeezeFunction>,
        "The squeeze function must be derived from the Function class");

        static_assert(std::is_base_of_v<GroupCommutator, commutator>,
        "The commutator must be derived from the GroupCommutator class");

        PointerArray<unsigned long long> layers;
        PointerArray<double> vector;

        unsigned long long inputSize = 0;

        PointerArray<double> out1;
        PointerArray<double> out2;

        PointerArray<double> processor;

        void processNode(PointerArray<double>& a, const double* b, const unsigned long long size, double* out) {
            processor.resize(size + 1);
            for(unsigned long long i = 0; i < size; i++) {
                processor.set(i, weightOperator::g(a.get(i), b[i]));
            }
            processor.set(size, b[size]);

            *out = squeezeFunction::f(commutator::h(processor));
        }

    public:
        HomogenousNetwork(const unsigned long long inputSize,
        const std::initializer_list<unsigned long long> layers) {
            unsigned long long k = 0;
            unsigned long size = 0;
            unsigned long long prevSize = 0;
            unsigned long long max = 0;
            this->inputSize = inputSize;

            for(const auto i: layers) {
                if(k == 0) {
                    size+= i * (inputSize + 1);
                } else {
                    size+= i * (prevSize + 1);
                }

                this->layers.set(k, i);

                if(i > max) {
                    max = i;
                }

                prevSize = i;
                k++;
            }

            vector = PointerArray<double>(size);
            out1 = PointerArray<double>(max);
            out2 = PointerArray<double>(max);
            processor = PointerArray<double>(max);
        }

        PointerArray<double> push(PointerArray<double>& data) {
            const double* vecPointer = vector.getP(0);
            unsigned long long prevSize = 0;

            memcpy(out1.getP(0), data.getP(0), sizeof(double) * data.getSize());

            bool toOut2 = true;

            for(unsigned long long layerN = 0; layerN < layers.getSize(); layerN++) {
                const unsigned long long layerSize = layers.get(layerN);
                unsigned long long nodeSize;

                if(layerN == 0) {
                    nodeSize = inputSize + 1;
                } else {
                    nodeSize = prevSize + 1;
                }

                for(unsigned long long nodeN = 0; nodeN < layerSize; nodeN++) {
                    if(toOut2) {
                        processNode(out1, vecPointer, nodeSize, out2.getP(nodeN));
                    } else {
                        processNode(out2, vecPointer, nodeSize, out1.getP(nodeN));
                    }
                    toOut2 = !toOut2;
                    vecPointer += nodeSize;
                }
                prevSize = layerSize;
            }

            if(toOut2) {
                return out1;
            }
            return out2;
        }

    };
}

#endif //QWCLASSIC_NETWORK_H
