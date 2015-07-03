//
// Created by Matthew McKay on 6/22/15.
//

#include "Rest.h"

std::ostream& operator<< (std::ostream& ostr, const Rest_T & rest)
{
    ostr << "DURATION = " << rest.GetDurationFraction();
    ostr << "\n";
    return ostr;
}

void Rest_T::SetDuration(int d) {
    if (d == 1) duration.numerator = d;
    else {
        duration.numerator = 1;
        duration.denominator = d;
    }
}
