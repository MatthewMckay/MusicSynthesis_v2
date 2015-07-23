//
// Created by Matthew McKay on 7/9/15.
//

#ifndef MUSICSYNTHESIS_V2_KEYSIGNATUREDEFAULT_H
#define MUSICSYNTHESIS_V2_KEYSIGNATUREDEFAULT_H


#include "Constants.h"
/**
* The music fifths dictates that certain pitch names will have accidentals depending on the key signature
* Each 'n', 's', and 'f' indicates the default accidental for each pitch (string[0] = 'a' through 'g') in
* each key signature SF0 - F7.
*/
class KeySignatureDefault_T {
protected:
    friend class Processing_T;
    static const std::string PROGRESSION; //order of increasing sharps, (its reverse for flats)
    StrV_T GetKeySig (std::string value) const;
};

//an octave is from pitch to same pitch abcdefg a   bcdefga b etc

#endif //MUSICSYNTHESIS_V2_KEYSIGNATUREDEFAULT_H
