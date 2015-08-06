//
// Created by Matthew McKay on 6/22/15.
//

#include "Fragment.h"

void Fragment_T::GenerateBasis() {
    for (auto it = seqFrag.begin(); it != seqFrag.end(); ++it){
        basis.InputElem(*it);
    }
    basis.MakeBasis();
    //std::cout << basis << "\n\n\n";
}