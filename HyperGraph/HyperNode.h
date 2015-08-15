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
    HyperNode_T(const unsigned int element, const std::bitset<MAX_ID_BIT_LENGTH> unique_id) : data(element), id(unique_id) {}
    std::set<HyperEdge_T> edges;
    unsigned int data;
    std::bitset<MAX_ID_BIT_LENGTH> id;
    void AddEdge(const std::bitset<MAX_BIT_STRNG_LENGTH> &edge){
        HyperEdge_T newEdge(edge);
        edges.insert(edge);
    }
};


#endif //MUSICSYNTHESIS_V2_HYPERNODE_H
