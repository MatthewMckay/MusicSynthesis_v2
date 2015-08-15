//
// Created by Matthew McKay on 7/14/15.
//

#ifndef MUSICSYNTHESIS_V2_HYPEREDGE_H
#define MUSICSYNTHESIS_V2_HYPEREDGE_H
#include <iostream>
#include <bitset>

#include "../Constants.h"

class HyperEdge_T {
#define FIFTY_TWO_BITS 4503599627370495
#define MAX_BIT_PULL 52
public:
    HyperEdge_T(const std::bitset<MAX_BIT_STRNG_LENGTH> sequence) : sourceSequence(sequence) {}

    std::bitset<MAX_BIT_STRNG_LENGTH> sourceSequence;
    //****************** methods

    /*
     * convert a 52bit block of a bitset into an unsigned long given (n-1) block
     */
    unsigned long Get52Bits(const int8_t &n) const{
        // copy the set to preserve the original
        std::bitset<MAX_BIT_STRNG_LENGTH> temp1 = sourceSequence;
        //shift the block to the lowest 52 bits
        temp1 >>= (MAX_BIT_PULL * n);
        //create another bitset to grab the lowest 52 bits
        std::bitset<MAX_BIT_STRNG_LENGTH> temp2 (FIFTY_TWO_BITS);
        temp1 &= temp2;
        return temp1.to_ullong();
    }
    /*
     * bitsets do not have a way to compare bits to other bitsets
     * to know if a bitset is greater, find the most significant set bit that isn't also set in the other
     *   sourceSquence is 468 bits long with 13 bit long blocks.
     *   a 64bit long can hold 4 13bit blocks or 52bits
     *   52 bits into 468bits is 9
     * comparing each individual bit may take at most 468 comparisons
     * converting 52bit blocks to unsigned long integters from most signifcant bit will take at most 9 comparisons
     */
    friend bool operator> (const HyperEdge_T & lhs, const HyperEdge_T & rhs) {
        // start at the 52 most significant bits
        int8_t n = 9; //indicates which of the 9 52bit blocks are being compared

        unsigned long l, r; // holds the converted integers for each iteration;
        //while the sets are equal and there are more bits to compare
        while (n){
            n--; //shifting requires (52 * (n-1)
            l = lhs.Get52Bits(n);
            r = rhs.Get52Bits(n);

            //if either condition is true return the answer
            if (l > r) return true;
            else if (l < r) return false;
        }
        // the sets are equal so return false
        return false;
    }
    friend bool operator< (const HyperEdge_T & lhs, const HyperEdge_T & rhs) {
        int8_t n = 9;
        unsigned long l, r;
        while (n){
            n--;
            l = lhs.Get52Bits(n);
            r = rhs.Get52Bits(n);
            if (l < r) return true;
            else if (l > r) return false;
        }
        return false;
    }
    friend bool operator== (const HyperEdge_T & lhs, const HyperEdge_T & rhs) {
        return lhs.sourceSequence == rhs.sourceSequence;
    }
};


#endif //MUSICSYNTHESIS_V2_HYPEREDGE_H
