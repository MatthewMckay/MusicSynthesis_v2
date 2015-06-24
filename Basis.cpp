//
// Created by Matthew McKay on 6/22/15.
//

#include "Basis.h"
BASIS::BASIS(std::vector<NOTE> *sNotes, std::vector<REST> *sRests)
{
    noteBasis = new std::vector<NOTE>;
    typedef std::unordered_set<char> usc;
    typedef std::unordered_set<int> usi;
    typedef std::unordered_set<double> usd;

    std::cout<<"INPUTTED NOTES:\n";
    usc Pitches;
    usc Accidentals;
    usi Octaves;
    usd NoteDurations;
    usd RestDurations;
    for (unsigned long i = 0; i < sNotes->size(); i++)
    {
        Pitches.insert((*sNotes)[i].GetPitch());
        Accidentals.insert((*sNotes)[i].GetAccidental());
        Octaves.insert((*sNotes)[i].GetOctave());
        NoteDurations.insert((*sNotes)[i].GetDuration());
        //sortIntoCategories((*sNotes)[i]);
        std::cout<<(*sNotes)[i];
    }

 /*   std::cout<<"\n\nINPUTTED RESTS:\n";
    for (unsigned long i = 0; i < sRests->size(); i++)
    {
        sortIntoCategoriesR(sRests->[i]);
        std::cout<<sRests[i];
    }*/
    std::cout<<"\n\nCALCULATING BASIS:\n";
    std::cout<<"UNIQUE PITCHES: " << Pitches.size() << "\n";
    std::cout<<"UNIQUE ACCIDENTALS: " << Accidentals.size() << "\n";
    std::cout<<"UNIQUE OCTAVES: " << Octaves.size() << "\n";
    std::cout<<"UNIQUE DURATIONSS: " << NoteDurations.size() << "\n\n";

    for ( auto pi = Pitches.begin(); pi != Pitches.end(); ++pi){
        for ( auto ai = Accidentals.begin(); ai != Accidentals.end(); ++ai){
            for ( auto oi = Octaves.begin(); oi != Octaves.end(); ++oi){
                for ( auto ndi = NoteDurations.begin(); ndi != NoteDurations.end(); ++ndi){
                    NOTE note(*pi, *ai, *oi, *ndi);
                    noteBasis->push_back(note);
                }
            }
        }
    }
    for ( auto it = noteBasis->begin(); it != noteBasis->end(); ++it ){
        std::cout << *it;
    }
    std::cout << "\n" << noteBasis->size() << " NOTES POSSIBLE\n\n";
}

void BASIS::sortIntoCategories( NOTE note) {
    xc p(note.GetPitch());
    ps.push_back(p);
    pitches.insert_unique(ps[ps.size()-1]);
    xc a(note.GetAccidental());
    as.push_back(a);
    accidentals.insert_unique(as[as.size()-1]);
    xi o(note.GetOctave());
    os.push_back(o);
    octaves.insert_unique(os[os.size()-1]);
    xd d(note.GetDuration());
    dns.push_back(d);
    noteDurations.insert_unique(dns[dns.size()-1]);
}

void BASIS::sortIntoCategoriesR(REST rest) {
    xd d(rest.GetDuration());
    restDurations.insert_unique(d);
}

void BASIS::nBasis1() {
    crbTree::const_iterator p(pitches.begin()), pe(pitches.end());
    crbTree::const_iterator a(accidentals.begin()), ae(accidentals.end());
    irbTree::const_iterator o(octaves.begin()), oe(octaves.end());
    drbTree::const_iterator d(noteDurations.begin()), de(noteDurations.end());
    for (; p != pe; ++p){
        for (; a != ae; ++a){
            for (; o != oe; ++o){
                for (; d != de; ++d){
                    NOTE note((*p).t(), (*a).t(), (*o).t(), (*d).t());
                }
            }
        }
    }
}