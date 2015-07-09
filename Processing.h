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


/**
 * Processing_T is instantiated with a vector of file names
 *
 * this object holds the original music data in the correct order
 * TODO this object provides methods for extracting fragments
 *
 * for each file:
 * 1 - it creates a new XmlDomDocument
 * 2 - for every music  element it encounters
 *      A - a music object is created
 *      B - it passes the constant set of tag names to the FirstElementChildName(TAGS) in the document
 *      C - for each found element
 *          i   - it pulls the appropriate attributes for the found element
 *          ii  - the element creates a matching object and added to the music object
 * 3 - the document is deleted and the next file is processed
 * 4 - TODO fragments are created
 */
class Processing_T {
    typedef std::set<const std::string> strSet_T; // this is the type that the XmlDomDocument excepts

    //used to iterate through Score Definition staffDefs
    typedef std::unordered_map<std::string, StaffDefinition_T>::iterator strStfMapIt_T;

private:
    const static strSet_T tags; // stores the tag names
    XmlDomDocument_T * doc;     // points to a document
    std::vector<Music_T> music;  // holds all processed music data
    //std::vector<SHP(Fragment_T) // holds all fragments generated

    void CreateMusic();     //creates new music object and pushes it to the music vector
    void CreateScoreDef();  //creates new score definition and puts in back music obj
    void CreateStaffDef();  //creates new staff definition and puts in back scoreDef obj
    void CreateSection();   //      ||    section                   ||      music obj
    void CreateMeasure();   //      ||    measure                   ||      section obj
    void CreateStaff();     //      ||    staff                     ||      measure obj
    void CreateLayer();     //      ||    layer                     ||      staff obj
    void CreateChord();     //      ||    chord                     ||      layer obj
    void CreateNote();      //      ||    note                      ||          ||
    void CreateRest();      //      ||    rest                      ||          ||
    void CreateMRest();     //      ||    measure rest              ||          ||
    void CreateMSpace();    //      ||    measure space             ||          ||
    void CreateMultiRest(); //      \/    multi-measure rest        \/          \/

    //SHP( type_t ) -> std::shared_ptr< type_t >
    SHP_T(Note_T) AddChordNote(TimeFraction_T &chordDur, int &chordDots); //creates and adds a note to a chord

    void BeginProcessing(); //Pulls data from all files provided

    Processing_T(){}; //ensures that this must be instantiated with an argument

public:
    Processing_T(std::vector<const char *> files); //only acceptable constructor
    void PrintMusic(){ std::cout<<music.back()<<'\n'; } //used to check if
    //TODO create GenerateFragments()
    //TODO create vector<share_ptr<Fragment_T>> GetFragments() const

private:
    //These are the typical and necessary element tag names found in an MEI XML file
#define TAGS "scoreDef","staffDef","section","measure","staff","layer","chord","note","rest","mRest","mSpace","multiRest"

/**
 * these macros make code more readable
 */
#define GEA(str) doc->GetElementAttribute(str)
#define GEA_E(str) doc->GetElementAttribute(str).empty()
#define MUSICB music.back()
#define SECTB sections.back()
#define MEASB measures.back()
#define STAFFB staffs.back()
#define LAYB layers.back()
};


#endif //MUSICSYNTHESIS_V2_PROCESSING_H
