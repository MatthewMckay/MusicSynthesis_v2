//
// Created by Matthew McKay on 6/22/15.
//

#include "Note.h"

//************* Setters **********************

void Note_T::SetPitch(char p) { pitch = p; }

void Note_T::SetAccidental(char a) { accidental = a; }

void Note_T::SetOctave(int o) { octave = o; }

void Note_T::SetDuration(double d) { duration = d; }



//************* Getters **********************

char   Note_T::GetPitch() const { return pitch; }

char   Note_T::GetAccidental() const { return accidental; }

int    Note_T::GetOctave() const { return octave; }

double Note_T::GetDuration() const { return duration; }


//************* Operators ********************

std::ostream& operator<< (std::ostream& ostr, Note_T &note)
{
    ostr << "PITCH = " << note.pitch;
    ostr << "  ACCIDENTAL = " << note.accidental;
    ostr << "  OCTAVE = " << note.octave;
    ostr << "  DURATION = " << note.duration;
    ostr << "\n";
    return ostr;
}