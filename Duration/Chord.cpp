//
// Created by Matthew McKay on 7/1/15.
//

#include "Chord.h"

void Chord_T::SetDuration( int d ) {
    if ( d == 1 ) duration.numerator = d;
    else {
        duration.numerator = 1;
        duration.denominator = d;
    }
}

void Chord_T::DotModify(int dots ) {
    if ( dots == 0 ) return;
    else{
        duration.numerator = ( duration.numerator << ( dots + 1 ) ) - 1;
        duration.denominator = duration.denominator << dots;
    }
}

void Chord_T::AddNote(Note_T note) {
    if (GetDuration() == 0) SetDuration(note.GetDurationFraction());
    else {
        if ( note.GetDuration() == 0) note.SetDuration(GetDurationFraction());
    }
    notes.push_back(note);
}

void Chord_T::SetDuration(TimeFraction_T dur) {
    duration = dur;
}
