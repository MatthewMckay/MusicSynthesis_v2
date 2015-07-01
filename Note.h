//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_NOTE_H
#define MUSICSYNTHESIS_V2_NOTE_H

#include <iostream>
#include <fstream>

#include "Duration.h"

class Note_T : public Duration_T {
private:
    char   pitch;
    char   accidental;
    int    octave;
    double duration;
public:
    Note_T() : pitch('\0'), accidental('\0'), octave(-1), duration(-1) {}
    Note_T(char p, char a, int o, double d) : pitch(p), accidental(a), octave(o), duration(d) {}
    //~NOTE();

    void SetPitch(char p);
    void SetAccidental(char a);
    void SetOctave(int o);
    void SetDuration(double d);

    char   GetPitch() const;
    char   GetAccidental() const;
    int    GetOctave() const;
    double GetDuration() const;

    friend std::ostream& operator<< (std::ostream& ostr, const Note_T & note);
};


#endif //MUSICSYNTHESIS_V2_NOTE_H
