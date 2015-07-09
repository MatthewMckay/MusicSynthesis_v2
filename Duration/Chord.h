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

class Chord_T : public Duration_T {
friend class Processing_T;
private:
    std::vector<SHP(Note_T)> notes;
    int dots;
    int children;
public:
    Chord_T() : dots(0), children(0) {type = "chord";}
    void SetDuration(int d);
    void SetDuration(TimeFraction_T dur);
    void DotModify(int d);
    TimeFraction_T ReverseDotModify() const;
    //void AddNote(SHP(Note_T) note);
    std::vector<SHP(Note_T)> GetNotes() const {return notes;}

    friend std::ostream& operator<< (std::ostream& ostr, const Chord_T& chord) {
        TimeFraction_T tf;
        ostr << "\t\tCHORD:";
        tf = chord.ReverseDotModify();
        ostr << "  DURATION = " << tf;
        ostr << "  DOTS = " << chord.dots;
        tf = chord.GetDurationFraction();
        ostr << "  MODIFIED DURATION = " << tf << " has ("<<chord.children<<") children\n";
        for (int i = 0; i < chord.notes.size(); ++i) {
            ostr << "  " << *(chord.notes[i]);
        }
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_CHORD_H
