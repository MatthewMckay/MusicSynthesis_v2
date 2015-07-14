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
    void SetDuration(int d);
    void DotModify(const int& dots);
    TimeFraction_T ReverseDotModify() const;

    char GetPitch() const;
    std::string GetAccidental() const;
    int  GetOctave() const;
    int GetDots() const;
    void SetPitch(char p);
    void SetAccidental(std::string a);
    void SetOctave(int o);
    void SetDuration(TimeFraction_T d);
    void SetDots(int d);

    //these aren't used just yet
    /*
*/

    friend std::ostream& operator<< (std::ostream& ostr, const Note_T & note);
    friend bool operator== (const Note_T &lhs, const Note_T &rhs){
        return ( lhs.pitch == rhs.pitch &&
                 lhs.accidental == rhs.accidental &&
                 lhs.octave == rhs.octave &&
                 lhs.duration == rhs.duration &&
                 lhs.dots == rhs.dots );
    }
};

struct NoteHash {
public:
    std::size_t operator() (const Note_T &note) const {
        std::string str;
        str += note.GetPitch();
        str += note.GetAccidental();
        str += std::to_string(note.GetOctave());
        str += std::to_string(note.GetDurationFraction().numerator);
        str += std::to_string(note.GetDurationFraction().denominator);
        str += std::to_string(note.GetDots());
        std::hash<std::string> str_hash;
        return str_hash(str);
    }
};


#endif //MUSICSYNTHESIS_V2_NOTE_H
