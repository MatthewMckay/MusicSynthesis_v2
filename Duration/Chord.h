//
// Created by Matthew McKay on 7/1/15.
//

#ifndef MUSICSYNTHESIS_V2_CHORD_H
#define MUSICSYNTHESIS_V2_CHORD_H

#include <iostream>
#include <vector>

#include "Duration.h"
#include "Note.h"

class Chord_T : public Duration_T {
friend class Processing_T;
private:
    std::vector<Note_T> notes;
public:
    Chord_T(){}
    void SetDuration(int d);
    void SetDuration(TimeFraction_T dur);
    void DotModify(int d);
    void AddNote(Note_T note);
    std::vector<Note_T> GetNotes() const {return notes;}

    friend std::ostream& operator<< (std::ostream& ostr, const Chord_T& chord){
        ostr << "Chord:\n";
        for (auto it = chord.notes.cbegin(); it != chord.notes.cend(); ++it) {
            ostr << "\t" << *it;
        }
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_CHORD_H
