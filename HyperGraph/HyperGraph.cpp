//
// Created by Matthew McKay on 7/14/15.
//

#include "HyperGraph.h"
unsigned int HyperGraph_T::AddNode(const std::vector<unsigned int> &sequence){
    HyperNode_T node(sequence);
    vertices.push_back(node);
    return (unsigned int) vertices.size() - 1;
}
