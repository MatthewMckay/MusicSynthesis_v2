//
// Created by Matthew McKay on 7/14/15.
//

#ifndef MUSICSYNTHESIS_V2_HYPERGRAPH_H
#define MUSICSYNTHESIS_V2_HYPERGRAPH_H
#include <iostream>
#include <vector>

#include "../Constants.h"
#include "HyperEdge.h"
#include "HyperNode.h"

template <class T, class A>
class HyperGraph_T {
public:
    typedef std::vector<HyperNode_T<T,A>> vHypeN_T;
    vHypeN_T vertices;
    IntBool_T AddNode(const T &inputData);
};


#endif //MUSICSYNTHESIS_V2_HYPERGRAPH_H
