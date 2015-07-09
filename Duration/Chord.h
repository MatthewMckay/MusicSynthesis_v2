//
// Created by Matthew McKay on 7/1/15.
//

#ifndef MUSICSYNTHESIS_V2_CHORD_H
#define MUSICSYNTHESIS_V2_CHORD_H

#include <iostream>
#include <vector>

#include "../Constants.h"
#include "Duration.h"
#include "Note.h"

/**
 * Chord_T is a subclass of Duration_T
 * this groups together a small number of notes and in some cases set those notes' durations
 */
class Chord_T : public Duration_T {
    //to make code more readable Processing_T is friended
    friend class Processing_T;
private:
    //SHP_T(x) = shared_ptr<x>
    std::vector<SHP_T(Note_T)> notes;   //holds the notes
    int dots;                           //holds the dots
    int noteCount;                      //holds how notes are owned by this chord
public:
    //By default all chords have zero dots and no notes
    //Because all duration elements are casted to SHP(Duration_T) to preserve order, Duration_T has the field "type" to
    //reference in order to cast the pointer back to its original type. all Chord_T have type = "chord"
    Chord_T() : dots(0), noteCount(0) {type = "chord";}

    void SetDuration(int d);
    void SetDuration(TimeFraction_T dur);
    void DotModify(int d);                      //modifies the duration to account for dots [ dur * ((2^(n+1)-1)/(2^n))]
    TimeFraction_T ReverseDotModify() const;    //returns an unmodified duration

    //void AddNote(SHP(Note_T) note);
    std::vector<SHP_T(Note_T)> GetNotes() const {return notes;}

    friend std::ostream& operator<< (std::ostream& ostr, const Chord_T& chord) {
        TimeFraction_T tf;
        ostr << "\t\tCHORD:";
        tf = chord.ReverseDotModify();
        ostr << "  DURATION = " << tf;
        ostr << "  DOTS = " << chord.dots;
        tf = chord.GetDurationFraction();
        ostr << "  MODIFIED DURATION = " << tf << " has ("<<chord.noteCount<<") notes\n";
        for (int i = 0; i < chord.notes.size(); ++i) {
            ostr << "  " << *(chord.notes[i]);
        }
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_CHORD_H
