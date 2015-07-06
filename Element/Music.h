//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_MUSIC_H
#define MUSICSYNTHESIS_V2_MUSIC_H

#include <vector>

#include "ScoreDefinition.h"
#include "Section.h"

class Music_T {
friend class Processing_T;
private:
    ScoreDefinition_T scoreDef;
    std::vector<Section_T> sections;
public:
    Music_T(){}
};


#endif //MUSICSYNTHESIS_V2_MUSIC_H
