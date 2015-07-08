//
// Created by Matthew McKay on 6/24/15.
//

#ifndef MUSICSYNTHESIS_V2_DURATION_H
#define MUSICSYNTHESIS_V2_DURATION_H

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
    TimeFraction_T() : numerator(0), denominator(1) {}
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
    friend std::ostream& operator<< (std::ostream& ostr, const TimeFraction_T& duration) {
        if (duration.denominator == 1) ostr << duration.numerator;
        else if (duration.numerator > 0)ostr << duration.numerator << "/" << duration.denominator;
        else ostr << ERR_CLRS << "ERR: uncaught invalid duration" << DFLT_CLRS;
        return ostr;
    }
};

class Duration_T {
protected:
    TimeFraction_T duration;
    friend class Processing_T;
public:
    /**
     * Duration_T constructor set duration to zero time
     */
    Duration_T(){};

    double GetDuration() const { return (double)duration.numerator / (double)duration.denominator; }
    TimeFraction_T GetDurationFraction() const {return duration; }
    //if Duration_T is instantiated with a time this is invalid
    virtual void   SetDuration(int n, int d);
};


#endif //MUSICSYNTHESIS_V2_DURATION_H
