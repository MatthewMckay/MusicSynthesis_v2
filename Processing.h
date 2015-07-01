//
// Created by Matthew McKay on 6/24/15.
//

#ifndef MUSICSYNTHESIS_V2_PROCESSING_H
#define MUSICSYNTHESIS_V2_PROCESSING_H
#include <iostream>
#include <vector>
#include <string>

#include "XmlDomDocument_T.h"


class Processing {
private:
    XmlDomDocument_T * doc;//parsed xml file (takes an Xml file name for initialization
    std::vector<int> scoreDef;
    std::vector<int> staffDef;
    std::vector<int> measure;
    std::vector<int> note;
};


#endif //MUSICSYNTHESIS_V2_PROCESSING_H
