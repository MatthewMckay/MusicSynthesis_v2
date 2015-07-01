//
// Created by Matthew McKay on 6/22/15.
//

#include "Rest.h"

void Rest_T::SetDuration(double d) { duration = d; }

double Rest_T::GetDuration() const { return duration; }

std::ostream& operator<< (std::ostream& ostr, Rest_T & rest)
{
    ostr << "DURATION = " << rest.duration;
    ostr << "\n";
    return ostr;
}