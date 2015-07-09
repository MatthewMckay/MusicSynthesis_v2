//
// Created by Matthew McKay on 6/24/15.
//

#include "Processing.h"

const Processing_T::strSet_T Processing_T::tags = {TAGS};

Processing_T::Processing_T(std::vector<const char *> files) {
    for (auto it = files.begin(); it != files.end(); ++it){
        doc = new XmlDomDocument_T(*it);
        BeginProcessing();
        delete doc;
    }
}

void Processing_T::BeginProcessing() {
    std::string value = " ";
    for (int i = 0; i < doc->GetChildCount("music"); i++){
        doc->SetNewRoot("music",i);
        CreateMusic();
        try {
            while (value != "") {
                value = doc->FirstDescendantNamed(tags);
                if (value == "note") CreateNote();
                else if (value == "rest") CreateRest();
                else if (value == "layer") CreateLayer();
                else if (value == "chord") CreateChord();
                else if (value == "staff") CreateStaff();
                else if (value == "measure") CreateMeasure();
                else if (value == "mRest") CreateMRest();
                else if (value == "staffDef") CreateStaffDef();
                else if (value == "section") CreateSection();
                else if (value == "mSpace") CreateMSpace();
                else if (value == "multiRest") CreateMultiRest();
                else if (value == "scoreDef") CreateScoreDef();
                //else throw "ERR: Uncaught - Invalid tag value";
            }
        }
        catch (std::string e) {
            std::cerr << ERR_CLRS << e << DFLT_CLRS << '\n';
            std::exit(EXIT_FAILURE);
        }
    }
}


void Processing_T::CreateMusic() {
    Music_T newMusic;
    music.push(newMusic);
}
//“meter.count”,”meter.unit”,”key.sig”,”key.mode”
void Processing_T::CreateScoreDef() {
    ScoreDefinition_T newScoreDef;
    if (!GEA_E("meter.count")) newScoreDef.meterCount = std::stoi(GEA("meter.count"));
    if (!GEA_E("meter.unit")) newScoreDef.meterUnit  = std::stoi(GEA("meter.unit"));
    newScoreDef.keySig  = GEA("key.sig");
    newScoreDef.keyMode = GEA("key.mode");
    newScoreDef.defaultAccidentals = GetKeySig(newScoreDef.keySig);
    MT.scoreDef = newScoreDef;
    std::cout<<"scoreDef\n";
}

/*void Processing_T::CreateStaffGrp() {
}*/

//“key.sig”,”label”,”n”
void Processing_T::CreateStaffDef() {
    StaffDefinition_T staffDef;
    try{
        if(!GEA_E("key.sig")) staffDef.keySig = GEA("key.sig");
                else {
            if (!MT.scoreDef.keySig.empty()) staffDef.keySig = MT.scoreDef.keySig;
            //else throw "ERR: Either scoreDef or staffDeff must specify a key signature";
        }
    }
    catch (std::string e) {
        std::cerr << ERR_CLRS << e << DFLT_CLRS << '\n';
        std::exit(EXIT_FAILURE);
    }
    staffDef.label  = GEA("label");
    staffDef.n      = GEA("n");
    staffDef.defaultAccidentals = GetKeySig(staffDef.keySig);
    MT.scoreDef.staffDefs.insert({staffDef.n, staffDef});
    //std::cout<<"\tstaffDef\n";
}

void Processing_T::CreateSection() {
    Section_T sect;
    sect.n = GEA("n");
    MT.sections.push_back(sect);
    //std::cout<<"section\n";
}

void Processing_T::CreateMeasure() {
    Measure_T measure;
    measure.n = GEA("n");
    MT.SEB.measures.push_back(measure);
    //std::cout<<"\tmeasure\n";
}

void Processing_T::CreateStaff() {
    Staff_T staff;
    staff.n = GEA("n");
    MT.SEB.MB.staffs.push_back(staff);
    //std::cout<<"\t\tstaff\n";
}

void Processing_T::CreateLayer() {
    Layer_T layer;
    layer.n = GEA("n");
    MT.SEB.MB.SB.layers.push_back(layer);
    //std::cout<<"\t\t\tlayer\n";
}
//“dur”,”dots"
void Processing_T::CreateChord() {
    SHP(Chord_T) chord (new Chord_T);
    TimeFraction_T tf;
    try {
        if (!GEA_E("dur")) {
            chord->SetDuration(std::stoi(GEA("dur")));
            if (!GEA_E("dots")) {
                chord->dots = std::stoi(GEA("dots"));
                chord->DotModify(chord->dots);
            }
        }chord->children = doc->GetTotalChildCount();
        for (int i = 0; i < chord->children; i++) {
            chord->notes.push_back(AddChordNote(chord->duration, i));
        }
        if (chord->duration == tf) throw "ERR: All chords must have a duration";
    }
    catch (std::string e) {
        std::cerr << ERR_CLRS << e << DFLT_CLRS << '\n';
        std::exit(EXIT_FAILURE);
    }
    MT.SEB.MB.SB.LB.sequence.push_back(chord);
}

