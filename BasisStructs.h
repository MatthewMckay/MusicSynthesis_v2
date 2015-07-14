//
// Created by Matthew McKay on 7/13/15.
//

#ifndef MUSICSYNTHESIS_V2_BASISSTRUCTS_H
#define MUSICSYNTHESIS_V2_BASISSTRUCTS_H

struct Tone_T {
    char pitch;
    std::string accid;
    friend bool operator== (const Tone_T &lhs, const Tone_T &rhs){
        return (lhs.pitch == rhs.pitch && lhs.accid == rhs.accid);
    }
    friend bool operator< (const Tone_T &lhs, const Tone_T &rhs){
        std::string l = lhs.pitch + lhs.accid;
        std::string r = rhs.pitch + rhs.accid;
        return l < r;
    }
    friend bool operator> (const Tone_T &lhs, const Tone_T &rhs){
        std::string l = lhs.pitch + lhs.accid;
        std::string r = rhs.pitch + rhs.accid;
        return l > r;
    }
};

struct Dur_T {
    TimeFraction_T timeFraction;
    int dur;
    friend bool operator== (const Dur_T &lhs, const Dur_T &rhs) {
        return (lhs.timeFraction.numerator == rhs.timeFraction.numerator &&
                lhs.timeFraction.denominator == rhs.timeFraction.denominator &&
                lhs.dur == rhs.dur);
    }
    friend bool operator< (const Dur_T &lhs, const Dur_T &rhs) {
        return lhs.timeFraction < rhs.timeFraction;
    }
    friend bool operator> (const Dur_T &lhs, const Dur_T &rhs) {
        return lhs.timeFraction > rhs.timeFraction;
    }
};

#endif //MUSICSYNTHESIS_V2_BASISSTRUCTS_H
