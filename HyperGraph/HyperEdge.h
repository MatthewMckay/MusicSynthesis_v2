//
// Created by Matthew McKay on 7/14/15.
//

#ifndef MUSICSYNTHESIS_V2_HYPEREDGE_H
#define MUSICSYNTHESIS_V2_HYPEREDGE_H
#include <iostream>
#include <vector>

template <class A>
class HyperEdge_T {
public:
    typedef std::vector<int> vInt;
    int  targetNode;
    vInt sourceNodes;
    A    annotation;
};


#endif //MUSICSYNTHESIS_V2_HYPEREDGE_H
