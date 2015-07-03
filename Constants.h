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

const std::string PROGRESSION = "fcgdaeb";//order of increasing sharps, (its reverse for flats)

/**
 * takes in a KeySig value and returns a vector of default accidental values
 */
std::vector<std::string> GetKeySig (const std::string value) {
                                               //A B C D E F G
    std::vector<std::string> defaults (7, "n");//0 1 2 3 4 5 6
    //get the number of sharps or flats
    std::string number = value.substr(0, 1);
    int n = std::stoi(number);
    if (n == 0) return defaults;
    else {
        //determine if there are sharps, double sharps, flats, or double flats
        const std::string type = value.substr(1);
        //if there are doubles then there will not be any naturals
        if (type.size() > 1) {
                //double sharps
            if (type[0] == 's'){
                for (int i = 0; i < n; i++) defaults[PROGRESSION[i]-'a'] = type;
                for (int i = n; i < PROGRESSION.size(); i++) defaults[PROGRESSION[i]-'a'] = type[0];
            }
                //double flats
            else {
                for (int i = PROGRESSION.size() - 1; i >= PROGRESSION.size() - n; i--){
                    defaults[PROGRESSION[i]-'a'] = type;
                }
                for (int i = n - 1; i >= 0; i--) defaults[PROGRESSION[i]-'a'] = type[0];
            }
        }
        else {
                //sharps
            if (type[0] == 's'){
                for (int i = 0; i < n; i++) defaults[PROGRESSION[i]-'a'] = type;
            }
                //flats
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
