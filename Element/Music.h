//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_MUSIC_H
#define MUSICSYNTHESIS_V2_MUSIC_H

#include <iostream>
#include <vector>

#include "ScoreDefinition.h"
#include "Section.h"

/**
 * Music object stores its score definition and vector of all the sections
 */
class Music_T {
//to make code more readable Processing_T is friended
friend class Processing_T;
private:
    ScoreDefinition_T scoreDef;
    std::vector<Section_T> sections;
public:
    Music_T(){}
    friend std::ostream& operator<< (std::ostream& ostr, const Music_T& music){
        ostr << "MUSIC:\n";
        ostr << music.scoreDef;
        //print off all the sections
        for (auto it = music.sections.begin(); it != music.sections.end(); ++it){
            ostr << *it;
        }
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_MUSIC_H
