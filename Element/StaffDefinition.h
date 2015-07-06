//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_STAFFDEFINITION_H
#define MUSICSYNTHESIS_V2_STAFFDEFINITION_H

#include <vector>
#include <string>

class StaffDefinition_T {
    friend class Processing_T;
    friend class ScoreDefinition_T;
private:
    std::vector<std::string> defaultAccidentals;
    std::string keySig;
    std::string label;
    std::string n;
};


#endif //MUSICSYNTHESIS_V2_STAFFDEFINITION_H
