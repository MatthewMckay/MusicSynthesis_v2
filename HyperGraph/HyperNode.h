//
// Created by Matthew McKay on 7/14/15.
//

#ifndef MUSICSYNTHESIS_V2_HYPERNODE_H
#define MUSICSYNTHESIS_V2_HYPERNODE_H

#include <iostream>
#include <vector>

#include "HyperEdge.h"

template <class T, class A>
class HyperNode_T {
public:
    typedef std::vector<HyperEdge_T<A>> vHypeE;
    T      data;
    int    id;
    vHypeE edges;
};


#endif //MUSICSYNTHESIS_V2_HYPERNODE_H
