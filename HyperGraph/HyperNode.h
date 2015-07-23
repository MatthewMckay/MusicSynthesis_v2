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
    typedef std::vector<HyperEdge_T<A>> vHypeE_T;
    T      data;
    int    id;
    vHypeE_T edges;
    HyperNode_T(const T& d, int i) : data(d), id(i) {}
};


#endif //MUSICSYNTHESIS_V2_HYPERNODE_H
