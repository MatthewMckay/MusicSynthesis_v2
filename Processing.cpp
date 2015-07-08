//
// Created by Matthew McKay on 6/24/15.
//

#include "Processing.h"

Processing_T::Processing_T(std::vector<const char *> files) {
    //functionMap["music"]    = &CreateMusic;
    functionMap["scoreDef"] = &CreateScoreDef;
    //functionMap["staffGrp"] = &CreateStaffGrp;
    functionMap["staffDef"] = &CreateStaffDef;
    functionMap["section"]  = &CreateSection;
    functionMap["measure"]  = &CreateMeasure;
    functionMap["staff"]    = &CreateStaff;
    functionMap["layer"]    = &CreateLayer;
    functionMap["chord"]    = &CreateChord;
    functionMap["note"]     = &CreateNote;
    functionMap["rest"]     = &CreateRest;
    functionMap["mRest"]    = &CreateMRest;
    functionMap["mSpace"]   = &CreateMSpace;
    functionMap["multiRest"]= &CreateMultiRest;

    tags = {TAGS};
    for (auto it = files.begin(); it != files.end(); ++it){
        doc = new XmlDomDocument_T(*it);
        BeginProcessing();
        delete doc;
    }
}

void Processing_T::BeginProcessing() {
    std::string value = " ";
    for (int i = 0; i < doc->GetChildCount("music"); i++){
        musicIndex = i;
        doc->SetNewRoot("music",i);
        CreateMusic();
        while (value != ""){
            value = doc->FirstDescendantNamed(tags);
            strFuncMap_T::iterator it = functionMap.find(value);
            if (it != functionMap.end()) it->second();
        }
    }
}


void Processing_T::CreateMusic() {
    Music_T newMusic;
    music.push(newMusic);
}
//“meter.count”,”meter.unit”,”key.sig”,”key.mode”
void Processing_T::CreateScoreDef() {
    ScoreDefinition_T newScoreDef;;
    if (GEA_E("meter.count")) newScoreDef.meterCount = std::stoi(GEA("meter.count"));
    if (GEA_E("meter.unit")) newScoreDef.meterUnit  = std::stoi(GEA("meter.unit"));
    newScoreDef.keySig  = GEA("key.sig");
    newScoreDef.keyMode = GEA("key.mode");
    newScoreDef.defaultAccidentals = GetKeySig(newScoreDef.keySig);
    MT.scoreDef = newScoreDef;
}

/*void Processing_T::CreateStaffGrp() {
}*/

//“key.sig”,”label”,”n”
void Processing_T::CreateStaffDef() {
    StaffDefinition_T staffDef;
    staffDef.keySig = GEA("key.sig");
    staffDef.label  = GEA("label");
    staffDef.n      = GEA("n");
    staffDef.defaultAccidentals = GetKeySig(staffDef.keySig);
    MT.scoreDef.staffDefs.insert({staffDef.n, staffDef});
}

void Processing_T::CreateSection() {
    Section_T sect;
    sect.n = GEA("n");
    MT.sections.push_back(sect);
}

void Processing_T::CreateMeasure() {
    Measure_T measure;
    measure.n = GEA("n");
    MT.SEB.measures.push_back(measure);
}

void Processing_T::CreateStaff() {
    Staff_T staff;
    staff.n = GEA("n");
    MT.SEB.MB.staffs.push_back(staff);
}

void Processing_T::CreateLayer() {
    Layer_T layer;
    layer.n = GEA("n");
    MT.SEB.MB.SB.layers.push_back(layer);
}
//“dur”,”dots"
void Processing_T::CreateChord() {
    Chord_T chord;
    if (!GEA_E("dur")){
        chord.SetDuration(std::stoi(GEA("dur")));
        if (!GEA_E("dots")) chord.DotModify(std::stoi(GEA("dots")));
    }
    else {
        for (int i = 0; i < doc->GetTotalChildCount(); i++){
            chord.notes.push_back(AddChordNote(chord.duration));
        }
    }
}

Note_T Processing_T::AddChordNote(TimeFraction_T &dur) {
    Note_T note;
    TimeFraction_T tf;
    note.pitch = GEA("pname")[0];
    try {
        if (!GEA_E("oct")) note.octave = std::stoi(GEA("oct"));
        else throw "ERR: Notes must have octave";
    }
    catch (std::string e) { std::cerr << ERR_CLRS << e << DFLT_CLRS << '\n'; }

    try {
        if (!GEA_E("dur")){
            note.SetDuration(std::stoi(GEA("dur")));
            if (!GEA_E("dots")) note.DotModify(std::stoi(GEA("dots")));
            if (dur == tf) dur = note.duration;
            else if (note.duration != dur) throw "ERR: All notes in a chord must have the same duration";
        }
        else {
            if (dur != tf) note.duration = dur;
            else throw "ERR: All notes and chords must have durations";
        }
    }
    catch (std::string e) { std::cerr << ERR_CLRS << e << DFLT_CLRS << '\n'; }

    if (GEA_E("accid")) note.accidental = GEA("accid");
    else {
        strStfMapIt_T it = music.top().scoreDef.staffDefs.find(MT.SEB.MB.SB.LB.n);
        if(it != MT.scoreDef.staffDefs.end()){
            if (!it->second.keySig.empty()) {
                note.accidental = it->second.keySig[note.pitch - 'a'];
            }
        }
        else note.accidental = "n";
    }
}

//“pname”,”accid”,”oct”,”dur”,”dots”
void Processing_T::CreateNote() {

}
//dur
void Processing_T::CreateRest() {

}
//num
void Processing_T::CreateMRest() {

}

void Processing_T::CreateMSpace() {

}

void Processing_T::CreateMultiRest() {
}


