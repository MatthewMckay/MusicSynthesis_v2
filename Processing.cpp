//
// Created by Matthew McKay on 6/24/15.
//

#include "Processing.h"

//initializes the set of tags
const Processing_T::strSet_T Processing_T::tags = {TAGS};

/**
 * Processes every file in the vector
 */
Processing_T::Processing_T(std::vector<const char *> files) {
    for (auto it = files.begin(); it != files.end(); ++it){
        //create a new document for each file
        doc = new XmlDomDocument_T(*it);
        //pull the data from the document
        BeginProcessing();
        //delete the processed document, its no longer needed
        delete doc;
    }
}

/**
 * creates music objects which store all information about a musical work necessary for synthesis
 */
void Processing_T::BeginProcessing() {
    // find every music in the file
    for (int i = 0; i < doc->GetChildCount("music"); i++){
        // search only the decendants of this music element
        doc->SetNewRoot("music",i);
        // create a music
        CreateMusic();

        try {
            std::string tagName = " "; //holds the name of the macthed element tag
            /**
             * while a valid tag is found create the appropriate object
             * these are ordered from most frequent occurence in an XML down
             */
            while (tagName != "") {
                tagName = doc->FirstDescendantNamed(tags);
                if (tagName == "note") CreateNote();
                else if (tagName == "rest") CreateRest();
                else if (tagName == "layer") CreateLayer();
                else if (tagName == "chord") CreateChord();
                else if (tagName == "staff") CreateStaff();
                else if (tagName == "measure") CreateMeasure();
                else if (tagName == "mRest") CreateMRest();
                else if (tagName == "staffDef") CreateStaffDef();
                else if (tagName == "section") CreateSection();
                else if (tagName == "mSpace") CreateMSpace();
                else if (tagName == "multiRest") CreateMultiRest();
                else if (tagName == "scoreDef") CreateScoreDef();
                else if (tagName == "") break;
                else throw "ERR: Uncaught, invalid tag";
            }
        }
        catch (const char * e) {
            std::cerr<< e << '\n';
            std::exit(EXIT_FAILURE);
        }
    }
}

/**
 * Creates a music object
 * contains:
 *      scoreDef ScoreDefinition_T
 *      sections vector<Section_T>
 */
void Processing_T::CreateMusic() {
    Music_T newMusic;
    music.push_back(newMusic); // store the music
}

/**
 * Creates a score definition object
 * initializes the fields:
 *      “meterCount” int    mandatory
 *      ”meterUnit”  int    mandatory
 *      ”keySig”     string mandatory
 *      ”keyMode”    string mandatory
 *      "defaultAccidentals vector<string>
 * contains:
 *      staffDefs    unordered_map<string n, StaffDefinition_T>
 *
 * WORKS FOR MOST CASES
 * TODO add method for extracting key signature from a combination of key pitch, key accidental, and key mode;
 */
void Processing_T::CreateScoreDef() {
    ScoreDefinition_T newScoreDef;

    try {
        if (!GEA_E("meter.count")) newScoreDef.meterCount = std::stoi(GEA("meter.count"));
        //else throw "ERR: meter count not specified";

        if (!GEA_E("meter.unit")) newScoreDef.meterUnit = std::stoi(GEA("meter.unit"));
        //else throw "ERR: meter unit not specified";

        if (!GEA_E("key.sig")) newScoreDef.keySig = GEA("key.sig");
        //else throw "ERR: key signature not specified";

        if (!GEA_E("key.mode")) newScoreDef.keyMode = GEA("key.mode");
        //else throw "ERR: key mode not specified";

        newScoreDef.defaultAccidentals = newScoreDef.GetKeySig(newScoreDef.keySig);
    }
    catch (const char * e) {
        std::cerr<< e << '\n';
        std::exit(EXIT_FAILURE);
    }

    MUSICB.scoreDef = newScoreDef; //add to music
}

/**
 * Creates a staff definition object
 * initializes the fields:
 *      keySig  int     mandatory (gets from score definition if not specified)
 *      label   string  not mandatory
 *      n       string  mandatory (staffs share the same parameter and used to look for dflt accids for notes)
 *      defaultAccidentals vector<string>
 */
