//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_MEASURE_H
#define MUSICSYNTHESIS_V2_MEASURE_H

#include <iostream>
#include <vector>
#include <string>

#include <Staff.h>

class Measure_T {
    friend class Music_T;
private:
    std::vector<Staff_T> staffs;
    std::string n;
};


#endif //MUSICSYNTHESIS_V2_MEASURE_H