SHP(Note_T) Processing_T::AddChordNote(TimeFraction_T &dur, const int& i) {
    doc->FirstDescendantNamed(tags);
    SHP(Note_T) note (new Note_T);
    TimeFraction_T tf;
    try {
        if (!GEA_E("pname"))note->pitch = GEA("pname")[0];
        //else throw "ERR: All notes must have a pitch";

        if (!GEA_E("oct")) note->octave = std::stoi(GEA("oct"));
        //else throw "ERR: Notes must have octave";


        if (!GEA_E("dur")) {
            note->SetDuration(std::stoi(GEA("dur")));
            if (!GEA_E("dots")) {
                note->dots = std::stoi(GEA("dots"));
                note->DotModify(note->dots);
            }
            if (dur == tf) dur = note->duration;
            //else if (note.duration != dur) throw "ERR: All notes in a chord must have the same duration";
        }
        else {
            if (dur != tf) note->duration = dur;
            //else throw "ERR: All notes must have durations";
        }

        if (!GEA_E("accid")) {note->accidental = GEA("accid"); std::cout<<GEA("accid")<<'\n';}
        else {
            strStfMapIt_T it = music.top().scoreDef.staffDefs.find(MT.SEB.MB.SB.n);
            if (it != MT.scoreDef.staffDefs.end()) {
                if (!it->second.keySig.empty()) {
                    note->accidental = it->second.defaultAccidentals[note->pitch - 'a'];
                }
            }
            //else throw "ERR: All notes must have an accidental";
        }
    }
    catch (std::string e) {
        std::cerr << ERR_CLRS << e << DFLT_CLRS << '\n';
        std::exit(EXIT_FAILURE);
    }
    return note;
}

//“pname”,”accid”,”oct”,”dur”,”dots”
void Processing_T::CreateNote() {
    SHP(Note_T) note (new Note_T);
    TimeFraction_T tf;
    try {
        if (!GEA_E("pname"))note->pitch = GEA("pname")[0];
        //else throw "ERR: All notes must have a pitch";

        if (!GEA_E("oct")) note->octave = std::stoi(GEA("oct"));
        //else throw "ERR: Notes must have octave";

        if (!GEA_E("dur")) {
            note->SetDuration(std::stoi(GEA("dur")));
            if (!GEA_E("dots")) {
                note->dots = std::stoi(GEA("dots"));
                note->DotModify(note->dots);
            }
        }
        //else throw "ERR: All notes should have durations";

        if (!GEA_E("accid")) note->accidental = GEA("accid");
        else {
            strStfMapIt_T it = music.top().scoreDef.staffDefs.find(MT.SEB.MB.SB.LB.n);
            if (it != MT.scoreDef.staffDefs.end()) {
                if (!it->second.keySig.empty()) {
                    note->accidental = it->second.defaultAccidentals[note->pitch - 'a'];
                }
            }
            //else throw "ERR: All notes should have durations";
        }
    }
    catch (std::string e) {
        std::cerr << ERR_CLRS << e << DFLT_CLRS << '\n';
        std::exit(EXIT_FAILURE);
    }
    MT.SEB.MB.SB.LB.sequence.push_back(note);
}
//dur
void Processing_T::CreateRest() {
    SHP(Rest_T) rest (new Rest_T);
    try {
        if (!GEA_E("dur")) rest->SetDuration(std::stoi(GEA("dur")));
        //else throw "ERR: All rests must have durations";
    }
    catch (std::string e) {
        std::cerr << ERR_CLRS << e << DFLT_CLRS << '\n';
        std::exit(EXIT_FAILURE);
    }

    MT.SEB.MB.SB.LB.sequence.push_back(rest);
}

void Processing_T::CreateMRest() {
    SHP(MeasureRest_T) mRest (new MeasureRest_T);
    mRest->SetDuration();

    MT.SEB.MB.SB.LB.sequence.push_back(mRest);
}

void Processing_T::CreateMSpace() {
    SHP(MeasureSpace_T) mSpace (new MeasureSpace_T);
    mSpace->SetDuration();

    MT.SEB.MB.SB.LB.sequence.push_back(mSpace);
}
//num
void Processing_T::CreateMultiRest() {
    SHP(MultiMeasureRest_T) multiRest (new MultiMeasureRest_T);
    try {
        if (!GEA_E("num")) multiRest->SetDuration(std::stoi(GEA("num")));
        //else throw "ERR: All multi-measure rests must have a duration";
    }
    catch (std::string e) {
        std::cerr << ERR_CLRS << e << DFLT_CLRS << '\n';
        std::exit(EXIT_FAILURE);
    }
    MT.SEB.MB.SB.LB.sequence.push_back(multiRest);
}


