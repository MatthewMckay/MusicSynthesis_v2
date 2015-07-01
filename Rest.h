//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_REST_H
#define MUSICSYNTHESIS_V2_REST_H


#include <iostream>

#include "Duration.h"

class Rest_T : public Duration_T {
private:
    double duration;
public:
    Rest_T() : duration(-1) {};
    Rest_T(double d) : duration(d) {};
    ~Rest_T(){};

    void SetDuration(double d);

    double GetDuration() const;

    friend std::ostream& operator<< (std::ostream& ostr, Rest_T & rest);
};


#endif //MUSICSYNTHESIS_V2_REST_H
