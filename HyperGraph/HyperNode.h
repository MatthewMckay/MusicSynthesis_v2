//
// Created by Matthew McKay on 7/14/15.
//

#ifndef MUSICSYNTHESIS_V2_HYPERNODE_H
#define MUSICSYNTHESIS_V2_HYPERNODE_H

#include <iostream>
#include <set>
#include <initializer_list>

#include "HyperEdge.h"

class HyperNode_T {
public:
    HyperNode_T(const unsigned int element, const u_int16_t unique_id) : data(element), id(unique_id) {}
    std::set<HyperEdge_T> edges;
    unsigned int data;
    u_int16_t id;
    void AddEdge(const BitWiseDeque64<u_int64_t, 13> &edge){
        HyperEdge_T newEdge(edge);
        edges.insert(edge);
    }
};


#endif //MUSICSYNTHESIS_V2_HYPERNODE_H
