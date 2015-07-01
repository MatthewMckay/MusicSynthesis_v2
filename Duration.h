//
// Created by Matthew McKay on 6/24/15.
//

#ifndef MUSICSYNTHESIS_V2_DURATION_H
#define MUSICSYNTHESIS_V2_DURATION_H


class Duration_T {
private:
    double duration;
public:
    /**
     * Duration_T constructor can either set duration to zero time or be initialized with a time
     */
    Duration_T() : duration(0) {};
    Duration_T(double dur) : duration(dur) {};

    double GetDuration() const { return duration; }
    //if Duration_T is instantiated with a time this is invalid
    void   SetDuration(double dur) { if ( duration == 0) duration = dur; }
};


#endif //MUSICSYNTHESIS_V2_DURATION_H
