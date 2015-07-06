//
// Created by Matthew McKay on 6/24/15.
//

#ifndef MUSICSYNTHESIS_V2_PROCESSING_H
#define MUSICSYNTHESIS_V2_PROCESSING_H
#include <iostream>
#include <vector>
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

/**
 * parses all files
 * todo 1 - input all files
 * todo 2 - if file was just parsed, delete the XML doc
 * todo 3 - pull all data in the music elements
 */

/**
 * Assumed: each file contains only one music element
 * each music has a scoreDef and sections
 *  each scoreDef has a staffGrp and atts(meter.count, meter.unit, key.sig, and key.mode) need error catches otherwise
 *      each staffGrp has staffDefs
 *          each staffDef may have atts(key.sig, label n)
 *          (all elements with keysig atts will hold a default pitch string)
 *  each section has measures and may have att(n)
 *      each measure has staff(s)
 *          each staff has layer(s) and may have att(n)
 *              each layer has notes and rests and may have att(n)
 */
const int INDECIES = 8;
typedef std::vector<std::pair<int,int>> Counts_T;
class Processing_T {
private:
    XmlDomDocument_T * doc;
    std::vector<Music_T> music;
    std::vector<int> i;
    Counts_T I;
public:
    Processing_T(std::vector<const char *> f) {
        for (int k = 0; k < INDECIES; k++) i.push_back(0);
        for (auto it = f.begin(); it != f.end(); ++it){
            doc = new XmlDomDocument_T(*it);
            for (int k = 0; k < INDECIES; k++) {
                i.push_back(0);
                I.push_back(std::make_pair(0,0));
            }
            GetMusic();
            delete doc;
        }
    }
    void GetMusic();             //index 0
    void GetScoreDefinition();   //index 1
    void GetStaffDefinitions();  //index 2
    void GetSections();          //index 3
    void GetMeasures();          //index 4
    void GetStaffs();            //index 5
    void GetLayers();            //index 6
};


#endif //MUSICSYNTHESIS_V2_PROCESSING_H
