//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_SCOREDEFINITION_H
#define MUSICSYNTHESIS_V2_SCOREDEFINITION_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

#include "../Constants.h"
#include "../KeySignatureDefault.h"
#include "StaffDefinition.h"


/**
 * ScoreDefinition_T holds general information about a score that applies to the whole musical piece
 *      importantly - it holds the default key signature
 */
class ScoreDefinition_T : public KeySignatureDefault_T{
    //to make code more readable Processing_T is friended
    friend class Processing_T;
private:
    typedef std::unordered_map<std::string, StaffDefinition_T> strStfMap_T;
    int meterCount;             //how many beats
    int meterUnit;              //length of beat
    std::string keySig;         //i.e. "1s" = 1 sharp
    StrV_T defaultAccidentals;  //i.e. for C major keySig = "0" this would b (A"n" B"n" C"n" D"n" E"n" F"n" G"n")
    std::string keyMode;        //i.e. "major"
    strStfMap_T staffDefs;      //holds a set of staff definitions that possibly hold alternate key signatures

    //std::vector<StaffGroup_T> staffGrp;
public:
    //to ensure a value is in place for error checking these fields are initialized
    ScoreDefinition_T() : meterCount(0), meterUnit(0), keySig(""), keyMode("") {};

    friend std::ostream& operator<< (std::ostream& ostr, const ScoreDefinition_T& sd){
        ostr << "SCORE DEFINITION:  METER COUNT = " << sd.meterCount;
        ostr << "  METER UNIT = " << sd.meterUnit;
        ostr << "  KEY SIG = " << sd.keySig;
        ostr << "  DEFAULT ACCIDS =";
        char pname = 'A';
        for (auto it = sd.defaultAccidentals.begin(); it != sd.defaultAccidentals.end(); ++it){
            ostr << " " << pname << ":" << *it;
            pname++;
        }
        ostr << "  KEY MODE = " << sd.keyMode;
        ostr << "\n";
        for (auto i = sd.staffDefs.begin(); i != sd.staffDefs.end(); ++i) {
            ostr << i->first << ":" << i->second;
        }
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_SCOREDEFINITION_H
