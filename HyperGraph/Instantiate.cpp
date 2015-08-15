//
// Created by Matthew McKay on 8/1/15.
//

#include "Instantiate.h"

Instantiate_T::Instantiate_T(SHP_T(Fragment_T) f) : fragment(f) {
    //each bucket holds all notes of a certain pitch a-g or all rests
    std::vector<unsigned int> bucket;
    for (int i = 0; i < 8; ++i) {
        intBasis.push_back(bucket);
    }
    //duration elements are really big, this converts them into an unsigned integer
    ConvertDurationBasisToInt();
    //this grabs the first note of the fragment
    short id = -1;
    for (auto item : intBasis) {
        for (auto subitem : item){
            intToIDmap.insert( {subitem, ++id} );
            graph.AddNode(subitem, id);
        }
    }

    //gather appropriate elements for each chord
    for (int i = 0; i < fragment->chordPitches.size(); ++i){
        std::deque<std::bitset<MAX_ID_BIT_LENGTH> > bs;
        idsPerChord.push_back(bs);
        for (int k = 0; k < fragment->chordPitches[i]; ++k){
            for (auto tone : fragment->chordPitches[i]){
                for (auto note : GetNotes(tone)){
                    idsPerChord.back().push_back(note);
                }
            }
            for (auto rest : intBasis[7]){
                idsPerChord.back().push_back(rest);
            }
        }
    }

    Note_T firstFragmentNote = *SPC_(Note_T)(fragment->seqFrag[0]);
    //next we guess which chord the first note is in
    fragment->DetermineCurrentChord(firstFragmentNote.GetPitch() + firstFragmentNote.GetAccidental());



    for (auto item : idsPerChord[fragment->currentChord - 1]) {
        if (Extract(item, elemPiece(e_elemType)) == 1) break;
        else {
            TimeFraction_T duration(1, 1);
            duration.denominator = Extract(item, elemPiece(e_denominator));
            int dots = Extract(item, elemPiece(e_dots));
            DotModify(duration, dots);
            if ( (graphDepth + duration) <= fragment->length ) {
                graphDepth += duration;
                nodeDepth = 0;
                IntToShortID_T::iterator mapIt = intToIDmap.find(item);
                Append(currentElemSequence, mapIt->second, MAX_ID_BIT_LENGTH, nodeDepth);
                Instantiate();
                graphDepth -= duration;
            }
        }
    }
}

/*
 * retrieves all notes of the specified pitch and accidental
 */
const std::vector<int> Instantiate_T::GetNotes(const std::string & pitch) {
    std::vector<int> notes;
    int pitchNum = pitch[0]-'a';
    for (auto note : intBasis[pitchNum]) {
        int8_t accidType;
        switch(pitch[1]){
            case 'f' : accidType = 2;
                break;
            case 's' : accidType = 3;
            default  : accidType = 1;
        }
        if (Extract(note, elemPiece(e_accidental)) == accidType) {
                notes.push_back(note);
        }
    }
    return notes;
}
#include <iomanip>
/*
 * converts all duration elements in the basis to an integer
 */
void Instantiate_T::ConvertDurationBasisToInt() {
    for (auto item : fragment->basis.completeBasis){
        if (item->type == "note") {
            int intRep = 0;
            Note_T note = *SPC_(Note_T)(item);
            intRep = ConvertNoteToInt(note);

            //puts each "pitched" note into its own bucket
            if (note.GetPitch() == 'a')  intBasis[0].push_back(intRep);
            else if (note.GetPitch() == 'b') intBasis[1].push_back(intRep);
            else if (note.GetPitch() == 'c') intBasis[2].push_back(intRep);
            else if (note.GetPitch() == 'd') intBasis[3].push_back(intRep);
            else if (note.GetPitch() == 'e') intBasis[4].push_back(intRep);
            else if (note.GetPitch() == 'f') intBasis[5].push_back(intRep);
            else intBasis[6].push_back(intRep);
        }
        else intBasis[7].push_back( ConvertRestToInt(*item) );
    }
    for (auto item : intBasis){
        for(auto subitem : item){
            std::cout<<std::setw(10)<<std::setfill(' ')<<subitem<<"    ";
        }
        std::cout<<"\n\n";
    }
}

