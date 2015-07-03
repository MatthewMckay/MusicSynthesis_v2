//
// Created by Matthew McKay on 7/1/15.
//

#ifndef MUSICSYNTHESIS_V2_CHORD_H
#define MUSICSYNTHESIS_V2_CHORD_H

#include <vector>

#include "Duration.h"
#include "Note.h"

class Chord_T : public Duration_T {
private:
    std::vector<Note_T> notes;
public:
    Chord_T(){}
    void SetDuration(int d);
    void SetDuration(TimeFraction_T dur);
    void DotModify(int d);
    void AddNote(Note_T note);
    std::vector<Note_T> GetNotes() const {return notes;}
};


#endif //MUSICSYNTHESIS_V2_CHORD_H
