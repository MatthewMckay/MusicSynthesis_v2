//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_MEASURE_H
#define MUSICSYNTHESIS_V2_MEASURE_H

#include <iostream>
#include <vector>
#include <string>

#include "Staff.h"

/**
 * Measure_T divides music into pieces by a certain number of beats
 * each measure can contain many staffs
 */
class Measure_T {
    //used to make code more readable
    friend class Processing_T;
private:
    std::vector<Staff_T> staffs;    //holds a group of staffs
    std::string n;                  //not used at this time
public:
    friend std::ostream& operator<< (std::ostream& ostr, const Measure_T& measure){
        ostr << "  MEASURE:  n = ";
        if (measure.n.empty()) ostr << "UNDEFINED\n";
        else ostr << measure.n << '\n';
        for (auto it = measure.staffs.begin(); it != measure.staffs.end(); ++it){
            ostr << *it;
        }
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_MEASURE_H
