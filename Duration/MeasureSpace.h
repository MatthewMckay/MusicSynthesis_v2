//
// Created by Matthew McKay on 7/2/15.
//

#ifndef MUSICSYNTHESIS_V2_MEASURESPACE_H
#define MUSICSYNTHESIS_V2_MEASURESPACE_H

#include <iostream>

#include "Duration.h"
#include "Rest.h"

class MeasureSpace_T : public Rest_T {
public:
    MeasureSpace_T(){}
    void SetDuration() {duration.numerator = 1;}
    friend std::ostream& operator<< (std::ostream& ostr, const MeasureSpace_T& ms) {
        ostr << "DURATION = " << ms.GetDurationFraction() << "\n";
    }
};


#endif //MUSICSYNTHESIS_V2_MEASURESPACE_H
