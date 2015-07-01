//
// Created by Matthew McKay on 6/30/15.
//

#ifndef MUSICSYNTHESIS_V2_CONSTANTS_H
#define MUSICSYNTHESIS_V2_CONSTANTS_H
#include <string>
#include <vector>

const int FRAGMENT_LENGTH = 3;

/**
 * NOTE: E# == Fn  && B# == Cn  Fb == En && Cb == B
 */

/**
 * The music fifths dictates that certain pitch names will have accidentals depending on the key signature
 * Each 'n', 's', and 'f' indicates the default accidental for each pitch (string[0] = 'a' through 'g') in
 * each key signature SF0 - F7.
 */
//                          a   b   c   d   e   f   g
const std::string SF0[] = {"n","n","n","n","n","n","n"};
const std::string S1[]  = {"n","n","n","n","n","s","n"};
const std::string S2[]  = {"n","n","s","n","n","s","n"};
const std::string S3[]  = {"n","n","s","n","n","s","s"};
const std::string S4[]  = {"n","n","s","s","n","s","s"};
const std::string S5[]  = {"s","n","s","s","n","s","s"};
const std::string S6[]  = {"s","n","s","s","s","s","s"};
const std::string S7[]  = {"s","s","s","s","s","s","s"};
const std::string F1[]  = {"n","f","n","n","n","n","n"};
const std::string F2[]  = {"n","f","n","n","f","n","n"};
const std::string F3[]  = {"f","f","n","n","f","n","n"};
const std::string F4[]  = {"f","f","n","f","f","n","n"};
const std::string F5[]  = {"f","f","n","f","f","n","f"};
const std::string F6[]  = {"f","f","f","f","f","n","f"};
const std::string F7[]  = {"f","f","f","f","f","f","f"};
const std::string * SHARPS[] = {S1,S2,S3,S4,S5,S6,S7};
const std::string * FLATS[]  = {F1,F2,F3,F4,F5,F6,F7};

const std::string PROGRESSION = "fcgdaeb";

std::vector<std::string> GetKeySig (const std::string value) {
                                        //A   B   C   D   E   F   G
    std::vector<std::string> defaults = {"n","n","n","n","n","n","n"};
    //get the number of sharps or flats
    std::string number = value.substr(0, 1);
    int n = std::stoi(number);
    if (n == 0) return defaults;
    else {
        //determine if there are sharps, double sharps, flats, or double flats
        const std::string type = value.substr(1);
        //if there are doubles then there will not be any naturals
        if (type.size() > 1) {
            if (type[0] == 's'){
                for (int i = 0; i < n; i++) defaults[PROGRESSION[i]-'a'] = type;
                for (int i = n; i < PROGRESSION.size(); i++) defaults[PROGRESSION[i]-'a'] = type[0];
            }
            else {
                for (int i = PROGRESSION.size() - 1; i >= PROGRESSION.size() - n; i--){
                    defaults[PROGRESSION[i]-'a'] = type;
                }
                for (int i = n - 1; i >= 0; i--) defaults[PROGRESSION[i]-'a'] = type[0];
            }
        }
        else {
            if (type[0] == 's'){
                for (int i = 0; i < n; i++) defaults[PROGRESSION[i]-'a'] = type;
            }
            else {
                for (int i = PROGRESSION.size() - 1; i >= PROGRESSION.size() - n; i--){
                    defaults[PROGRESSION[i]-'a'] = type;
                }
            }
        }
        return defaults;
    }
}




#endif //MUSICSYNTHESIS_V2_CONSTANTS_H
