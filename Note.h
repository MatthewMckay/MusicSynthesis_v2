//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_NOTE_H
#define MUSICSYNTHESIS_V2_NOTE_H

#include <iostream>
#include <fstream>

class NOTE {
private:
    char   pitch;
    char   accidental;
    int    octave;
    double duration;
public:
    NOTE() : pitch('\0'), accidental('\0'), octave(-1), duration(-1) {}
    NOTE(char p, char a, int o, double d) : pitch(p), accidental(a), octave(o), duration(d) {}
    //~NOTE();

    void SetPitch(char p);
    void SetAccidental(char a);
    void SetOctave(int o);
    void SetDuration(double d);

    char   GetPitch();
    char   GetAccidental();
    int    GetOctave();
    double GetDuration();

    friend std::ostream& operator<< (std::ostream& ostr, NOTE& note);
};


#endif //MUSICSYNTHESIS_V2_NOTE_H
