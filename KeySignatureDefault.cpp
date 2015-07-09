//
// Created by Matthew McKay on 7/9/15.
//

#include "KeySignatureDefault.h"

const std::string KeySignatureDefault_T::PROGRESSION = "fcgdaeb";//order of increasing sharps, (its reverse for flats)

StrV_T KeySignatureDefault_T::GetKeySig (std::string value) const{
                             //A B C D E F G
    StrV_T defaults (7, "n");//0 1 2 3 4 5 6
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