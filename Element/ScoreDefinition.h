//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_SCOREDEFINITION_H
#define MUSICSYNTHESIS_V2_SCOREDEFINITION_H

#include <vector>
#include <string>

#include "StaffDefinition.h"

class ScoreDefinition_T {
    friend class Processing_T;
    friend class ScoreDefinition_T;
private:
    int meterCount;
    int meterUnit;
    std::string keySig;
    std::vector<std::string> defaultAccidentals;
    std::string keyMode;
    std::vector<StaffDefinition_T> staffGrp;
public:
    ScoreDefinition_T(){}
};


#endif //MUSICSYNTHESIS_V2_SCOREDEFINITION_H
