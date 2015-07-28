//
// Created by Matthew McKay on 6/22/15.
//

#include "Fragment.h"

void Fragment_T::GenerateBasis() {
    for (auto it = seqFrag.begin(); it != seqFrag.end(); ++it){
        basis.InputElem(*it);
    }
    basis.MakeBasis();
    std::cout << basis << "\n\n\n";
}

void Fragment_T::Synthesize() {
    hypergraph.AddNode(seqFrag[0]);
    hypergraph.AddNode(seqFrag[1]);
    std::string str;
    if (seqFrag[1]->GetType() == "note") {
        str = SPC_(Note_T)(seqFrag[0])->GetPitch();
        str += SPC_(Note_T)(seqFrag[0])->GetAccidental();
        DetermineCurrentChord(str);
    }

}