//
// Created by Matthew McKay on 7/2/15.
//

#ifndef MUSICSYNTHESIS_V2_MEASUREREST_H
#define MUSICSYNTHESIS_V2_MEASUREREST_H

#include <iostream>

#include "Duration.h"
#include "Rest.h"

class MeasureRest_T : public Duration_T {
public:
    MeasureRest_T(){type = "mRest";}
    void SetDuration() { duration.numerator = 1; }
    friend std::ostream& operator<< (std::ostream& ostr, const MeasureRest_T& mr) {
        TimeFraction_T tf = mr.GetDurationFraction();
        ostr << "\t\tMEASURE REST:  DURATION = " << tf;
        ostr << "\n";
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_MEASUREREST_H
