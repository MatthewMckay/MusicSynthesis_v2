//
// Created by Matthew McKay on 6/24/15.
//

#include "Processing.h"

void Processing_T::GetMusic() {
    try {
        if (doc->getChildCount("mei", 0, "music") > 1) {
            throw "Only the first music will be processed from this file";
        }
        else {
            Music_T m;
            music.push_back(m);
            i[1] = i[3] = 0;
            for (i[1]; i[1] < doc->getChildCount("music", 0, "scoreDef"); i[1]++) {
                ScoreDefinition_T sd;
                music[i[0]].scoreDef = sd;
                GetScoreDefinition();
            }
            for (i[3]; i[3] < doc->getChildCount("music", 0, "section"); i[3]++) {
                Section_T s;
                music[i[0]].sections.push_back(s);
                GetSections();
            }
            i[0]++;
        }
    }
    catch (std::string e) {
        std::cerr << e << '\n';
        return;
    }
}

void Processing_T::GetScoreDefinition() {
    std::string value;
    value = doc->getChildAttribute("music", 0, "scoreDef", i[1], "meter.count");
    music[i[0]].scoreDef.meterCount = std::stoi(value);
    value = doc->getChildAttribute("music", 0, "scoreDef", i[1], "meter.unit");
    music[i[0]].scoreDef.meterUnit = std::stoi(value);
    value = doc->getChildAttribute("music", 0, "scoreDef", i[1], "key.mode");
    music[i[0]].scoreDef.keyMode = value;
    value = doc->getChildAttribute("music", 0, "scoreDef", i[1], "key.sig");
    music[i[0]].scoreDef.keySig = value;
    music[i[0]].scoreDef.defaultAccidentals = GetKeySig(music[i[0]].scoreDef.keySig);
    i[2] = 0;
    for (i[2]; i[2] < doc->getChildCount("scoreDef", i[1], "staffDef"); i[2]++){
        StaffDefinition_T st;
        music[i[0]].scoreDef.staffGrp.push_back(st);
        GetStaffDefinitions();
    }
}

void Processing_T::GetStaffDefinitions() {
    std::string value;
    value = doc->getChildAttribute("scoreDef", i[1], "staffDef", i[2], "n");
    music[i[0]].scoreDef.staffGrp[i[2]].n = value;
    value = doc->getChildAttribute("scoreDef", i[1], "staffDef", i[2], "label");
    music[i[0]].scoreDef.staffGrp[i[2]].label = value;
    value = doc->getChildAttribute("scoreDef", i[1], "staffDef", i[2], "key.sig");
    if (value == "") {
    music[i[0]].scoreDef.staffGrp[i[2]].keySig = music[i[0]].scoreDef.keySig;
    music[i[0]].scoreDef.staffGrp[i[2]].defaultAccidentals = music[i[0]].scoreDef.defaultAccidentals;
    }
    else {
        music[i[0]].scoreDef.staffGrp[i[2]].keySig = value;
        music[i[0]].scoreDef.staffGrp[i[2]].defaultAccidentals = GetKeySig(value);
    }
}

void Processing_T::GetSections() {
    std::string value;
    value = doc->getChildAttribute("music", 0, "section", i[3], "n");
    music[i[0]].sections[i[3]].n = value;
    i[4] = 0;
    for (i[4]; i[4] < doc->getChildCount("section",i[3], "measure"); i[4]++){

    }
}
