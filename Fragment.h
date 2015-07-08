//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_FRAGMENT_H
#define MUSICSYNTHESIS_V2_FRAGMENT_H
#include <iostream>
#include <vector>
#include <string>

#include "XmlDomDocument_T.h"
#include "Duration/Note.h"
#include "Duration/Rest.h"
#include "Basis.h"

class Fragment_T {
private:
    XmlDomDocument_T * doc;
    BASIS * basis;
    std::vector<Note_T> * noteSamples;
    std::vector<Rest_T> * restSamples;

    //void GrabNotesAndRests();
public:
    Fragment_T(const char* xmlFile);
    ~Fragment_T(){delete noteSamples; delete restSamples; delete basis;}
};


#endif //MUSICSYNTHESIS_V2_FRAGMENT_H
