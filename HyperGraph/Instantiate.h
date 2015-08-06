//
// Created by Matthew McKay on 8/1/15.
//

#ifndef MUSICSYNTHESIS_V2_INSTANTIATE_H
#define MUSICSYNTHESIS_V2_INSTANTIATE_H

#include <cmath>
#include <deque>
#include <vector>

#include "../Constants.h"
#include "../Fragment.h"
#include "HyperGraph.h"

template <class T>
class Deque_T : public std::deque<T> {
public:
    Deque_T<T>& operator+= (const Deque_T<T> &rhs){
        for (auto item : rhs){
            this->push_back(item);
        }
        return *this;
    }
};

typedef std::vector<std::vector<int> > IntBucketVect_T;

class Instantiate_T {
private:

    //used to convert duration element integer back into its corresponding note/rest object
    unsigned int Extract(unsigned int num, const int &digit, const int &count) {
        if (digit > 1) num /= (unsigned int) pow(10, digit - 1);
        num %= (unsigned int) pow(10, count);
        return num;
    }

    SHP_T(Fragment_T) fragment; //Holds orignal fragment sequence and basis
    IntBucketVect_T   intBasis; //holds a smaller memory footprint of the original basis
    std::vector<unsigned int>  currentSequence; //keeps track of most recently used sequence of notes
    std::vector<unsigned long> localNodeIndex;
    TimeFraction_T    graphDepth;      //holds current time depth of graph
    /*
     * first pass:
     *  * determine next possible nodes and save in a stack
     */
public:

    HyperGraph_T      graph;    //creates a power set variant

    Instantiate_T(SHP_T(Fragment_T) f);

    void ConvertDurationBasisToInt();
    Deque_T<unsigned int> GetNotes(unsigned int pitch, const int &floor, const int &ceiling);
    unsigned int ConvertNoteToInt(const Note_T &note);
    unsigned int ConvertRestToInt(const Duration_T &rest);
    void Instantiate();

#define PITCH 9,1
#define ACCID 8,1
#define OCT 7,1
#define DOTS 6,1
#define DENOM 2,4
#define NUMER 6,5
};

/*
 *
 *
 */


#endif //MUSICSYNTHESIS_V2_INSTANTIATE_H
