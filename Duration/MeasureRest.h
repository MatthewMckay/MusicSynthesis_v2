//
// Created by Matthew McKay on 7/2/15.
//

#ifndef MUSICSYNTHESIS_V2_MEASUREREST_H
#define MUSICSYNTHESIS_V2_MEASUREREST_H

#include "Rest.h"
class MeasureRest_T : public Rest_T {
public:
    MeasureRest_T(){}
    void SetDuration() { duration.numerator = 1; }
    friend std::ostream& operator<< (std::ostream& ostr, const MeasureRest_T& mr) {
        ostr << "DURATION = " << mr.GetDurationFraction() << "\n";
    }
};


#endif //MUSICSYNTHESIS_V2_MEASUREREST_H
