//
// Created by Matthew McKay on 6/22/15.
//

#include "Measure.h"

Measure_T::~Measure_T() {
    for ( auto it = sequence.begin(); it != sequence.end(); ++it) delete(*it);
}
//template <class T>
void Measure_T::AddElement(Duration_T * element) {
    sequence.push_back(element);
}