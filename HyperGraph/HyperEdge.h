//
// Created by Matthew McKay on 7/14/15.
//

#ifndef MUSICSYNTHESIS_V2_HYPEREDGE_H
#define MUSICSYNTHESIS_V2_HYPEREDGE_H
#include <iostream>
#include <vector>

class HyperEdge_T {
public:
    typedef std::vector<unsigned long> vUsLong_T;

    //****************** variables
    unsigned long  targetNode;
    vUsLong_T sourceNodes;

    //****************** methods
};


#endif //MUSICSYNTHESIS_V2_HYPEREDGE_H
