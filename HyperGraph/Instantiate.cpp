//
// Created by Matthew McKay on 8/1/15.
//

#include "Instantiate.h"

/*
 * read basis
 * convert duration objects into integer representations
 * assign an id
 * sort into buckets according to size
 */
Instantiate_T::Instantiate_T(SHP_T(Fragment_T) f) : fragment(f) {
    edgeCount = 0;
    //each bucket holds all notes of a certain pitch a-g or all rests
    std::vector<unsigned int> bucket;
    for (int i = 0; i < 8; ++i) {
        intBasis.push_back(bucket);
    }
    //duration elements are really big, this converts them into an unsigned integer
    ConvertDurationBasisToInt();
    short id = -1;
    for (auto item : intBasis) {
        for (auto subitem : item){
            intToIDmap.insert( {subitem, ++id} );
            graph.AddNode(subitem, id);
        }
    }
    ConvertSequenceToIntSeq();
    DetermineChangingElements();
    ChangeDurations();
    AddElements();
    for (auto item : newIntSeq){PrintIntToElement(item);}

    //sort nodes into buckets


  /*  int head = ConvertNoteToInt(*SPC_(Note_T)(fragment->seqFrag.front()));
    int tail = ConvertNoteToInt(*SPC_(Note_T)(fragment->seqFrag.back()));
    currentElemSequence.push_back(head);
    TimeFraction_T tf(1, Extract(head, e_denominator));
    DotModify(tf, e_dots);
    graphDepth += tf;
    currentElemSequence.push_back(tail);
    tf.numerator = 1;
    tf.denominator = Extract(tail, e_denominator);
    graphDepth += tf;*/
}

/*
 * retrieves all notes of the specified pitch and accidental
 */
const std::deque<unsigned int> Instantiate_T::GetNotes(const std::string & pitch) {
    std::deque<unsigned int> notes;
    int pitchNum = pitch[0]-'a';
    for (auto note : intBasis[pitchNum]) {
        int8_t accidType;
        switch(pitch[1]){
            case 'f' : accidType = 2;
                break;
            case 's' : accidType = 3;
                break;
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
            unsigned int intRep = 0;
            Note_T note = *SPC_(Note_T)(item);
            intRep = ConvertNoteToInt(note);
            if (note.chordProg) intRep-=note.chordProg << CHORD_POS;
            //intRep -= Extract(intRep, e_chord) << CHORD_POS;
            //puts each "pitched" note into its own bucket
            if (note.GetPitch() == 'a')  intBasis[0].push_back(intRep);
            else if (note.GetPitch() == 'b') intBasis[1].push_back(intRep);
            else if (note.GetPitch() == 'c') intBasis[2].push_back(intRep);
            else if (note.GetPitch() == 'd') intBasis[3].push_back(intRep);
            else if (note.GetPitch() == 'e') intBasis[4].push_back(intRep);
            else if (note.GetPitch() == 'f') intBasis[5].push_back(intRep);
            else intBasis[6].push_back(intRep);
            durBuckets_it = durBuckets.find(note.GetDurationFraction());
            if (durBuckets_it != durBuckets.end()){
                durBuckets_it->second.insert(intRep);
            }
            else{
                std::set<unsigned int> temp;
                temp.insert(intRep);
                durBuckets.insert(std::make_pair(note.GetDurationFraction(), temp));
                durations.insert(note.GetDurationFraction());
            }
        }
        else {
            unsigned int intRep = ConvertRestToInt(*item);
            intBasis[7].push_back( intRep );
            durBuckets_it = durBuckets.find(item->GetDurationFraction());
            if (durBuckets_it != durBuckets.end()){
                durBuckets_it->second.insert(intRep);
            }
            else{
                std::set<unsigned int> temp;
                temp.insert(intRep);
                durBuckets.insert(std::make_pair(item->GetDurationFraction(), temp));
                durations.insert(item->GetDurationFraction());
            }
        }
    }
    for (auto item : intBasis){
        for(auto subitem : item){
            //std::cout<<std::setw(10)<<std::setfill(' ')<<subitem<<"    ";
        }
    }
}

/*
 * converts notes to integers
 */
