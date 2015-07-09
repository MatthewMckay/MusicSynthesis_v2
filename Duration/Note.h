//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_NOTE_H
#define MUSICSYNTHESIS_V2_NOTE_H

#include <iostream>
#include <fstream>
#include <string>

#include "Duration.h"

class Note_T : public Duration_T {
friend class Processing_T;
private:
    char pitch;
    std::string accidental;
    int octave;
    int dots;
public:
    Note_T() : pitch('\0'), accidental(""), octave(7), dots(0){type = "note";}
    void SetPitch(char p);
    void SetAccidental(std::string a);
    void SetOctave(int o);
    void SetDuration(int d);
    void SetDuration(TimeFraction_T d);
    void DotModify(const int& dots);
    TimeFraction_T ReverseDotModify() const;

    char GetPitch() const;
    std::string GetAccidental() const;
    int  GetOctave() const;

    friend std::ostream& operator<< (std::ostream& ostr, const Note_T & note);
};


#endif //MUSICSYNTHESIS_V2_NOTE_H
