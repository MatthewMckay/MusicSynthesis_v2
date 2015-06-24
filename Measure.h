//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_MEASURE_H
#define MUSICSYNTHESIS_V2_MEASURE_H

#include <iostream>
#include <vector>

#include "Note.h"
#include "Rest.h"

class MEASURE {
private:
    //keeps track of the order of notes and rests
    std::vector<std::pair<char, int>> order;
    std::vector<NOTE> notes;
    std::vector<REST> rests;
public:
    MEASURE();
    ~MEASURE();

    void UpdateOrder(char mType, unsigned long pos);
    void InsertNote(char p, char a, int o, double d);
    void InsertRest(double d);

    std::vector<NOTE> GetNotes();
    std::vector<REST> GetRests();

    friend std::ostream& operator<< (std::ostream& ostr, MEASURE& measure);
};


#endif //MUSICSYNTHESIS_V2_MEASURE_H
