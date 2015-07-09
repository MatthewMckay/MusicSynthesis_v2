//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_REST_H
#define MUSICSYNTHESIS_V2_REST_H


#include <iostream>

#include "TimeFraction.h"
#include "Duration.h"

/**
 * Rest_T is a subclass of Duration_T and a superclass of MeasureRest_T, MeasureSpace_T, and MultiMeasureRest_T
 * these simply have a duration. The difference is in how they are displayed in MEI and what the int dur changes in the
 * time fraction
 */
class Rest_T : public Duration_T {
public:
    //Because all duration elements are casted to SHP(Duration_T) to preserve order, Duration_T has the field "type" to
    //reference in order to cast the pointer back to its original type. all Rest_T have type = "rest"
    Rest_T(){type = "rest";}
    virtual void SetDuration(int d); //sets the denominator of the time fraction and changes the numerator to 1

    friend std::ostream& operator<< (std::ostream& ostr, const Rest_T & rest);
};


#endif //MUSICSYNTHESIS_V2_REST_H
