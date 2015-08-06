//
// Created by Matthew McKay on 8/1/15.
//

#include "Instantiate.h"

Instantiate_T::Instantiate_T(SHP_T(Fragment_T) f) : fragment(f) {
    //each bucket holds all notes of a certain pitch a-g or all rests
    std::vector<int> bucket;
    for (int i = 0; i < 8; ++i) {
        intBasis.push_back(bucket);
    }
    //duration elements are really big, this converts them into an unsigned integer
    ConvertDurationBasisToInt();
    //this grabs the first note of the fragment
    Note_T firstFragmentNote = *SPC_(Note_T)(fragment->seqFrag[0]);
    //next we guess which chord the first note is in
    fragment->DetermineCurrentChord(firstFragmentNote.GetPitch() + firstFragmentNote.GetAccidental());
    //after we know what chord, we can make a list of possible notes
    Deque_T<unsigned int> firstNotes;
    for (auto tone : fragment->GetTonesInCurrentChord()) {
        if (tone.size() > 1){
            switch(tone[1]){
                case 'n' : firstNotes += GetNotes(tone[0]-'a', 0, 1); break;
                case 'f' : firstNotes += GetNotes(tone[0]-'a', 1, 2); break;
                default  : firstNotes += GetNotes(tone[0]-'a', 2, 3);
            }
        }
    }
    //for each possible note make every possible sequence to the specified time depth
    while (firstNotes.size()) {
        TimeFraction_T tf, testLength;//tf holds the time of the next potential element, test length is a temporary way to limit time depth
        testLength.numerator = 1;
        testLength.denominator = 4;
        tf.numerator = 1;
        tf.denominator = Extract(firstNotes[0],DENOM);
        //so long as adding the next element won't go over the desired time depth add the next element to the graph
        if (graphDepth + tf <= testLength) {
            graphDepth += tf;
            currentSequence.push_back(firstNotes[0]);
            localNodeIndex.push_back(graph.AddNode(currentSequence));
            std::cout<<"\n\n\n";
            Instantiate();//continue the sequence
            graphDepth -= tf;
            currentSequence.pop_back();
            localNodeIndex.pop_back();
        }
        firstNotes.pop_front();//Note is used, no longer need to keep track of it
    }
}

/*
 * retrieves all notes of the specified pitch and accidental
 */
Deque_T<unsigned int> Instantiate_T::GetNotes(unsigned int pitch, const int &floor, const int& ceiling) {
    Deque_T<unsigned int> notes;
    int x = 0;
    for (auto note : intBasis[pitch]) {
        //all notes with the same accidental
        if (note > (pitch * 10 + floor) * 10000000 && note < (pitch * 10 + ceiling) * 10000000) {
            notes.push_back(note); x++;
        }
    }
    return notes;
}

/*
 *  Takes the more human readable Note and rest fields and combines them into 1 integer representation
 *         10 9 8 7 6 5 4 3 2 1
 *  Notes:  X X X X X X X X X X
 *            X | | | |       | => Pitch 0 = 'A' -> 6 ='G'
 *              X | | |       | => Accidental 0 ='n'  1='f'  2='s'
 *                X | |       | => Octave 0 -> 9
 *                  X |       | => Dots 0 -> 9
 *                    X X X X | => Duration denominator 2^n -> 2^0 -> 2^10
 *                            X => 0 = Note
 *         10 9 8 7 6 5 4 3 2 1
 *  Rests:  X X X X X X X X X X
 *          X X X X X |       | => Duration numerator
 *                    X X X X | => Duration denominator
 *                            X => 1 = Rest
 */
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
            if (intRep < 100000000) intBasis[0].push_back(intRep);
            else if (intRep < 200000000) intBasis[1].push_back(intRep);
            else if (intRep < 300000000) intBasis[2].push_back(intRep);
            else if (intRep < 400000000) intBasis[3].push_back(intRep);
            else if (intRep < 500000000) intBasis[4].push_back(intRep);
            else if (intRep < 600000000) intBasis[5].push_back(intRep);
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
unsigned int Instantiate_T::ConvertNoteToInt(const Note_T &note) {
    unsigned int intRep = 0;
    intRep += note.ReverseDotModify().denominator * 10//duration
              + note.GetDots() * 100000               //dots
              + note.GetOctave() * 1000000            //octave
              + (tolower(note.GetPitch()) - 'a') * 100000000;//pitch
    switch(note.GetAccidental()[0]) {//accidental
        case 'n' :
            break;
        case 'f' :
            intRep += 10000000;
            break;
        case 's' :
            intRep += 20000000;
            break;
        default  :;
    }
    return intRep;
}

