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

#include "XmlDomDocument_T.h"

#include "Constants.h"

#include "Element/Music.h"
#include "Element/ScoreDefinition.h"
#include "Element/StaffDefinition.h"
#include "Element/Section.h"
#include "Element/Measure.h"
#include "Element/Staff.h"
#include "Element/Layer.h"

#include "Duration/Duration.h"
#include "Duration/Chord.h"
#include "Duration/Note.h"
#include "Duration/Rest.h"
#include "Duration/MeasureRest.h"
#include "Duration/MeasureSpace.h"
#include "Duration/MultiMeasureRest_T.h"
//staffGrp not implemented
//music is queried explicitly
#define TAGS "scoreDef","staffDef","section","measure","staff","layer","chord","note","rest","mRest","mSpace","multiRest"
#define SCOREDEFATTS “meter.count”,”meter.unit”,”key.sig”,”key.mode”
#define STAFFDEFATTS “key.sig”,”label”,”n”
#define SECTATTS "n"
#define MEASATTS "n"
#define STAFFATTS "n"
#define LAYERATTS "n"
#define CHORDATTS “dur”,”accid”,”dots"
#define NOTEATTS “pname”,”accid”,”oct”,”dur”,”dots”
#define RESTATTS "dur"
#define MULTIRESTATTS "num"

class Processing_T {
    typedef void funcPtr_T();
    typedef std::map<const std::string, funcPtr_T*> strFuncMap_T;
    typedef const std::set<const std::string> strSet_T;
private:
    const std::set<const std::string> tags;
    strFuncMap_T functionMap;
    XmlDomDocument_T * doc;
    std::stack<Music_T> music;
    int musicIndex;
#define GEA(str) doc->GetElementAttribute(str)
#define GEA_E(str) doc->GetElementAttribute(str).empty()
#define MT music.top()
#define SEB sections.back()
#define MB measure.back()
#define SB staff.back()
#define LB layers.back()
#define SQB sequence.back()
#define NB notes.back()
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
    Note_T AddChordNote(TimeFraction_T &dur);
    void CreateNote();
    void CreateRest();
    void CreateMRest();
    void CreateMSpace();
    void CreateMultiRest();
};


#endif //MUSICSYNTHESIS_V2_PROCESSING_H
