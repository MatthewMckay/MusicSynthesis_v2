//
// Created by Matthew McKay on 7/2/15.
//

#ifndef MUSICSYNTHESIS_V2_MEASURESPACE_H
#define MUSICSYNTHESIS_V2_MEASURESPACE_H

#include <iostream>

#include "TimeFraction.h"
#include "Duration.h"
#include "Rest.h"


//TODO error in logic correct duration fraction. a time fraction indicates a fraction of a note not measure
//TODO utilize time signature (meter count, and meter unit)

/**
 * MeasureSpace_T indicates an empty measure similar to a MeasureRest_T except in appearance in MEI
 */
class MeasureSpace_T : public Rest_T {
public:
    //Because all duration elements are casted to SHP(Duration_T) to preserve order, Duration_T has the field "type" to
    //reference in order to cast the pointer back to its original type. all MeasureSpace_T have type = "mSpace"
    MeasureSpace_T(){type = "mSpace";}

    //time fraction are initialized to 0/1 so the numerator is change to 1 to indicate 1 whole measure
    void SetDuration() {duration.numerator = 1;}

    friend std::ostream& operator<< (std::ostream& ostr, const MeasureSpace_T& ms) {
        TimeFraction_T tf = ms.GetDurationFraction();
        ostr << "\t\tMEASURE SPACE:  DURATION = " << tf;
        ostr << "\n";
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_MEASURESPACE_H
