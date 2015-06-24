//
// Created by Matthew McKay on 6/22/15.
//

#include "Rest.h"

void REST::SetDuration(double d) { duration = d; }

double REST::GetDuration() { return duration; }

std::ostream& operator<< (std::ostream& ostr, REST& rest)
{
    ostr << "DURATION = " << rest.duration;
    ostr << "\n";
    return ostr;
}