//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_SCOREDEFINITION_H
#define MUSICSYNTHESIS_V2_SCOREDEFINITION_H

#include <vector>
#include <unordered_map>
#include <string>

#include "StaffDefinition.h"

typedef std::unordered_map<std::string, StaffDefinition_T>::iterator strStfMapIt_T;

class ScoreDefinition_T {
    friend class Processing_T;
    friend class ScoreDefinition_T;
private:
    typedef std::unordered_map<std::string, StaffDefinition_T> strStfMap_T;
    int meterCount;
    int meterUnit;
    std::string keySig;
    std::vector<std::string> defaultAccidentals;
    std::string keyMode;
    strStfMap_T staffDefs;

    //std::vector<StaffGroup_T> staffGrp;
public:
    ScoreDefinition_T(){}
};


#endif //MUSICSYNTHESIS_V2_SCOREDEFINITION_H
