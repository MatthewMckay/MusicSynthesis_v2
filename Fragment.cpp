//
// Created by Matthew McKay on 6/22/15.
//

#include "Fragment.h"

std::string::size_type Sz;
Fragment_T::Fragment_T(const char *xmlFile) : basis(NULL), noteSamples(NULL), restSamples(NULL)
{
    noteSamples = new std::vector<Note_T>;
    restSamples = new std::vector<Rest_T>;
    std::cout<<"in frag constr\n";
    std::string value;
    doc = new XmlDomDocument_T(xmlFile);
    for (int i = 0; i < doc->getChildCount("mei", 0, "measure"); i++)
    {
        for (int k = 0; k < doc->getChildCount("measure", i, "note"); k++)
        {
            Note_T note;
            value = doc->getChildAttribute("measure", i, "note", k, "pname");
            note.SetPitch(value[0]);
            value = doc->getChildAttribute("measure", i, "note", k, "accid");
            note.SetAccidental(value[0]);
            value = doc->getChildAttribute("measure", i, "note", k, "oct");
            note.SetOctave(std::stoi(value, &Sz));
            value = doc->getChildAttribute("measure", i, "note", k, "dur");
            note.SetDuration(std::stod(value, &Sz));
            noteSamples->push_back(note);
        }
        for (int k = 0; k < doc->getChildCount("measure", i, "rest"); k++)
        {
            Rest_T rest;
            value = doc->getChildAttribute("measure", i, "note", k, "dur");
            rest.SetDuration(std::stod(value, &Sz));
            restSamples->push_back(rest);
        }
    }
    basis = new BASIS(noteSamples, restSamples);
}