//
// Created by Matthew McKay on 7/2/15.
//

#ifndef MUSICSYNTHESIS_V2_MULTIMEASUREREST_H
#define MUSICSYNTHESIS_V2_MULTIMEASUREREST_H

#include <iostream>

#include "Duration.h"
#include "Rest.h"

class MultiMeasureRest_T : public Rest_T{
public:
    MultiMeasureRest_T(){}
    void SetDuration(int n) { duration.numerator = n; }

    friend std::ostream& operator<< (std::ostream& ostr, const MultiMeasureRest_T& mmr) {
        ostr << "DURATION = " << mmr.GetDurationFraction() << "\n";
    }
};


#endif //MUSICSYNTHESIS_V2_MULTIMEASUREREST_H
