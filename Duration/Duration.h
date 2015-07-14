//
// Created by Matthew McKay on 6/24/15.
//

#ifndef MUSICSYNTHESIS_V2_DURATION_H
#define MUSICSYNTHESIS_V2_DURATION_H

#include <iostream>
#include <string>

#include "../Constants.h"
#include "TimeFraction.h"


/**
 * Duration_T is the base class for all notes and rests
 * they all share the fields type and duration
 */
class Duration_T {
//these are protected to allow direct access from subclasses
protected:
    // used to make code more readable
    friend class Processing_T;
    TimeFraction_T duration;    //duration fraction
    std::string type;           //holds subclass type
public:
    Duration_T() {};

    // this returns the duration in decimal form (will be used when creating basis)
    double GetDuration() const { return (double)duration.numerator / (double)duration.denominator; }

    //this returns the duration as a fraction in "MatheType" form
    TimeFraction_T GetDurationFraction() const {return duration; }

    //this returns the type of Duration_T subclass
    std::string GetType() const { return type; }

    //this isn't ever used as is
    virtual void   SetDuration(int n, int d);

    friend std::ostream& operator<< (std::ostream& ostr, const Duration_T& dur) {
        return ostr;
    }
};
typedef std::vector<SHP_T(Duration_T)> VectSHPdur_T;


#endif //MUSICSYNTHESIS_V2_DURATION_H