int Instantiate_T::ConvertNoteToInt(const Note_T &note) {
    int noteRep = 0;
    noteRep += ( (tolower(note.GetPitch()) - 'a') << PITCH_POS )
               +  ( note.GetOctave()   << OCTAV_POS )
               +  ( note.GetDots()     << DOTS_POS )
               +  ( note.ReverseDotModify().denominator << DENOM_POS );
    if (note.chordProg) {
        noteRep+=note.chordProg << CHORD_POS;
    }
    switch (note.GetAccidental()[0]){
        case 'f': noteRep += 16385;
            break;
        case 's': noteRep += 24576;
            break;
        default : noteRep += 8192;
    }
    return noteRep;
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

void Instantiate_T::ConvertSequenceToIntSeq() {
    for (auto item : fragment->seqFrag){
        if (item->type == "note"){
            Note_T note = *SPC_(Note_T)(item);
            int noteInt = ConvertNoteToInt(note);
            originalIntSeq.push_back(noteInt);
            TimeFraction_T tf = note.GetDurationFraction();
            originalDurSeq.push_back(tf);
        }
        else {
            Rest_T rest = *SPC_(Rest_T)(item);
            int restInt = ConvertRestToInt(rest);
            originalIntSeq.push_back(restInt);
            TimeFraction_T tf = rest.duration;
            originalDurSeq.push_back(tf);
        }
    }
    /*cout << "\n\noriginal int sequence:\n";
    for (auto item : originalIntSeq){
        PrintIntToElement(item);
    }
    cout<<"\n\n\n";*/
}

void Instantiate_T::DetermineChangingElements() {
    toChangeOrNot.push_back(0);
    for (int i = 1; i < originalIntSeq.size() - 2; ++i) {
        toChangeOrNot.push_back(RollTheDie(0, 1));
    }
    toChangeOrNot.push_back(0);
    for (int i = 1; i < toChangeOrNot.size() - 1; ++i) {
        if (toChangeOrNot[i]) {
            TimeFraction_T totalTime(0, 1), zeroTf(0, 1);
            int k = 0;
            int startPos = i;
            while (toChangeOrNot[i]) {
                TimeFraction_T temp = originalDurSeq[i];
                if (temp.numerator > 1 && temp.denominator > 1) {
                    if (totalTime == zeroTf) {
                        changingSegments.push_back(std::make_tuple(temp, startPos, 1, 1));
                    }
                    else {
                        changingSegments.push_back(std::make_tuple(totalTime, startPos, k, 0));
                        changingSegments.push_back(std::make_tuple(temp, i, 1, 1));
                        totalTime.numerator = 0;
                        totalTime.denominator = 1;
                        k = 0;
                    }
                }
                else {
                    totalTime += temp;
                    ++k;
                }
                ++i;
            }
            changingSegments.push_back(std::make_tuple(totalTime, startPos, k, 0));
        }
    }
}
void Instantiate_T::ChangeDurations(){
    /*cout <<endl<<toChangeOrNot.size()<<endl;
    for (int i = 0; i < toChangeOrNot.size(); ++i){
        std::cout << toChangeOrNot[i] << "  ";
    }
    std::cout << "\n\n";*/
    int itemCountDifference = 0;
    newDurSeq = originalDurSeq;
    newIntSeq = originalIntSeq;
    /*for (auto item : durBuckets){
        cout << item.first <<endl;
        for (auto subitem : item.second){
            cout << subitem << "  ";
        }
        cout <<endl<<endl;
    }*/
    for (auto item : changingSegments) {
        //this can only be a note
        if (get<3>(item)) {
            //do nothing
        }
        else {
            //randomly add lengths that sum up to the original duration, adjust the item count accordingly
            //remove changing elements
            //get possible lengths
            //randomly pick one
            //subtract from total length
            //repeat until 0
            newDurSeq.erase(newDurSeq.begin() + get<1>(item) + itemCountDifference,
                            newDurSeq.begin() + get<1>(item) + get<2>(item) + itemCountDifference);
            newIntSeq.erase(newIntSeq.begin() + get<1>(item) + itemCountDifference,
                                newIntSeq.begin() + get<1>(item) + get<2>(item) + itemCountDifference);
            toChangeOrNot.erase(toChangeOrNot.begin() + get<1>(item) + itemCountDifference,
                            toChangeOrNot.begin() + get<1>(item) + get<2>(item) + itemCountDifference);
            TimeFraction_T timeLeft = get<0>(item), zeroTf(0, 1);
            //std::cout<<timeLeft<<std::endl;
            while (timeLeft > zeroTf) {
                //std::cout << "timeLeft: "<< timeLeft << std::endl;
                std::vector<TimeFraction_T> possibleDurations = GetPossibleDurations(timeLeft);
                int durationPick = RollTheDie(1, possibleDurations.size())-1;
                newDurSeq.insert(newDurSeq.begin() + get<1>(item) + itemCountDifference,
                                 possibleDurations[durationPick]);
                toChangeOrNot.insert(toChangeOrNot.begin() + get<1>(item) + itemCountDifference, 1);
                newIntSeq.insert(newIntSeq.begin() + get<1>(item) + itemCountDifference, 0);
                itemCountDifference++;
                timeLeft -= possibleDurations[durationPick];
            }
            itemCountDifference -= get<2>(item);
        }
    }
    /*std::cout << "\n\n\n";
    for (auto item : originalIntSeq){
        std::cout << item << "  ";
    }
    std::cout << '\n';
    for (auto item : originalDurSeq){
        std::cout << item << "  ";
    }
    std::cout << '\n';
    for (int k = 0; k < toChangeOrNot.size(); ++k){
        std::cout << toChangeOrNot[k] << "  ";
    }
    std::cout << '\n';
    std::cout << "\n\n\n";
    for (auto item : newIntSeq){
        std::cout << item << "  ";
    }
    std::cout << '\n';
    for (auto item : newDurSeq){
        std::cout << item << "  ";
    }
    std::cout << '\n';

    for (int i = 0; i < newIntSeq.size()-1; ++i){
        PrintIntToElement(newIntSeq[i]);
        std::cout << std::endl;
    }*/
}

void Instantiate_T::AddElements(){
    for (int seqIndex = 0; seqIndex < newIntSeq.size(); ++seqIndex) {
        //cout<<Extract(originalIntSeq[seqIndex], e_chord)<<endl;
        if (!newIntSeq[seqIndex]) {
            std::vector<std::vector<unsigned int> > durPitchVect;
            std::vector<unsigned int> pitchVect;
            for (int i = 0; i < 7; ++i) durPitchVect.push_back(pitchVect);
            durBuckets_it = durBuckets.find(newDurSeq[seqIndex]);
            if (durBuckets_it != durBuckets.end()) {
                for (auto element : durBuckets_it->second) {
                    //cout << Extract(element, e_pitch)<<"  ";
                    if (Extract(element, e_elemType)) {
                        durPitchVect[7].push_back(element);
                        PrintIntToElement(element);
                    }
                    else {
                        durPitchVect[Extract(element, e_pitch)].push_back(element);
                        PrintIntToElement(element);
                    }
                }
            }
            int lastChord = fragment->GetNextPossibleChords(Extract(newIntSeq[seqIndex-1], e_chord));
            //cout<<"before condition LastChord: "<<Extract(newIntSeq[seqIndex-1], e_chord)<<endl;
            if (newIntSeq[seqIndex+1]){
                //cout<<"condition 1\n";
                int nextChord = fragment->GetPreviousPossibleChords(Extract(newIntSeq[seqIndex+1], e_chord));
                cout<<"lastChord: " <<lastChord<<" nextChord: "<< nextChord<<" last & next: "<<(lastChord & nextChord)<<endl;
                int possibleChords = lastChord & nextChord;
                //cout<<lastChord<<"  "<<nextChord<<"  "<<possibleChords<<endl;
                vector<int> poss_chords;
                while (possibleChords){
                    if (possibleChords & 7) poss_chords.push_back(possibleChords & 7);
                    cout << (possibleChords & 7) << " ";
                    possibleChords >>= 3;
                }
                cout << "\nposs chords: ";
                for (auto x : poss_chords){
                    cout << x << "  ";
                }
                cout <<endl;
                //cout<<"\ngot chords"<<poss_chords.size()<<"\n";
                int chosenChord = poss_chords[RollTheDie(0,poss_chords.size()-1)];
                //cout<<"chose chord"<<chosenChord<<"\n";
                cout<<"chosen chord: "<<chosenChord<<endl;
                std::vector<int> possibleNotes = fragment->GetNextPossibleNotes(chosenChord);
                cout << "possible Notes: ";
                for (auto x : possibleNotes) cout <<x<<" ";
                cout <<endl;
                //cout<<"got possible notes\n";
                int chosenNote = possibleNotes[RollTheDie(0,possibleNotes.size()-1)];
                //cout<<"chose note\n";
                cout<<"chosen note: "<<chosenNote<<endl;
                chosenNote = durPitchVect[chosenNote][RollTheDie(0,durPitchVect[chosenNote].size()-1) ];
                cout<<"chosen note: "<<chosenNote;
                PrintIntToElement(chosenNote);
                //cout<<"note selected\n";
                chosenNote += chosenChord << CHORD_POS;
                //cout<<"note given chord\n";
                newIntSeq[seqIndex] = chosenNote;
                //cout<<chosenNote<<": ";
                //PrintIntToElement(chosenNote);
                //cout<<"completed condition 1\n";
            }
            else{
                //cout<<"condition 2\n";
                vector<int> poss_chords;
                cout<<lastChord<<endl;
                while (lastChord){
                    if (lastChord & 7) poss_chords.push_back(lastChord & 7);
                    cout << (lastChord & 7) << " ";
                    lastChord >>= 3;
                }
                cout << "\nposs chords: ";
                for (auto x : poss_chords){
                    cout << x << "  ";
                }
                cout <<endl;
                //cout<<"got chords"<<poss_chords.size()<<"\n";
                int chosenChord = poss_chords[RollTheDie(0,poss_chords.size()-1)];
                //cout<<"chose chord"<<chosenChord<<"\n";
                cout<<"chosen chord: "<<chosenChord<<endl;
                std::vector<int> possibleNotes = fragment->GetNextPossibleNotes(chosenChord);
                cout << "possible Notes: ";
                for (auto x : possibleNotes) cout <<x<<" ";
                cout <<endl;
                //cout<<"got possible notes\n";
                int chosenNote = possibleNotes[RollTheDie(0,possibleNotes.size()-1)];
                //cout<<"chose note\n";
                cout<<"chosen note: "<<chosenNote<<endl;
                chosenNote = durPitchVect[chosenNote][RollTheDie(0,durPitchVect[chosenNote].size()-1) ];
                cout<<"chosen note: "<<chosenNote;
                PrintIntToElement(chosenNote);
                //cout<<"note selected\n";
                //cout<<chosenChord<<" -> ";
                chosenNote += chosenChord << CHORD_POS;
                //cout<<"note given chord\n";
                newIntSeq[seqIndex] = chosenNote;
                //cout<<chosenNote<<": ";
                //PrintIntToElement(chosenNote);
                //cout<<"completed condition 2\n";
            }
            /*for (int i = 0; i < newIntSeq.size(); ++i){
                std::cout<<newIntSeq[i]<<"  ";
            }
            std::cout << std::endl;*/
        }
    }
    /*for (int i = 0; i < newIntSeq.size(); ++i){
        PrintIntToElement(newIntSeq[i]);
    }*/
};

int Instantiate_T::RollTheDie(const int &flr, const int &ceil) {
    std::random_device generator;
    cout << "floor: "<<flr<<" ceiling: "<<ceil<<endl;
    if (flr == 0){
        if (ceil == 1) return generator() % 2;
        else return generator() % (ceil + 1);
    }
    else return generator() % (ceil - flr + 1) + flr;
}

std::vector<TimeFraction_T> Instantiate_T::GetPossibleDurations(const TimeFraction_T &tf) {
    std::vector<TimeFraction_T> rvals;
    durations_it = durations.begin();
    while (*durations_it <= tf && durations_it != durations.end()) ++durations_it;
    while (durations_it != durations.begin()){
        --durations_it;
        if (durations_it->numerator > 1 && durations_it->denominator > 1){}
        else {
            rvals.push_back(*durations_it);
        }
    }
    return rvals;
}

void Instantiate_T::PrintIntToElement(const unsigned int i) const {
    if (Extract(i,e_elemType)) {
        Rest_T rest;
        rest.SetDuration(Extract(i,e_numerator),Extract(i,e_denominator));
        std::cout << rest << std::endl;
    }
    else {
        Note_T note;
        note.SetPitch(Extract(i, e_pitch) + 'a');
        switch (Extract(i, e_accidental)) {
            case  2:
                note.SetAccidental("f");
                break;
            case  3:
                note.SetAccidental("s");
            default:
                note.SetAccidental("n");
        }
        note.SetOctave(Extract(i, e_octave));
        note.SetDots(Extract(i, e_dots));
        note.SetDuration(Extract(i, e_denominator));
        std::cout << note << std::endl;
    }
}
