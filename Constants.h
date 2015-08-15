//
// Created by Matthew McKay on 6/30/15.
//

#ifndef MUSICSYNTHESIS_V2_CONSTANTS_H
#define MUSICSYNTHESIS_V2_CONSTANTS_H
#include <string>
#include <vector>
#include <cmath>
const std::string ERR_CLRS = "\033[1;48;5;228;38;5;202m";
const std::string DFLT_CLRS = "\033[0m";
const int FRAGMENT_LENGTH = 3;
const int MAX_ID_BIT_LENGTH = 13;
                                                               //P A Do O Du Nu De
const int MAX_BIT_STRNG_LENGTH = 468; // (13 * 240 = 3120) log2(7*3*3*10*10+10_10) * 60BPM/60S * 12S * 3
typedef std::vector<std::string> StrV_T;
typedef std::pair<int,bool> IntBool_T;
#define SHP_T(x) std::shared_ptr<x>
#define SPC_(x) std::static_pointer_cast<x>


#endif //MUSICSYNTHESIS_V2_CONSTANTS_H