/*
 * converts notes to integers
 */
int Instantiate_T::ConvertNoteToInt(const Note_T &note) {
    int noteRep = 0;
    noteRep += ( (note.GetPitch() - 'a') << PITCH_POS )
               +  ( note.GetOctave()   << OCTAV_POS )
               +  ( note.GetDots()     << DOTS_POS )
               +  ( note.ReverseDotModify().denominator << DENOM_POS );
    switch (note.GetAccidental()[0]){
        case 'f': noteRep += 32768;
            break;
        case 's': noteRep += 49152;
            break;
        default : noteRep += 16384;
    }
    return noteRep
}

/*
 * converts rests to integers
 */
int Instantiate_T::ConvertRestToInt(const Duration_T &rest) {
    int restRep = 1;
    restRep += ( rest.duration.denominator << DENOM_POS )
               +  ( rest.duration.numerator   << NUMER_POS );
    return restRep;
}

/*
 * builds the hypergraph
 */
void Instantiate_T::Instantiate() {
    int8_t previousChord = fragment->currentChord;
    int  nextChords = 0;
    std::vector<int> * temp = new std::vector<int>;
    *temp = fragment->GetNextPossibleChords();
    for (int i = 0; i < temp->size(); ++i){
        nextChords += ( (*temp)[i] << (3 * i) );
    }
    delete temp;

    int8_t nextChord;
    while (nextChords & 7){
        nextChord = nextChords & 7;
        nextChords >>= 3;
        fragment->currentChord = nextChord;
        for (auto item : idsPerChord[nextChord - 1]) {
            TimeFraction_T duration(1, 1);
            duration.denominator = Extract(item, elemPiece(e_denominator));
            int dots = Extract(item, elemPiece(e_dots));
            DotModify(duration, dots);
            if ( (graphDepth + duration) <= fragment->length ) {
                graphDepth += duration;
                nodeDepth++;
                IntToShortID_T::iterator mapIt = intToIDmap.find(item);
                Append(currentElemSequence, mapIt->second, MAX_ID_BIT_LENGTH, nodeDepth);
                Instantiate();
                graphDepth -= duration;
                nodeDepth--;
            }
        }
    }
}

/**
 * dots (number of dots n) modify the original duration (dur) with the following equation
 * dur * (2 - (1 / (2^n))) == dur * ((2^(n+1)-1)/(2^n))
 * TODO add check to avoid double modifications
 */
void Instantiate_T::DotModify(TimeFraction_T &duration, const int& dots ) {
    if ( dots == 0 || duration.numerator > 1) return;
    else{
        duration.numerator = ( duration.numerator << ( dots + 1 ) ) - 1;
        duration.denominator = duration.denominator << dots;
    }
}

void Instantiate_T::ExtractElementDuration(TimeFraction_T &duration, const unsigned int &element) {
    if (Extract(element,1,1) == 0){
        duration.denominator = Extract(element, DENOM);
        int dots = Extract(element,DOTS);
        DotModify(duration, dots);
    }
    else {
        duration.numerator = Extract(element,NUMER);
        duration.denominator = Extract(element,DENOM);
    }
}

std::bitset<MAX_BIT_STRNG_LENGTH> Instantiate_T::SequenceToIDSequence() {
    std::bitset<MAX_BIT_STRNG_LENGTH> sequence;
    IntToShortID_T::iterator mapIt;
    for (int i = 0; i < currentSequence.size()-1; ++i) {
        mapIt = intToIDmap.find(currentSequence[i].second);
        if (mapIt != intToIDmap.end()){
            for (int k = 0; k < MAX_ID_BIT_LENGTH; ++k){
                sequence[i * MAX_ID_BIT_LENGTH + k] = mapIt->second[k];
            }
        }
    }
    return sequence;
}
