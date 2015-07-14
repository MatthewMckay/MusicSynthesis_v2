//
// Created by Matthew McKay on 6/22/15.
//

#include "Rest.h"

std::ostream& operator<< (std::ostream& ostr, const Rest_T & rest)
{
    TimeFraction_T tf = rest.GetDurationFraction();
    ostr << "\t\tREST:  DURATION = " << tf;
    ostr << "\n";
    return ostr;
}

/*
 * a rest may be a fraction of a beat or an entire beat
 */
void Rest_T::SetDuration(int d) {
    if (d == 1) duration.numerator = d;
    else {
        duration.numerator = 1;
        duration.denominator = d;
    }
}

void Rest_T::SetDuration(TimeFraction_T tf) { duration = tf; }