//“key.sig”,”label”,”n”
void Processing_T::CreateStaffDef() {
    StaffDefinition_T staffDef;

    try {
        if (!GEA_E("key.sig")) staffDef.keySig = GEA("key.sig");
        else if (!MUSICB.scoreDef.keySig.empty()) staffDef.keySig = MUSICB.scoreDef.keySig;
        else throw "ERR: Uncaught scoreDef should have a key signature";

        if (!GEA_E("label")) staffDef.label = GEA("label");
        else staffDef.label = "N/A";

        if (!GEA_E("n")) staffDef.n = GEA("n");
        else throw "ERR: staff definitions must have a name \"n\"";

        staffDef.defaultAccidentals = staffDef.GetKeySig(staffDef.keySig);
    }
    catch (const char * e) {
        std::cerr<< e << '\n';
        std::exit(EXIT_FAILURE);
    }

    MUSICB.scoreDef.staffDefs.insert({staffDef.n, staffDef}); // add to scoreDef
}

/**
 * Creates a section object
 * initializes fields:
 *      n   string  not mandatory
 */
void Processing_T::CreateSection() {
    Section_T sect;
    sect.n = GEA("n");
    MUSICB.sections.push_back(sect);
}

/**
* Creates a measure object
* initializes fields:
*      n   string  not mandatory
*/
void Processing_T::CreateMeasure() {
    Measure_T measure;
    measure.n = GEA("n");
    MUSICB.SECTB.measures.push_back(measure);
}

/**
* Creates a staff object
* initializes fields:
*      n   string  mandatory (used to find staff definition that has correct default accids for notes)
*/
void Processing_T::CreateStaff() {
    Staff_T staff;

    try {
        if (!GEA_E("n")) staff.n = GEA("n");
        else throw "ERR: n not specified";
    }
    catch (const char * e) {
        std::cerr<< e << '\n';
        std::exit(EXIT_FAILURE);
    }

    MUSICB.SECTB.MEASB.staffs.push_back(staff);
}

/**
* Creates a layer object
* initializes fields:
*       n   string  not mandatory
* contains:
*       sequence    vector<shared_ptr<Duration_T>> aka vector<SHP(Duration_T)>
*/
void Processing_T::CreateLayer() {
    Layer_T layer;
    layer.n = GEA("n");
    MUSICB.SECTB.MEASB.STAFFB.layers.push_back(layer);
}

/**
 * Creates a chord object
 * initializes fields:
 *      dur         TimeFraction_T  mandatory
 *      dots        int mandatory
 *      noteCount   int mandatory
 *      notes       vector<shared_ptr<Note_T>> madatory
 * Calls AddChordNote(TimeFraction_T, int) for every child
 *      This will set the duration if not already specified
 */
//“dur”,”dots"
void Processing_T::CreateChord() {
    
    //SHP_T(x) = std::shared_ptr<x>
    SHP_T(Chord_T) chord (new Chord_T);
    global_shpCt++;
    TimeFraction_T tf;
    try {
        // if this chord element has a duration attribute set the chord duration
        if (!GEA_E("dur")) {
            chord->SetDuration(std::stoi(GEA("dur")));
            //if this chord element has a dots attribute modify the chord duration
            if (!GEA_E("dots")) {
                chord->dots = std::stoi(GEA("dots"));
                chord->DotModify(chord->dots);
            }
        }

        //count how many notes the chord contains
        chord->noteCount = doc->GetTotalChildCount();
        // use the count (for some reason calling "doc->GetTotalChildCount()" in the for-loop args doesn't work
        for (int i = 0; i < chord->noteCount; i++) {

            //create and add the note
            chord->notes.push_back(AddChordNote(chord->duration, chord->dots));
        }
        //if for some reason duration is still not set, throw an error
        if (chord->duration == tf) throw "ERR: All chords must have a duration";
    }
    catch (const char * e) {
        std::cerr<< e << '\n';
        std::exit(EXIT_FAILURE);
    }

    MUSICB.SECTB.MEASB.STAFFB.LAYB.sequence.push_back(chord);
}

