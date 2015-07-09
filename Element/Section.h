//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_SECTION_H
#define MUSICSYNTHESIS_V2_SECTION_H

#include <vector>
#include <string>
#include <iostream>

#include "Measure.h"

class Section_T {
    friend class Processing_T;
private:
    std::vector<Measure_T> measures;
    std::string n;
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
