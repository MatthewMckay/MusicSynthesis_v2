//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_SECTION_H
#define MUSICSYNTHESIS_V2_SECTION_H

#include <vector>
#include <string>

#include "Measure.h"

class Section_T {
    friend class Processing_T;
private:
    std::vector<Measure_T> measures;
    std::string n;
public:
    Section_T(){}
};


#endif //MUSICSYNTHESIS_V2_SECTION_H
