//
// Created by Matthew McKay on 7/14/15.
//

#ifndef MUSICSYNTHESIS_V2_HYPERNODE_H
#define MUSICSYNTHESIS_V2_HYPERNODE_H

#include <iostream>
#include <vector>
#include <initializer_list>

#include "HyperEdge.h"

class HyperNode_T {
public:
    HyperNode_T(const std::vector<unsigned int> &seq) : sequence(seq) {
        int x = 5;
        //std::cout<<sequence.size()<<'\n';
        for (auto item : sequence) {
            if (!x) {std::cout<<'\n'; x = 5;}
            x--;
            std::cout<<item<<'\t';
        }
    }
    typedef std::vector<HyperEdge_T> VHyperE_T;
    int    id;
    VHyperE_T edges;
    std::vector<unsigned int> sequence;

    void AddEdge(const std::initializer_list<unsigned long> &antecedent, const unsigned long &consequent){
        HyperEdge_T edge;
        edge.sourceNodes = antecedent;
        edge.targetNode = consequent;
        edges.push_back(edge);
        for (auto item : edge.sourceNodes) { std::cout<<item<<",";}
        std::cout<<" -> "<<edge.targetNode<<"\t\t";
    }
};


#endif //MUSICSYNTHESIS_V2_HYPERNODE_H
