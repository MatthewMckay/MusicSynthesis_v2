//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_STAFF_H
#define MUSICSYNTHESIS_V2_STAFF_H

#include <vector>
#include <string>
#include <iostream>

#include "Layer.h"

/**
 * Staff_T holds a group of layers
 * needed to retrieve default accidentals for notes from coressponding staff definitions
 */
class Staff_T {
    //to make code more readable Processing_T is friended
    friend class Processing_T;
private:
    std::vector<Layer_T> layers;    //holds the layers
    std::string n;                  //holds the name of the coressponding staff definition

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
