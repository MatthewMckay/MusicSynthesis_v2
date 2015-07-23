//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_STAFFDEFINITION_H
#define MUSICSYNTHESIS_V2_STAFFDEFINITION_H

#include <vector>
#include <string>
#include <iostream>

#include "../Constants.h"
#include "../KeySignature.h"

/**
 * StaffDefinition_T holds general information about a staff that applies to the whole musical piece
 *      importantly - it holds the default key signature for the staff
 */
class StaffDefinition_T {//: public KeySignatureDefault_T{
    //to make code more readable Processing_T is friended
    friend class Processing_T;
private:
    KeySignature_T keySignature;
    StrV_T defaultAccidentals;  //i.e. for C major keySig = "0" this would b (A"n" B"n" C"n" D"n" E"n" F"n" G"n")
    std::string keySig;         //i.e. "1s" = 1 sharp
    std::string keyMode;
    std::string label;          //usually used to indicate the use case for the staff
    std::string n;              //needs to be the name of the definition (used to insert in the defintion map) and to
                                //      refer back to this definition from a corresponding staff

public:
    void SetKeySignature(){
        KeySignature_T newKeySig(keySig, keyMode);
        keySignature = newKeySig;
    }
    const StrV_T GetKeySig() { return keySignature.GetKeySig(); }
    friend std::ostream& operator<< (std::ostream& ostr, const StaffDefinition_T&sd){
        ostr << "STAFF DEFINITION:  N = " << sd.n;
        ostr << "  LABEL = " << sd.label;
        ostr << "  KEY SIG = " << sd.keySig;
        ostr << "  DEFAULT ACCIDS =";
        char pname = 'A';
        for (auto it = sd.defaultAccidentals.begin(); it != sd.defaultAccidentals.end(); ++it){
            ostr << " " << pname << ":" << *it;
            pname++;
        }
        ostr << "\n";
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_STAFFDEFINITION_H
