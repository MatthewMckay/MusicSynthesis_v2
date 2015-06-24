//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_REST_H
#define MUSICSYNTHESIS_V2_REST_H


#include <iostream>

class REST {
private:
    double duration;
public:
    REST() : duration(-1) {};
    //~REST();

    void SetDuration(double d);

    double GetDuration();

    friend std::ostream& operator<< (std::ostream& ostr, REST& rest);
};


#endif //MUSICSYNTHESIS_V2_REST_H
