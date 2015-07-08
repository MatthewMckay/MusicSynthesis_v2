//
// Created by Matthew McKay on 6/22/15.
//

#include "Note.h"

//************* Setters **********************

void Note_T::SetPitch(char p) { pitch = p; }

void Note_T::SetAccidental(std::string a) { accidental = a; }

void Note_T::SetOctave(int o) { octave = o; }

void Note_T::SetDuration(int d) {
    if (d == 1) duration.numerator = d;
    else {
        duration.numerator = 1;
        duration.denominator = d;
    }
}
void Note_T::SetDuration(TimeFraction_T d) {
    duration = d;
}

/**
 * dots (number of dots n) modify the original duration (dur) with the following equation
 * dur * (2 - (1 / (2^n))) == dur * ((2^(n+1)-1)/(2^n))
 */
void Note_T::DotModify(const int& dots ) {
    if ( dots == 0 ) return;
    else{
        duration.numerator = ( duration.numerator << ( dots + 1 ) ) - 1;
        duration.denominator = duration.denominator << dots;
    }
}



//************* Getters **********************

char   Note_T::GetPitch() const { return pitch; }

char   Note_T::GetAccidental() const { return accidental; }

int    Note_T::GetOctave() const { return octave; }


//************* Operators ********************

std::ostream& operator<< (std::ostream& ostr, const Note_T &note)
{
    ostr << "PITCH = " << note.pitch;
    ostr << "  ACCIDENTAL = " << note.accidental;
    ostr << "  OCTAVE = " << note.octave;
    ostr << "  DURATION = " << note.GetDurationFraction();
    ostr << "\n";
    return ostr;
}