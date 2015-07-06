//
// Created by Matthew McKay on 7/1/15.
//

#include "Chord.h"

/**
 * used when the chord has a duration attribute
 */
void Chord_T::SetDuration( int d ) {
    if ( d == 1 ) duration.numerator = d;
    else {
        duration.numerator = 1;
        duration.denominator = d;
    }
}

/**
 * used when the chord copies the duration from its notes
 */
void Chord_T::SetDuration(TimeFraction_T dur) {
    duration = dur;
}

/**
 * dots (number of dots n) modify the original duration (dur) with the following equation
 * dur * (2 - (1 / (2^n))) == dur * ((2^(n+1)-1)/(2^n))
 */
void Chord_T::DotModify(int dots ) {
    if ( dots == 0 ) return;
    else{
        duration.numerator = ( duration.numerator << ( dots + 1 ) ) - 1;
        duration.denominator = duration.denominator << dots;
    }
}

/**
 * either the chord or the notes within the chord will have duration attributes
 * this makes sure both the chord and notes all have a duration set
 */
void Chord_T::AddNote(Note_T note) {
    //the chord doesn't have a duration attribute so get it from a note just once
    if (GetDuration() == 0) SetDuration(note.GetDurationFraction());
    else {
        //if
        if ( note.GetDuration() == 0) note.SetDuration(GetDurationFraction());
    }
    notes.push_back(note);
}
