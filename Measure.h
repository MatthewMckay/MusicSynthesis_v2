//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_MEASURE_H
#define MUSICSYNTHESIS_V2_MEASURE_H

#include <iostream>
#include <vector>

#include "Duration.h"
#include "Note.h"
#include "Rest.h"

class Measure_T {
private:
    //keeps track of the order of notes and rests
    std::vector<Duration_T *> sequence;

public:
    Measure_T(){};
    ~Measure_T();
    void AddElement(Duration_T * element);
};


#endif //MUSICSYNTHESIS_V2_MEASURE_H