/**
 * Create a note and return a SHP to it
 * initializes fields:
 *      pitch       char    mandatory
 *      octave      int     mandatory
 *      Accidental  string  mandatory
 *      duration    TimeFraction_T mandatory
 *      dots        int     not mandatory
 */
//SHP_T(x) = std::shared_ptr<x>
SHP_T(Note_T) Processing_T::AddChordNote(TimeFraction_T &chordDur, int &chordDots) {
    
    //advances document position
    doc->FirstDescendantNamed(tags);

    //creates new note
    SHP_T(Note_T) note (new Note_T);
    global_shpCt++;

    //TimeFraction_T are initialized to numerator = 0, denominator = 1 (aka 0)
    //used for checking durations have been set
    TimeFraction_T tf;
    try {
        //set the pitch
        if (!GEA_E("pname"))note->pitch = GEA("pname")[0];
        else throw "ERR: All notes must have a pitch";

        //set the octave
        if (!GEA_E("oct")) note->octave = std::stoi(GEA("oct"));
        else throw "ERR: Notes must have octave";

        //set the duration
        if (!GEA_E("dur")) {
            //if this note element has a duration specified, use it
            note->SetDuration(std::stoi(GEA("dur")));
            //if this note element has a dots specified, modify the duration
            if (!GEA_E("dots")) {
                note->dots = std::stoi(GEA("dots"));
                note->DotModify(note->dots);
            }
            //if the chord didn't have a specified duration copy the duration and dots from the first note encountered
            if (chordDur == tf) {
                chordDur  = note->duration;
                chordDots = note->dots;
            }
            // all note durations in a chord must be the same length
            // if this isn't the case, the parser messed up
            else if (note->duration != chordDur) throw "ERR-PARSE: All notes in a chord must have the same duration";
        }
        else {
            //if this note element didn't have a duration specified, copy the duration and dots from the chord
            if (chordDur != tf){
                note->duration = chordDur;
                note->dots = chordDots;
            }
            else throw "ERR: All notes must have durations";
        }

        //if an accidental is specified use it
        if (!GEA_E("accid")) note->accidental = GEA("accid");
        else {
            //otherwise look it up in the proper staffDef key signature
            //strstfMapIt_T = std::unordered_map<std::string, StaffDefinition_T>::iterator

            //match staff.n with corresponding staffDef.n
            strStfMapIt_T it = MUSICB.scoreDef.staffDefs.find(MUSICB.SECTB.MEASB.STAFFB.n);
            if (it != MUSICB.scoreDef.staffDefs.end()) {
                if (!it->second.keySig.empty()) {
                    //when found use the pitch [(should be lowercase) aka 97 - 103] - 'a' (aka 97) = 0-6
                    //to access correct string accidental for the pitch
                    note->accidental = it->second.defaultAccidentals[tolower(note->pitch) - 'a'];
                }
            }
            else throw "ERR: All notes must have an accidental";
        }
    }
    catch (std::string e) {
        std::cerr << ERR_CLRS << e << DFLT_CLRS << '\n';
        std::exit(EXIT_FAILURE);
    }
    return note;
}

/**
 * Create a note
 * initializes fields:
 *      pitch       char    mandatory
 *      octave      int     mandatory
 *      Accidental  string  mandatory
 *      duration    TimeFraction_T mandatory
 *      dots        int     not mandatory
 */
