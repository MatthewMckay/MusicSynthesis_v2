//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_MEASURE_H
#define MUSICSYNTHESIS_V2_MEASURE_H

#include <iostream>
#include <vector>
#include <string>

#include "Staff.h"

class Measure_T {
    friend class Processing_T;
private:
    std::vector<Staff_T> staffs;
    std::string n;
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
