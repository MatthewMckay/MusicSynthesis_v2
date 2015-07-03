//
// Created by Matthew McKay on 6/24/15.
//

#ifndef MUSICSYNTHESIS_V2_PROCESSING_H
#define MUSICSYNTHESIS_V2_PROCESSING_H
#include <iostream>
#include <vector>
#include <string>

#include "XmlDomDocument_T.h"

/**
 * parses all files
 * todo 1 - input all files
 * todo 2 - if file was just parsed, delete the XML doc
 * todo 3 - pull all data in the music elements
 */
class Processing {
private:
    std::vector<const char *> files;
    XmlDomDocument_T * doc;//parsed xml file (takes an Xml file name for initialization
    std::vector<int> musics;
    std::vector<int> scoreDefs;
    std::vector<int> staffDefs;
    std::vector<int> sections;
    std::vector<int> measures;
    std::vector<int> staffs;
    std::vector<int> layers;
    std::vector<int> chords;
    std::vector<int> notes;
    std::vector<int> rests;
    std::vector<int> mRests;
    std::vector<int> multiRests;
    std::vector<int> mSpaces;
};


#endif //MUSICSYNTHESIS_V2_PROCESSING_H
