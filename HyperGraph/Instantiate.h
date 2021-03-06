//
// Created by Matthew McKay on 8/1/15.
//

#ifndef MUSICSYNTHESIS_V2_INSTANTIATE_H
#define MUSICSYNTHESIS_V2_INSTANTIATE_H

#include <cmath>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <set>
#include <map>
#include <exception>
#include <random>
#include <cstdlib>

#include "../Constants.h"
#include "../BitWiseStack16_3.h"
#include "../BitWise32int_3.h"
#include "../Fragment.h"
#include "HyperGraph.h"
/*
template <class T>
class Vector_T : public std::vector<T> {
public:
    friend void operator+= (Vector_T &lhs, const Vector_T &rhs) {
        for (auto item : rhs) {
            lhs.push_back(item);
        }
    }
};

template <size_t N1, size_t N2>
int operator& (const std::bitset<N1> &lhs, const std::bitset<N2> &rhs) {
    try {
        if (N1 < N2) throw 10;
    }
    catch (int e) {
        std::cerr << "second bitset size_t must be smaller or equal to the first\n";
        std::exit (EXIT_FAILURE);
    }
    int value = 0;
    for (unsigned long i = 0; i < N2; ++i) {
        value += (lhs[i] & rhs[i]) << i;
    }
    return value;
}

template <size_t N1>
void Append(std::bitset<N1> &longer,const int& appendV, const short & bits, const short &n){
    std::bitset<N1> temp (appendV);
    temp <<= (bits * n);
    longer |= temp;
}

template <size_t N1>
void Truncate(std::bitset<N1> &longer,const int& truncV, const int & bits, const int &n){
    std::bitset<N1> temp (truncV);
    temp <<= (bits * n);
    longer ^= temp;
}
*/
typedef std::vector<std::vector<unsigned int> > IntBucketVect_T;
typedef std::vector<std::deque<unsigned int> > VectDeqBits_T;
typedef std::unordered_map<unsigned int, short> IntToShortID_T;

class Instantiate_T {
private:
#define POSSIBLE_ELEMS 5670

#define CHORD_POS 18
#define CHORD_GRAB 1835008
#define PITCH_POS 15
#define PITCH_GRAB 229376
#define ACCID_POS 13
#define ACCID_GRAB 24576
#define OCTAV_POS 9
#define OCTAV_GRAB 7680
#define DOTS_POS 7
#define DOTS_GRAB 384
#define NUMER_POS 7
#define NUMER_GRAB 1920
#define DENOM_POS 1
#define DENOM_GRAB 126
#define TYPE_GRAB 1
    enum elemPiece : u_int8_t {
        e_elemType = 0,
        e_denominator,
        e_dots,
        e_octave,
        e_accidental,
        e_pitch,
        e_chord,
        e_numerator
    };
    //used to convert duration element integer back into its corresponding note/rest object
    int Extract(const unsigned int &element, const elemPiece &ep)const {
        switch (ep){
            case e_elemType:    return (element & TYPE_GRAB);
            case e_denominator: return ( (element & DENOM_GRAB) >> DENOM_POS );
            case e_dots:        return ( (element & DOTS_GRAB)  >> DOTS_POS  );
            case e_octave:      return ( (element & OCTAV_GRAB) >> OCTAV_POS );
            case e_accidental:  return ( (element & ACCID_GRAB) >> ACCID_POS );
            case e_pitch:       return ( (element & PITCH_GRAB) >> PITCH_POS );
            case e_chord:       return ( (element & CHORD_GRAB) >> CHORD_POS );
            case e_numerator:   return ( (element & NUMER_GRAB) >> NUMER_POS );
        }
    }

    SHP_T(Fragment_T) fragment;   //Holds orignal fragment sequence and basis
    void ConvertSequenceToIntSeq();
    void DetermineChangingElements();
    void ChangeDurations();
    void AddElements();
    std::vector<TimeFraction_T> GetPossibleDurations(const TimeFraction_T &tf);
    int  RollTheDie(const int &flr, const int &ceil);

    std::vector<int> originalIntSeq, newIntSeq;
    std::vector<TimeFraction_T> originalDurSeq, newDurSeq;
    std::vector<TimeFraction_T>::iterator newDurSeq_it;
    std::vector<bool>           toChangeOrNot;
    std::vector<bool>::iterator toChangeOrNot_it;
    std::set<TimeFraction_T>    durations;
    std::set<TimeFraction_T>::iterator durations_it;
    std::deque<std::tuple<TimeFraction_T, int, int, bool> > changingSegments;
    std::map<TimeFraction_T, std::set<unsigned int> > durBuckets;
    std::map<TimeFraction_T, std::set<unsigned int> >::iterator durBuckets_it;
    IntBucketVect_T   intBasis;   //holds a smaller memory footprint of the original basis
    IntToShortID_T intToIDmap; //maps element to a unique local id;
    VectDeqBits_T     idsPerChord;
    //BitWiseStack16_3  currentChordSequence; //keeps track of most recently used sequence of notes
    //BitWiseDeque64<u_int64_t, 13> currentElemSequence;
    TimeFraction_T    graphDepth;      //holds current time depth of graph
    unsigned long long edgeCount;
    int nodeDepth;
    /*
     * first pass:
     *  * determine next possible nodes and save in a stack
     */
public:
    unsigned long iteration;
    void PrintIntToElement(const unsigned int) const;
    HyperGraph_T      graph;    //creates a power set variant

    Instantiate_T(SHP_T(Fragment_T) f);

    void ConvertDurationBasisToInt();
    const std::deque<unsigned int> GetNotes(const std::string &pitch);
    int ConvertNoteToInt(const Note_T &note);
    int ConvertRestToInt(const Duration_T &rest);
    //std::bitset<MAX_BIT_STRNG_LENGTH> SequenceToIDSequence();
    void Instantiate();
    //void ExtractElementDuration(TimeFraction_T &duration, const unsigned int &element);
    void DotModify(TimeFraction_T &duration, const int& dots);


};

/*
 *
 *
 */


#endif //MUSICSYNTHESIS_V2_INSTANTIATE_H
