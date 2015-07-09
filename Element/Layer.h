//
// Created by Matthew McKay on 7/3/15.
//

#ifndef MUSICSYNTHESIS_V2_LAYER_H
#define MUSICSYNTHESIS_V2_LAYER_H

#include <vector>
#include <string>
#include <iostream>

#include "../Constants.h"
#include "../Duration/Duration.h"
#include "../Duration/Note.h"
#include "../Duration/Chord.h"
#include "../Duration/Rest.h"
#include "../Duration/MeasureRest.h"
#include "../Duration/MeasureSpace.h"
#include "../Duration/MultiMeasureRest_T.h"

class Layer_T {
    friend class Processing_T;
private:
    std::vector<SHP(Duration_T)> sequence;
    std::string n;
public:
    friend std::ostream& operator<< (std::ostream& ostr, const Layer_T& layer){
        #define LS layer.sequence
        ostr << "\t  LAYER:  n = ";
        if (layer.n.empty()) ostr << "UNDEFINED\n";
        else ostr << layer.n << '\n';
        for (int i = 0; i < LS.size(); ++i){
            if (LS[i]->GetType() == "chord") ostr << *SPC(Chord_T)(LS[i]);
            else if (LS[i]->GetType() == "note") ostr << *SPC(Note_T)(LS[i]);
            else if (LS[i]->GetType() == "rest") ostr << *SPC(Rest_T)(LS[i]);
            else if (LS[i]->GetType() == "mRest") ostr << *SPC(MeasureRest_T)(LS[i]);
            else if (LS[i]->GetType() == "mspace") ostr << *SPC(MeasureSpace_T)(LS[i]);
            else if (LS[i]->GetType() == "multiRest") ostr << *SPC(MultiMeasureRest_T)(LS[i]);
            else ostr << *(LS[i]);
        }
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_LAYER_H
