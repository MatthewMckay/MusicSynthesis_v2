//
// Created by Matthew McKay on 7/14/15.
//

#include "HyperGraph.h"

void HyperGraph_T::AddNode(const unsigned int &element, const short &id) {
    HyperNode_T node(element, id);
    vertices.push_back(node);
}
