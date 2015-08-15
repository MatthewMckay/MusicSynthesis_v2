//
// Created by Matthew McKay on 7/14/15.
//

#ifndef MUSICSYNTHESIS_V2_HYPERGRAPH_H
#define MUSICSYNTHESIS_V2_HYPERGRAPH_H
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>

#include "../Constants.h"
#include "HyperEdge.h"
#include "HyperNode.h"
#include "../Constants.h"
#include "../KeySignatureDefault.h"
#include "../Duration/TimeFraction.h"
#include "../Duration/Duration.h"
#include "../Duration/Note.h"
#include "../Duration/Chord.h"
#include "../Duration/Rest.h"
#include "../Duration/MeasureRest.h"
#include "../Duration/MeasureSpace.h"
#include "../Duration/MultiMeasureRest_T.h"

#include "../Fragment.h"


class HyperGraph_T {
private:
    unsigned int Extract(unsigned int num, const int &digit, const int &count) {
        if (digit > 1) num /= (unsigned int) pow(10, digit - 1);
        num %= (unsigned int) pow(10, count);
        return num;
    }
    SHP_T(Fragment_T) fragment;
public:
    HyperGraph_T(){}

    typedef std::vector<HyperNode_T> VHyperN_T;
    VHyperN_T vertices;
    void AddNode(const unsigned int &element, const std::bitset<MAX_ID_BIT_LENGTH> &id);
};


#endif //MUSICSYNTHESIS_V2_HYPERGRAPH_H
