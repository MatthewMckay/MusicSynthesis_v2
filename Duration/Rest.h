//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_REST_H
#define MUSICSYNTHESIS_V2_REST_H


#include <iostream>

#include "Duration.h"

class Rest_T : public Duration_T {
public:
    Rest_T(){}
    virtual void SetDuration(int d);

    friend std::ostream& operator<< (std::ostream& ostr, const Rest_T & rest);
};


#endif //MUSICSYNTHESIS_V2_REST_H
