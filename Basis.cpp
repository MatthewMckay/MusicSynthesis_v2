//
// Created by Matthew McKay on 6/22/15.
//

#include "Basis.h"
BASIS::BASIS(std::vector<Note_T> *sNotes, std::vector<Rest_T> *sRests)
{
    noteBasis = new std::vector<Note_T>;
    restBasis = new std::vector<Rest_T>;
    Pitches = new usc;
    Accidentals = new usc;
    Octaves = new usi;
    NoteDurations = new usd;
    RestDurations = new usd;

    std::cout<<"INPUTTED NOTES:\n";
    for (unsigned long i = 0; i < sNotes->size(); i++)
    {
        sortIntoCategories((*sNotes)[i]);
        std::cout<<(*sNotes)[i];
    }

    std::cout<<"\n\nINPUTTED RESTS:\n";
    for (unsigned long i = 0; i < sRests->size(); i++)
    {
        sortIntoCategoriesR((*sRests)[i]);
        std::cout<<(*sRests)[i];
    }
    std::cout << "\n" << noteBasis->size() << " NOTES POSSIBLE\n\n";
    delete Pitches, Accidentals, Octaves, NoteDurations, RestDurations;
}

void BASIS::sortIntoCategories( Note_T note) {
    (*Pitches).insert(note.GetPitch());
    (*Accidentals).insert(note.GetAccidental());
    (*Octaves).insert(note.GetOctave());
    (*NoteDurations).insert(note.GetDuration());
}

void BASIS::sortIntoCategoriesR(Rest_T rest) {
    (*RestDurations).insert(rest.GetDuration());
}

void BASIS::CreateBasis() {
    std::cout<<"\n\nCALCULATING BASIS:\n";
    std::cout<<"UNIQUE PITCHES: " << (*Pitches).size() << "\n";
    std::cout<<"UNIQUE ACCIDENTALS: " << (*Accidentals).size() << "\n";
    std::cout<<"UNIQUE OCTAVES: " << (*Octaves).size() << "\n";
    std::cout<<"UNIQUE NOTE DURATIONS: " << (*NoteDurations).size() << "\n";
    std::cout<<"UNIQUE REST DURATIONS: " << (*RestDurations).size() << "\n\n";

    for ( auto pi = (*Pitches).begin(); pi != (*Pitches).end(); ++pi){
        for ( auto ai = (*Accidentals).begin(); ai != (*Accidentals).end(); ++ai){
            for ( auto oi = (*Octaves).begin(); oi != (*Octaves).end(); ++oi){
                for ( auto ndi = (*NoteDurations).begin(); ndi != (*NoteDurations).end(); ++ndi){
                    Note_T note(*pi, *ai, *oi, *ndi);
                    noteBasis->push_back(note);
                }
            }
        }
    }
    for ( auto it = RestDurations->begin(); it != RestDurations->end(); ++it){
        Rest_T rest(*it);
        restBasis->push_back(rest);
    }
    for ( auto it = noteBasis->begin(); it != noteBasis->end(); ++it ) std::cout << *it;
    for ( auto it = restBasis->begin(); it != restBasis->end(); ++it ) std::cout << *it;
}