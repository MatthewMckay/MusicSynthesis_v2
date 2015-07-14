//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_FRAGMENT_H
#define MUSICSYNTHESIS_V2_FRAGMENT_H
#include <iostream>
#include <vector>
#include <string>

#include "XmlDomDocument_T.h"
#include "Duration/Duration.h"
#include "Duration/Note.h"
#include "Duration/Rest.h"
#include "Basis.h"

class Fragment_T {
private:
    VectSHPdur_T seqFrag;
    Basis_T basis;
public:
    Fragment_T(){}
    ~Fragment_T(){};
    void AddElement(SHP_T(Duration_T) elem) { seqFrag.push_back(elem);}
    void GenerateBasis();
};


#endif //MUSICSYNTHESIS_V2_FRAGMENT_H
