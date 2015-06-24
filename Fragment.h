//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_FRAGMENT_H
#define MUSICSYNTHESIS_V2_FRAGMENT_H
#include <iostream>
#include <vector>
#include <string>
#include <boost/any.hpp>

#include "XmlDomDocument.h"
#include "Note.h"
#include "Rest.h"
#include "Basis.h"

class FRAGMENT {
private:
    XmlDomDocument* doc;
    BASIS * basis;
    std::vector<NOTE> * noteSamples;
    std::vector<REST> * restSamples;

    //void GrabNotesAndRests();
public:
    FRAGMENT(const char* xmlFile);
    ~FRAGMENT(){delete noteSamples; delete restSamples; delete basis;}
};


#endif //MUSICSYNTHESIS_V2_FRAGMENT_H
