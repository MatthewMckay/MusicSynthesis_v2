//
// Created by Matthew McKay on 7/2/15.
//

#ifndef MUSICSYNTHESIS_V2_MEASUREREST_H
#define MUSICSYNTHESIS_V2_MEASUREREST_H

#include <iostream>

#include "TimeFraction.h"
#include "Duration.h"
#include "Rest.h"

/**
 * MeasureRest_T indicate a rest for an entire measure and is indicated by a symbol in MEI
 */
class MeasureRest_T : public Duration_T {
public:
    //Because all duration elements are casted to SHP(Duration_T) to preserve order, Duration_T has the field "type" to
    //reference in order to cast the pointer back to its original type. all MeasureRest_T have type = "mRest"
    MeasureRest_T(){type = "mRest";}

    //time fraction are initialized to 0/1 so the numerator is change to 1 to indicate 1 whole measure
    void SetDuration() { duration.numerator = 1; }

    friend std::ostream& operator<< (std::ostream& ostr, const MeasureRest_T& mr) {
        TimeFraction_T tf = mr.GetDurationFraction();
        ostr << "\t\tMEASURE REST:  DURATION = " << tf;
        ostr << "\n";
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_MEASUREREST_H
