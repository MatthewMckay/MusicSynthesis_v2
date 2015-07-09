//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_STAFFDEFINITION_H
#define MUSICSYNTHESIS_V2_STAFFDEFINITION_H

#include <vector>
#include <string>
#include <iostream>

#include "../Constants.h"

class StaffDefinition_T {
    friend class Processing_T;
    friend class ScoreDefinition_T;
private:
    StrV_T defaultAccidentals;
    std::string keySig;
    std::string label;
    std::string n;
    friend std::ostream& operator<< (std::ostream& ostr, const StaffDefinition_T&sd){
        ostr << "STAFF DEFINITION:  N = " << sd.n;
        ostr << "  LABEL = " << sd.label;
        ostr << "  KEY SIG = " << sd.keySig;
        ostr << "  DEFAULT ACCIDS =";
        char pname = 'A';
        for (auto it = sd.defaultAccidentals.begin(); it != sd.defaultAccidentals.end(); ++it){
            ostr << " " << pname << ": " << *it;
            pname++;
        }
        ostr << "\n";
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_STAFFDEFINITION_H
