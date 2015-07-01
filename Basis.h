//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_BASIS_H
#define MUSICSYNTHESIS_V2_BASIS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

#include "Note.h"
#include "Rest.h"

class BASIS {
    typedef std::unordered_set<char> usc;
    typedef std::unordered_set<int> usi;
    typedef std::unordered_set<double> usd;
private:
    Note_T newNote;
    usc * Pitches;
    usc * Accidentals;
    usi * Octaves;
    usd * NoteDurations;
    usd * RestDurations;
    std::vector<Note_T> * noteBasis;
    std::vector<Rest_T> * restBasis;
    void sortIntoCategories(Note_T note);
    void sortIntoCategoriesR(Rest_T rest);
    BASIS(){};
    void CreateBasis();
public:
    BASIS(std::vector<Note_T> * sNotes, std::vector<Rest_T> * sRests);
    ~BASIS(){delete noteBasis, restBasis;}


    /*void InsertNote(char p, char a, int o, double d);
    void InsertRest(double d);

    std::vector<NOTE> GetNotes();
    std::vector<REST> GetRests();*/
};


#endif //MUSICSYNTHESIS_V2_BASIS_H