/*
 * converts rests to integers
 */
unsigned int Instantiate_T::ConvertRestToInt(const Duration_T &rest) {
    return 1 + (unsigned)rest.duration.denominator * 10 + (unsigned)rest.duration.numerator * 100000;
}

/*
 * builds the hypergraph
 */
void Instantiate_T::Instantiate() {
    Deque_T<unsigned int> possibleElements;//holds possible next elements
    //gets next possible elements from the key signature object associated with the fragment then from buckets
    for (auto tone: fragment->GetNextPossibleNotes()){
        if (tone.size() > 1){
            switch(tone[1]){
                case 'n' : possibleElements += GetNotes(tone[0]-'a', 0, 1); break;
                case 'f' : possibleElements += GetNotes(tone[0]-'a', 1, 2); break;
                default  : possibleElements += GetNotes(tone[0]-'a', 2, 3);
            }
        }
    }

    unsigned long localParentIndex = localNodeIndex.back(); //keeps track of parent node
    //while there are still elements to try continue building graph
    while (possibleElements.size()){
        TimeFraction_T tf, testLength;
        testLength.numerator = 1;
        testLength.denominator = 4;
        //if a note
        if (Extract(possibleElements[0],0,1) == 0) {
            tf.numerator = 1;
            tf.denominator = Extract(possibleElements[0],DENOM);
            //as long as adding the next element won't exceed the time specified
            if (graphDepth + tf <= testLength){
                graphDepth += tf; //delete time taken by new element
                currentSequence.push_back(possibleElements[0]);
                localNodeIndex.push_back(graph.AddNode(currentSequence));

                //add the edge between parent and child to both the parent and child nodes
                graph.vertices[localParentIndex].AddEdge({localParentIndex}, localNodeIndex.back());
                graph.vertices[localNodeIndex.back()].AddEdge({localParentIndex}, localNodeIndex.back());
                std::cout<<"\n\n";

                Instantiate();//continue sequencing
                currentSequence.pop_back();//the back no longer accurate
                localNodeIndex.pop_back();//the back no longer accurate
                graphDepth -= tf; //we came back to an earlier node, therefore time must be reverted
            }
        }
        else {
            tf.numerator = Extract(possibleElements[0],NUMER);
            tf.denominator = Extract(possibleElements[0],DENOM);
            if (graphDepth + tf <= testLength){
                graphDepth += tf; //delete time taken by new element
                currentSequence.push_back(possibleElements[0]);
                localNodeIndex.push_back(graph.AddNode(currentSequence));

                //add the edge between parent and child to both the parent and child nodes
                graph.vertices[localParentIndex].AddEdge({localParentIndex}, localNodeIndex.back());
                graph.vertices[localNodeIndex.back()].AddEdge({localParentIndex}, localNodeIndex.back());
                std::cout<<"\n\n";

                Instantiate();//continue sequencing
                currentSequence.pop_back();//the back no longer accurate
                localNodeIndex.pop_back();//the back no longer accurate
                graphDepth -= tf; //we came back to an earlier node, therefore time must be reverted
            }
        }
        possibleElements.pop_front();//finished trying element, get rid of it and try the next one
    }
}