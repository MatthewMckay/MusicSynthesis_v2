//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_SECTION_H
#define MUSICSYNTHESIS_V2_SECTION_H

#include <vector>
#include <string>
#include <iostream>

#include "Measure.h"

/**
 * Section_T divides music into different parts
 * music is divided into sections that may have different music qualities
 */
class Section_T {
    //to make code more readable Processing_T is friended
    friend class Processing_T;
private:
    std::vector<Measure_T> measures;    //holds relevant measures
    std::string n;                      //not used at this this time
public:
    Section_T(){}
    friend std::ostream& operator<< (std::ostream& ostr, const Section_T& section){
        ostr << "SECTION:  n = ";
        if (section.n.empty()) ostr << "UNDEFINED\n";
        else ostr << section.n << '\n';
        for (auto it = section.measures.begin(); it != section.measures.end(); ++it){
            ostr << *it;
        }
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_SECTION_H
