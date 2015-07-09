//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_NOTE_H
#define MUSICSYNTHESIS_V2_NOTE_H

#include <iostream>
#include <fstream>
#include <string>

#include "TimeFraction.h"
#include "Duration.h"

/**
 * Note_T holds necessary information about a note
 * pitch; accidentals affect pitch
 * octave
 * duration; dots affect duration
 */
class Note_T : public Duration_T {
friend class Processing_T;
private:
    char pitch;             //holds pitch
    std::string accidental; //holds accidental
    int octave;             //holds octave
    int dots;               //needed to reverse modify durations
public:
    //everything is zeroed to check for being set
    //Because all duration elements are casted to SHP(Duration_T) to preserve order, Duration_T has the field "type" to
    //reference in order to cast the pointer back to its original type. all Note_T have type = "note"
    Note_T() : pitch('\0'), accidental(""), octave(0), dots(0){type = "note";}
    void SetDuration(TimeFraction_T d);
    void DotModify(const int& dots);
    TimeFraction_T ReverseDotModify() const;

    //these aren't used just yet
    /*void SetPitch(char p);
    void SetAccidental(std::string a);
    void SetOctave(int o);
    void SetDuration(int d);

    char GetPitch() const;
    std::string GetAccidental() const;
    int  GetOctave() const;*/

    friend std::ostream& operator<< (std::ostream& ostr, const Note_T & note);
};


#endif //MUSICSYNTHESIS_V2_NOTE_H