//SHP_T(x) = std::shared_ptr<x>
void Processing_T::CreateNote() {
    
    //create a new note
    SHP_T(Note_T) note (new Note_T);
    global_shpCt++;
    try {
        //set pitch
        if (!GEA_E("pname"))note->pitch = GEA("pname")[0];
        else throw "ERR: All notes must have a pitch";

        //set octave
        if (!GEA_E("oct")) note->octave = std::stoi(GEA("oct"));
        else throw "ERR: Notes must have octave";

        //set duration
        if (!GEA_E("dur")) {
            note->SetDuration(std::stoi(GEA("dur")));
            //if dots are specified, set dots
            if (!GEA_E("dots")) {
                note->dots = std::stoi(GEA("dots"));
                note->DotModify(note->dots);
            }
        }
        else throw "ERR: All notes should have durations";

        //if an accidental is specified use it
        if (!GEA_E("accid")) note->accidental = GEA("accid");
        else {
            //otherwise look it up in the proper staffDef key signature
            //strstfMapIt_T = std::unordered_map<std::string, StaffDefinition_T>::iterator

            //match staff.n with corresponding staffDef.n
            strStfMapIt_T it = MUSICB.scoreDef.staffDefs.find(MUSICB.SECTB.MEASB.STAFFB.n);
            if (it != MUSICB.scoreDef.staffDefs.end()) {
                if (!it->second.keySig.empty()) {
                    //when found use the pitch [(should be lowercase) aka 97 - 103] - 'a' (aka 97) = 0-6
                    //to access correct string accidental for the pitch
                    note->accidental = it->second.defaultAccidentals[note->pitch - 'a'];
                }
            }
            else throw "ERR: All notes should have accidentals";
        }
    }
    catch (std::string e) {
        std::cerr << ERR_CLRS << e << DFLT_CLRS << '\n';
        std::exit(EXIT_FAILURE);
    }
    MUSICB.SECTB.MEASB.STAFFB.LAYB.sequence.push_back(note);
}

/**
 * Creates rest obj
 * initializes fields:
 *      duration    TimeFraction_T mandatory
 */
void Processing_T::CreateRest() {
    
    SHP_T(Rest_T) rest (new Rest_T);
    global_shpCt++;
    try {
        if (!GEA_E("dur")) rest->SetDuration(std::stoi(GEA("dur")));
        //else throw "ERR: All rests must have durations";
    }
    catch (std::string e) {
        std::cerr << ERR_CLRS << e << DFLT_CLRS << '\n';
        std::exit(EXIT_FAILURE);
    }

    MUSICB.SECTB.MEASB.STAFFB.LAYB.sequence.push_back(rest);
}

/**
 * Creates Measure rest obj
 */
void Processing_T::CreateMRest() {
    
    SHP_T(MeasureRest_T) mRest (new MeasureRest_T);
    global_shpCt++;
    mRest->SetDuration();

    MUSICB.SECTB.MEASB.STAFFB.LAYB.sequence.push_back(mRest);
}

/**
 * Creates measure space obj
 */
void Processing_T::CreateMSpace() {
    
    SHP_T(MeasureSpace_T) mSpace (new MeasureSpace_T);
    global_shpCt++;
    mSpace->SetDuration();

    MUSICB.SECTB.MEASB.STAFFB.LAYB.sequence.push_back(mSpace);
}

/**
 * Creates multi-measure rest obj
 * initializes fields:
 *      duration    TimeFraction_T mandatory
 */
void Processing_T::CreateMultiRest() {
    
    SHP_T(MultiMeasureRest_T) multiRest (new MultiMeasureRest_T);
    global_shpCt++;
    try {
        if (!GEA_E("num")) multiRest->SetDuration(std::stoi(GEA("num")));
        else throw "ERR: All multi-measure rests must have a duration";
    }
    catch (std::string e) {
        std::cerr << ERR_CLRS << e << DFLT_CLRS << '\n';
        std::exit(EXIT_FAILURE);
    }
    MUSICB.SECTB.MEASB.STAFFB.LAYB.sequence.push_back(multiRest);
}

std::vector<SHP_T(Fragment_T)> Processing_T::MakeFragments() {
    
    int fragCount = 0;
    for (auto music_it = music.begin(); music_it != music.end(); ++music_it){
        for (auto sect_it = music_it->sections.begin(); sect_it != music_it->sections.end(); ++sect_it){
            int count = 0;
            for (auto meas_it = sect_it->measures.begin(); meas_it != sect_it->measures.end(); ++meas_it){
                if (count == FRAGMENT_LENGTH) count = 0;
                if (count == 0) {
                    SHP_T(Fragment_T) fragment (new Fragment_T);
                    global_shpCt++;
                    fragments.push_back(fragment);
                    fragCount++;
                }
                for (auto seq_it = meas_it->STAFFB.LAYB.sequence.begin();
                        seq_it != meas_it->STAFFB.LAYB.sequence.end(); ++seq_it){
                    fragments.back()->AddElement(*seq_it);
                }
                count++;
            }
        }
    }
    std::cout<<fragCount<<'\n';
    return fragments;
}