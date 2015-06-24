//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_BASIS_H
#define MUSICSYNTHESIS_V2_BASIS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <boost/any.hpp>
#include <boost/intrusive/rbtree.hpp>

#include "Note.h"
#include "Rest.h"
#include "Type.h"
#include "RBTree.h"

typedef X<char>   xc;
typedef X<int>    xi;
typedef X<double> xd;
typedef boost::intrusive::rbtree<xc>   crbTree;
typedef boost::intrusive::rbtree<xi>    irbTree;
typedef boost::intrusive::rbtree<xd> drbTree;

class BASIS {
private:
    crbTree pitches;
    std::vector<xc> ps;
    crbTree accidentals;
    std::vector<xc> as;
    irbTree octaves;
    std::vector<xi> os;
    drbTree noteDurations;
    std::vector<xd> dns;
    drbTree restDurations;
    std::vector<xd> drs;
    NOTE newNote;
    std::vector<NOTE> * noteBasis;
    std::vector<REST> * restBasis;
    void sortIntoCategories(NOTE note);
    void sortIntoCategoriesR(REST rest);
    BASIS(){};
public:
    BASIS(std::vector<NOTE> * sNotes, std::vector<REST> * sRests);
    ~BASIS(){pitches.clear(); accidentals.clear(); octaves.clear(); noteDurations.clear(); restDurations.clear(); delete noteBasis;}

    void nBasis1();
    /*void InsertNote(char p, char a, int o, double d);
    void InsertRest(double d);

    std::vector<NOTE> GetNotes();
    std::vector<REST> GetRests();*/
};


#endif //MUSICSYNTHESIS_V2_BASIS_H
