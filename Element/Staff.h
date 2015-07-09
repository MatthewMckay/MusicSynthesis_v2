//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_STAFF_H
#define MUSICSYNTHESIS_V2_STAFF_H

#include <vector>
#include <string>
#include <iostream>

#include "Layer.h"

class Staff_T {
    friend class Processing_T;
private:
    std::vector<Layer_T> layers;
    std::string n;
public:
    friend std::ostream& operator<< (std::ostream& ostr, const Staff_T& staff){
        ostr << "\tSTAFF:  n = ";
        if (staff.n.empty()) ostr << "UNDEFINED";
        else ostr << staff.n << '\n';
        for (auto it = staff.layers.begin(); it != staff.layers.end(); ++it){
            ostr << *it;
        }
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_STAFF_H
