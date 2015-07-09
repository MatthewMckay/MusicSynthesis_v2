//
// Created by Matthew McKay on 6/24/15.
//

#ifndef MUSICSYNTHESIS_V2_PROCESSING_H
#define MUSICSYNTHESIS_V2_PROCESSING_H
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <stack>
#include <string>
#include <exception>
#include <cstdlib>

#include "Constants.h"
#include "Duration/Duration.h"
#include "Duration/Note.h"
#include "Duration/Chord.h"
#include "Duration/Rest.h"
#include "Duration/MeasureRest.h"
#include "Duration/MeasureSpace.h"
#include "Duration/MultiMeasureRest_T.h"
#include "Element/Layer.h"
#include "Element/Staff.h"
#include "Element/Measure.h"
#include "Element/Section.h"
#include "Element/StaffDefinition.h"
#include "Element/ScoreDefinition.h"
#include "Element/Music.h"

#include "XmlDomDocument_T.h"

//staffGrp not implemented
//music is queried explicitly
#define TAGS "scoreDef","staffDef","section","measure","staff","layer","chord","note","rest","mRest","mSpace","multiRest"


class Processing_T {
    typedef std::set<const std::string> strSet_T;
private:
    const static strSet_T tags;
    //strFuncMap_T functionMap;
    XmlDomDocument_T * doc;
    std::stack<Music_T> music;

    Processing_T(){};
public:
    Processing_T(std::vector<const char *> files);

    void BeginProcessing();
    void CreateMusic();
    void CreateScoreDef();
    //void CreateStaffGrp();
    void CreateStaffDef();
    void CreateSection();
    void CreateMeasure();
    void CreateStaff();
    void CreateLayer();
    void CreateChord();
    SHP(Note_T) AddChordNote(TimeFraction_T &dur, const int& i);
    void CreateNote();
    void CreateRest();
    void CreateMRest();
    void CreateMSpace();
    void CreateMultiRest();
    void PrintMusic(){ std::cout<<music.top()<<'\n'; }
private:
#define GEA(str) doc->GetElementAttribute(str)
#define GEA_E(str) doc->GetElementAttribute(str).empty()
#define MT music.top()
#define SEB sections.back()
#define MB measures.back()
#define SB staffs.back()
#define LB layers.back()
};


#endif //MUSICSYNTHESIS_V2_PROCESSING_H
