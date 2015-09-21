//
// Created by Matthew McKay on 7/20/15.
//

#ifndef CYCLICARRAY_DIATONICCHORDS_H
#define CYCLICARRAY_DIATONICCHORDS_H
#include <iostream>
#include <cstring>
#include <string>
#include <set>
#include <list>

#include "CyclicArray.h"

typedef CyclicArray_T<std::string> CAStr_T;
typedef CyclicArray_T<int> CAInt_T;

#define SCALE {"a","b","c","d","e","f","g"}
#define SCALE_DIST {2,1,2,2,1,2,2}
#define DIAT_CHORDS {{1,3,5},{2,4,6},{3,5,7},{4,6,1},{5,7,2},{6,1,3},{7,2,4}}
#define D_CHORDS_SAME_PITCH {{1,4,6},{2,5,7},{3,6,1},{4,7,2},{5,1,3},{6,2,4},{7,3,5}}
#define SAME_PITCH_POS {1,3,2};
#define SHARPS {"f","c","g","d","a","e","b"}
#define FLATS {"b","e","a","d","g","c","f"}

class KeySignature_T {
protected:
    friend class Processing_T;
private:
    static const CAStr_T Scale_C;           //holds a - g in order
    static const CAInt_T ScaleDistRef_C;    //holds number of half tones to get to next pitch
    static const CAStr_T SharProg_C;        //holds order of sharp progression
    static const CAStr_T FlatProg_C;        //holds order of flat progression
    static const std::vector<std::vector<int>> DiatonicChords_C;        //holds pitch numbers for each chord I - VII
    static const std::vector<std::vector<int>> DChordW_SamePitch_C;     //holds chord numbers with same pitch a - g
    static const std::vector<int> SamePitchPos_C;   //holds position to find a similar pitch in each chord

    CAStr_T keySignature;       //holds order of pitches with accidentals
    std::string keyMode;        //major / minor
    int adjuster;       //keysignature is in a cyclicArray, this used to descramble so "X" - 'a' works

    void Simplify(std::string &str) const;  //modifies a pitch to its simplified equivalent \
                                            // ie. Bs = C : Aff = G : Dsf = D : Fs = Fs

public:

    int currentChord;   //when synthesizing this holds the last chord used to help determine next appropriate chord/note
    std::vector<std::vector<std::string>> chordPitches;     //holds pitches and there order contained in each diatonic chord

    KeySignature_T(){};
    KeySignature_T(std::string keySig, std::string mode); //sets keySignature, keyMode, adjuster, and chordPitches

    void Initialize(std::string keySig, std::string mode);

    unsigned int GetNextPossibleChords(const int lastChord);     //returns possible chords based on common chord progression theory
    unsigned int GetPreviousPossibleChords(const int nextChord);

    const int AdjustedI(int i) const;   //returns an unscrambled index
    void  DetermineCurrentChord(const std::string &pitch);  //if starting chord is unknown, guess from used notes
    const std::vector<std::pair<short, std::string> > GetTonesInCurrentChord() const;
    const std::vector<int> GetNextPossibleNotes(const int chord);  //returns a set of valid next notes to try

    //this was made to tie this into the existing project
    const std::vector<std::string> GetKeySig(){
        CAStr_T temp = keySignature;

        //shift back to align a-g
        temp.Shift(7-adjuster);

        //get rid of pitch name
        for (int i = 0; i < temp.Size(); i++){
            temp[i].erase(0,1);
            if (temp[i].size() == 0) temp[i] = "n";
        }

        //return a vector of accidentals
        return temp.data;
    }

    void UpdateCurrentChord(const int &chordNum) { currentChord = chordNum; }

    void MakeChordPitches();    //creates the pitches in each diatonic chord

    //const std::vector<int> GetPossibleChordNums(const char &pname, const std::string &accid);
    //void CalculateChordName(const std::vector<int> &chordName);
    //const int  CalculateDistance(const std::string &begining, const std::string &ending);

    const std::vector<std::vector<std::string>> GetChordPitches() const { return chordPitches; }
    const int GetAdjuster() const { return adjuster; }
    CAStr_T GetKeySignature() const { return keySignature; }
};

#endif //CYCLICARRAY_DIATONICCHORDS_H
