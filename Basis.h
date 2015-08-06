//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_BASIS_H
#define MUSICSYNTHESIS_V2_BASIS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>

#include "Constants.h"
#include "Duration/TimeFraction.h"
#include "Duration/Duration.h"
#include "Duration/Note.h"
#include "Duration/Chord.h"
#include "Duration/Rest.h"
#include "Duration/MeasureRest.h"
#include "Duration/MeasureSpace.h"
#include "Duration/MultiMeasureRest_T.h"
#include "BasisStructs.h"

extern unsigned long long global_shpCt;
class Basis_T {
private:
    typedef std::set<Tone_T> ToneSet_T;
    typedef std::set<int> IntSet_T;
    typedef std::set<Dur_T> DurSet_T;
    typedef std::set<TimeFraction_T> TFset_T;
    ToneSet_T tones;
    IntSet_T  octaves;
    DurSet_T  nDurations;
    TFset_T   rDurations;

public:
    VectSHPdur_T completeBasis;
    void InputElem(SHP_T(Duration_T) elem);
    void MakeBasis();
    void sizes(){
        std::cout << "Tones: ";
        for (auto it = tones.begin(); it != tones.end(); ++it){
            std::cout << it->pitch <<it->accid <<"  ";
        }
        std::cout <<"\nO: ";
        for (auto it = octaves.begin(); it != octaves.end(); ++it) std::cout << *it <<"  ";
        std::cout <<"\ndur: ";
        for (auto it = nDurations.begin(); it != nDurations.end(); ++it){
            std::cout << it->timeFraction << ":" << it->dots << "  ";
        }
        std::cout<<"\nRests: ";
        for (auto it = rDurations.begin(); it != rDurations.end(); ++it){
            std::cout << *it << "  ";
        }
        std::cout << "\n\n\n";
    }
    VectSHPdur_T GetBasis() const { return completeBasis; }
    unsigned long GetTonesSz() const { return tones.size(); }
    unsigned long  GetOctSz() const { return octaves.size(); }
    unsigned long  GetNdurSz() const { return nDurations.size(); }
    unsigned long  GetrDurSz() const { return rDurations.size(); }
    friend std::ostream& operator<< (std::ostream& ostr, const Basis_T &basis){
        ostr << "TONES: " << basis.GetTonesSz() << "  OCTS: " << basis.GetOctSz();
        ostr << "  N_DUR: " << basis.GetNdurSz() << "  R_DUR: " << basis.GetrDurSz();
        ostr << "\nEXPECTED BASIS SIZE: " << basis.GetTonesSz() * basis.GetOctSz() * basis.GetNdurSz() +
                                             basis.GetrDurSz() << "\nGOT: " << basis.GetBasis().size();
        ostr << '\n';
        for (int i = 0; i < basis.completeBasis.size(); i++){
            if ( basis.completeBasis[i]->GetType() == "note" ) ostr << *SPC_(Note_T)(basis.completeBasis[i]);
            else ostr << *SPC_(Rest_T)(basis.completeBasis[i]);
        }
        return ostr;
    }
};


#endif //MUSICSYNTHESIS_V2_BASIS_H
