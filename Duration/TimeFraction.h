//
// Created by Matthew McKay on 7/9/15.
//

#ifndef MUSICSYNTHESIS_V2_TIMEFRACTION_H
#define MUSICSYNTHESIS_V2_TIMEFRACTION_H

#include <iostream>

#include "../Constants.h"

/**
 * rests use integers in two ways to represent time. for rests within a measure they indicate the denominator (the
 * same way notes use them). mRests, multiRests, and mSpaces use them to indicate whole measures (the numerator)
 * initialize all durations to zero time
 * overload the operator==, operator <, operator >
 */

struct TimeFraction_T {
public:
    int numerator;
    int denominator;

    //intializes all new durations to 0;
    TimeFraction_T() : numerator(0), denominator(1) {}

    //***************************************************************************** comparison operators
    friend bool operator== (const TimeFraction_T& lhs, const TimeFraction_T& rhs) {
        return (double)lhs.numerator/(double)lhs.denominator ==
               (double)rhs.numerator/(double)rhs.denominator;
    }
    friend bool operator!= (const TimeFraction_T& lhs, const TimeFraction_T& rhs) {
        return (double)lhs.numerator/(double)lhs.denominator !=
               (double)rhs.numerator/(double)rhs.denominator;
    }
    friend bool operator> (const TimeFraction_T& lhs, const TimeFraction_T& rhs) {
        return (double)lhs.numerator/(double)lhs.denominator >
               (double)rhs.numerator/(double)rhs.denominator;
    }
    friend bool operator< (const TimeFraction_T& lhs, const TimeFraction_T& rhs) {
        return (double)lhs.numerator/(double)lhs.denominator <
               (double)rhs.numerator/(double)rhs.denominator;
    }

    //****************************************************************************** stream operator
    friend std::ostream& operator<< (std::ostream& ostr, TimeFraction_T& duration) {
        if (duration.denominator == 1) ostr << duration.numerator;
        else if (duration.numerator > 0)ostr << duration.numerator << "/" << duration.denominator;
        else ostr << ERR_CLRS << "ERR: uncaught invalid duration" << DFLT_CLRS;
        return ostr;
    }
};
#endif //MUSICSYNTHESIS_V2_TIMEFRACTION_H
