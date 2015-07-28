//
// Created by Matthew McKay on 7/2/15.
//

#ifndef MUSICSYNTHESIS_V2_MULTIMEASUREREST_H
#define MUSICSYNTHESIS_V2_MULTIMEASUREREST_H

#include <iostream>

#include "TimeFraction.h"
#include "Duration.h"
#include "Rest.h"


/**
 * MultiMeasureRest_T accounts for rests over multiple measures
 * this is a subclass of Rest_T
 */
class MultiMeasureRest_T : public Rest_T{
public:
    //Because all duration elements are casted to SHP(Duration_T) to preserve order, Duration_T has the field "type" to
    //reference in order to cast the pointer back to its original type. all MultiMeasureRest_T have type = "multiRest"
    MultiMeasureRest_T(int n, int d){
        duration.numerator = n;
        duration.denominator = d;
        type = "multiRest";
    }

    //time fraction are initialized to 0/1 so the numerator is change to "n" to indicate "n" whole measures
    void SetDuration(int n) { duration.numerator *= n; }

    friend std::ostream& operator<< (std::ostream& ostr, const MultiMeasureRest_T& mmr) {
        TimeFraction_T tf = mmr.GetDurationFraction();
        ostr << "\t\tMULTI-MEASURE REST:  DURATION = " << tf;
        ostr << "\n";
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_MULTIMEASUREREST_H
