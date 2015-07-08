//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_STAFF_H
#define MUSICSYNTHESIS_V2_STAFF_H

#include <vector>
#include <string>

#include "Layer.h"

class Staff_T {
    friend class Processing_T;
private:
    std::vector<Layer_T> layers;
    std::string n;
};


#endif //MUSICSYNTHESIS_V2_STAFF_H
