//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_FRAGMENT_H
#define MUSICSYNTHESIS_V2_FRAGMENT_H
#include <iostream>
#include <vector>
#include <string>

#include "Constants.h"
#include "KeySignature.h"
#include "XmlDomDocument_T.h"
#include "Duration/Duration.h"
#include "Duration/Note.h"
#include "Duration/Rest.h"
#include "Basis.h"
#include "HyperGraph/HyperGraph.h"

class Fragment_T : public KeySignature_T {
private:
    VectSHPdur_T seqFrag;
    Basis_T basis;
    HyperGraph_T<SHP_T(Duration_T),std::string> hypergraph;
public:
    Fragment_T(){}
    ~Fragment_T(){};

    void AddElement(SHP_T(Duration_T) elem) { seqFrag.push_back(elem);}
    void GenerateBasis();
    void Synthesize();
};


#endif //MUSICSYNTHESIS_V2_FRAGMENT_H
