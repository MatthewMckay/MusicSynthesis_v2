//
// Created by Matthew McKay on 6/22/15.
//

#include "Note.h"

//************* Setters **********************

void NOTE::SetPitch(char p) { pitch = p; }

void NOTE::SetAccidental(char a) { accidental = a; }

void NOTE::SetOctave(int o) { octave = o; }

void NOTE::SetDuration(double d) { duration = d; }



//************* Getters **********************

char   NOTE::GetPitch() { return pitch; }

char   NOTE::GetAccidental() { return accidental; }

int    NOTE::GetOctave() { return octave; }

double NOTE::GetDuration() { return duration; }


//************* Operators ********************

std::ostream& operator<< (std::ostream& ostr, NOTE &note)
{
    ostr << "PITCH = " << note.pitch;
    ostr << "  ACCIDENTAL = " << note.accidental;
    ostr << "  OCTAVE = " << note.octave;
    ostr << "  DURATION = " << note.duration;
    ostr << "\n";
    return ostr;
}