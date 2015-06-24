//
// Created by Matthew McKay on 6/22/15.
//

#include "Measure.h"

void MEASURE::UpdateOrder(char mType, unsigned long pos)
{
    order.push_back(std::make_pair(mType, pos));
}

void MEASURE::InsertNote(char p, char a, int o, double d)
{
    NOTE note;
    note.SetPitch(p);
    //todo add functionality to determine default accidental if unspecified
    note.SetAccidental(a);
    note.SetOctave(o);
    note.SetDuration(d);
    UpdateOrder('N', notes.size());
    notes.push_back(note);
}

void MEASURE::InsertRest(double d)
{
    REST rest;
    rest.SetDuration(d);
    UpdateOrder('R', rests.size());
    rests.push_back(rest);
}

std::vector<NOTE> MEASURE::GetNotes() { return notes; }

std::vector<REST> MEASURE::GetRests() { return rests; }

std::ostream& operator<< (std::ostream& ostr, MEASURE& measure)
{
    for ( int i = 0; i < measure.order.size(); i++ )
    {
        if ( measure.order[i].first == 'N' )
        {
            ostr << "NOTE(" << measure.order[i].second << "): ";
            ostr << measure.notes[measure.order[i].second] << "\n";
        }
        else
        {
            ostr << "REST(" << measure.order[i].second << "): ";
            ostr << measure.rests[measure.order[i].second] << "\n";
        }
    }
    return ostr;
}