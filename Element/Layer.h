//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_LAYER_H
#define MUSICSYNTHESIS_V2_LAYER_H

#include <vector>
#include <string>

#include "../Duration/Duration.h"
#include "../Duration/Chord.h"
#include "../Duration/Note.h"
#include "../Duration/Rest.h"
#include "../Duration/MeasureRest.h"
#include "../Duration/MeasureSpace.h"
#include "../Duration/MultiMeasureRest_T.h"

class Layer_T {
    friend class Staff_T;
private:
    std::vector<Duration_T> sequence;
    std::string n;
};


#endif //MUSICSYNTHESIS_V2_LAYER_H
