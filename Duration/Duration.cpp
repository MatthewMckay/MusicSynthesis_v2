//
// Created by Matthew McKay on 6/24/15.
//

#include "Duration.h"
void Duration_T::SetDuration(int d) {
    if (GetDuration() == 0){
        duration.numerator = n;
        duration.denominator = d;
    }
}
