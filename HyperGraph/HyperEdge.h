//
// Created by Matthew McKay on 7/14/15.
//

#ifndef MUSICSYNTHESIS_V2_HYPEREDGE_H
#define MUSICSYNTHESIS_V2_HYPEREDGE_H
#include <iostream>
#include <bitset>

#include "../Constants.h"
#include "../BitWiseDeque64.h"

class HyperEdge_T {
#define FIFTY_TWO_BITS 4503599627370495
#define MAX_BIT_PULL 52
public:
    HyperEdge_T(const BitWiseDeque64<u_int64_t, 13> sequence) : sourceSequence(sequence) {}

    BitWiseDeque64<u_int64_t, 13> sourceSequence;
    //****************** methods

    friend bool operator> (const HyperEdge_T & lhs, const HyperEdge_T & rhs) {
        return lhs > rhs;
    }
    friend bool operator< (const HyperEdge_T & lhs, const HyperEdge_T & rhs) {
        return lhs < rhs;
    }
    friend bool operator== (const HyperEdge_T & lhs, const HyperEdge_T & rhs) {
        return lhs.sourceSequence == rhs.sourceSequence;
    }
};


#endif //MUSICSYNTHESIS_V2_HYPEREDGE_H
