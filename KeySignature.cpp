//
// Created by Matthew McKay on 7/22/15.
//

#include "KeySignature.h"

//************* static constants
const CAStr_T KeySignature_T::Scale_C SCALE;

const CAInt_T KeySignature_T::ScaleDistRef_C SCALE_DIST;

const CAStr_T KeySignature_T::SharProg_C SHARPS;

const CAStr_T KeySignature_T::FlatProg_C FLATS;

const std::vector<std::vector<int>> KeySignature_T::DiatonicChords_C DIAT_CHORDS;

const std::vector<std::vector<int>> KeySignature_T::DChordW_SamePitch_C D_CHORDS_SAME_PITCH;

const std::vector<int> KeySignature_T::SamePitchPos_C SAME_PITCH_POS;


//******************************************************* Methods

/*
 * keysignature is in a cyclicArray, this used to descramble so "X" - 'a' works
 */
const int KeySignature_T::AdjustedI(int i) const {
    if (i < 0) i = i + keySignature.Size();
    return (i + adjuster) % keySignature.Size();
}


/*
 * sets keySignature, keyMode, adjuster, and chordPitches
 */
KeySignature_T::KeySignature_T(std::string keySig, std::string mode){
    CAStr_T rval SCALE;     //return value, cyclic array initialized to {a,b,c,d,e,f,g}
    keyMode = mode;         //sets key signature mode
    int accidPos = 0;       /* (keySig is in the form  X(s/f) where X is a string integer)
                             * holds accidental spot in string
                             */
    //iterate through the keySig input and find the accidental index
    for (auto i : keySig){
        if (i != 's' && i != 'f') accidPos++;
    }

    //an accidPos < 1 indicates an error
    if ( accidPos > 0 ) {
        //retrieve accidental count
        int accidentalCt = std::stoi(keySig.substr(0, (unsigned long) accidPos));
        //if the accidental has a repeated letter, every letter - 1 is attached to every pitch
        accidentalCt = accidentalCt + (keySig.substr(accidPos, keySig.size() - accidPos).size()-1) * 7;

        //0 indicates C Major or a minor
        if (keySig.length() == 1) {
            if (mode == "major") {
                rval.Shift('c' - 'a');
                adjuster = 'c' - 'a';
            }
            else adjuster = 0;
        }
        //handle sharps
        else if (keySig[accidPos] == 's') {
            CAStr_T temp = SharProg_C;          // f c g d a e b
            for (int i = 0; i < accidentalCt; i++) {
                rval[temp[i][0] - 'a'] += 's';
            }
            if (mode == "major") {              //ex: accidentalCt = 1
                temp.Shift(accidentalCt + 1);   //temp = g d a e b f c
                adjuster = temp[0][0] - 'a';    //'g' - 'a' = 7
            }
            else {
                temp.Shift(accidentalCt + 4);   //temp = e b f c g d a
                adjuster = temp[0][0] - 'a';    //
            }
            rval.Shift(tolower(temp[0][0]) - 'a');
        }
        else if (keySig[accidPos] == 'f') {
            CAStr_T temp = FlatProg_C;          // b e a d g c f
            for (int i = 0; i < accidentalCt; i++) {
                rval[temp[i][0] - 'a'] += 'f';
            }
            //all scales of like modes and accidentals shift the progression array the same
            if (mode == "major") {              //ex: accidentalCt = 1
                temp.Shift(accidentalCt + 5);   //temp = f b e a d g c f
                adjuster = temp[0][0] - 'a';
            }
            else {
                temp.Shift(accidentalCt + 2);
                adjuster = temp[0][0] - 'a';
            }
            rval.Shift(tolower(temp[0][0]) - 'a');
        }
        keySignature = rval;
        MakeChordPitches();
    }
    else std::cout<<"ERR: keysig must start with a number\n";
}

void KeySignature_T::Initialize(std::string keySig, std::string mode){
    CAStr_T rval SCALE;     //return value, cyclic array initialized to {a,b,c,d,e,f,g}
    keyMode = mode;         //sets key signature mode
    int accidPos = 0;       /* (keySig is in the form  X(s/f) where X is a string integer)
                             * holds accidental spot in string
                             */
    //iterate through the keySig input and find the accidental index
    for (auto i : keySig){
        if (i != 's' && i != 'f') accidPos++;
    }

    //an accidPos < 1 indicates an error
    if ( accidPos > 0 ) {
        //retrieve accidental count
        int accidentalCt = std::stoi(keySig.substr(0, (unsigned long) accidPos));
        //if the accidental has a repeated letter, every letter - 1 is attached to every pitch
        accidentalCt = accidentalCt + (keySig.substr(accidPos, keySig.size() - accidPos).size()-1) * 7;

        //0 indicates C Major or a minor
        if (keySig.length() == 1) {
            if (mode == "major") {
                rval.Shift('c' - 'a');
                adjuster = 'c' - 'a';
            }
            else adjuster = 0;
        }
            //handle sharps
        else if (keySig[accidPos] == 's') {
            CAStr_T temp = SharProg_C;          // f c g d a e b
            for (int i = 0; i < accidentalCt; i++) {
                rval[temp[i][0] - 'a'] += 's';
            }
            if (mode == "major") {              //ex: accidentalCt = 1
                temp.Shift(accidentalCt + 1);   //temp = g d a e b f c
                adjuster = temp[0][0] - 'a';    //'g' - 'a' = 7
            }
            else {
                temp.Shift(accidentalCt + 4);   //temp = e b f c g d a
                adjuster = temp[0][0] - 'a';    //
            }
            rval.Shift(tolower(temp[0][0]) - 'a');
        }
        else if (keySig[accidPos] == 'f') {
            CAStr_T temp = FlatProg_C;          // b e a d g c f
            for (int i = 0; i < accidentalCt; i++) {
                rval[temp[i][0] - 'a'] += 'f';
            }
            //all scales of like modes and accidentals shift the progression array the same
            if (mode == "major") {              //ex: accidentalCt = 1
                temp.Shift(accidentalCt + 5);   //temp = f b e a d g c f
                adjuster = temp[0][0] - 'a';
            }
            else {
                temp.Shift(accidentalCt + 2);
                adjuster = temp[0][0] - 'a';
            }
            rval.Shift(tolower(temp[0][0]) - 'a');
        }
        keySignature = rval;
        MakeChordPitches();
    }
    else std::cout<<"ERR: keysig must start with a number\n";
}

void KeySignature_T::MakeChordPitches(){
    /*
     *                 I       II     III      IV      V       VI     VII
     * DIAT_CHORDS {{1,3,5},{2,4,6},{3,5,7},{4,6,1},{5,7,2},{6,1,3},{7,2,4}}
     * each integer corresponds to a pitch number in any particular scale
     * each roman numeral refers to the diatonic chord in the same scale
     */
    for (auto item : DiatonicChords_C) {        //item is vector<int>
        std::vector<std::string> diatonicChord; //holds pitches that make the diatonic chord

        for (auto subItem : item){              //subItem is an integer index + 1
            diatonicChord.push_back(keySignature[subItem - 1]);
        }
        chordPitches.push_back(diatonicChord);
    }

    /*
     * common chord progressions are all naturally created with the exception of the eighth chord of minors
     * minors naturally contain the VII diminished chord, but a VII major chord exists in the common chord
     * progression flow and must be added here
     */
    if (keyMode == "minor") {
        std::vector<std::string> VIIdToVII = chordPitches[chordPitches.size()-1];
        VIIdToVII[2-1] += 's'; //first to third now = 4 half tones
        VIIdToVII[3-1] += 's'; //first to fifth now = 7 half tones
        chordPitches.push_back(VIIdToVII);
    }
    /*
     * chords can be a : (Major, minor, augmented, diminished) chord
     * these play a role in the rules for acceptable chord progressions
     *  - calculate the chord names starting with the first pitch in the key signature
     *  - roman numerals refer to the pitch number in the scale (if in C Major: I = c & VII = b)
     *  - integers refer to diatonic chord number in same scale
     *                          I       II     III      IV      V       VI     VII
     *  D_CHORDS_SAME_PITCH {{1,4,6},{2,5,7},{1,3,6},{2,4,7},{1,3,5},{2,4,6},{3,5,7}}
     */

    //
    /*for (auto chord : DiatonicChords_C) {
        CalculateChordName(chord);
    }
    for (int i = 0; i < chordPitches.size(); i++) {
        for (int k = 1; k < DChordW_SamePitch_C[i].size(); k++){
            chordPitches[DChordW_SamePitch_C[i][k] - 1][SamePitchPos_C[k]-1] =
            chordPitches[i][0];
        }
    }*/
}


/*
 * modifies a pitch to its simplified equivalent ie. Bs = C : Aff = G : Dsf = D : Fs = Fs
 */
void KeySignature_T::Simplify(std::string &str) const{
    /*
     * the first accidental has priority (left to right)
     * reduce one accidental at a time
     */
    while (str.length() > 2 && str[2] != 'd' && str[2] != 'a') {
        if (str[1] == 's') {
            if (str[0] == 'b' || str[0] == 'e') {
                str[0] = Scale_C[str[0] - 'a' + 1][0];
                str.erase(1,1);
            }
            else if (str[2] == 's'){
                str[0] = Scale_C[str[0] - 'a' + 1][0];
                str.erase(1,2);
            }
            else if (str[2] == 'f') {
                str[0] = Scale_C[str[0] - 'a'][0];
                str.erase(1,2);
            }
        }
        else if (str[1] == 'f') {
            if (str[0] == 'c' || str[0] == 'f') {
                str[0] = Scale_C[str[0] - 'a' - 1][0];
                str.erase(1,1);
            }
            else if (str[2] == 'f'){
                str[0] = Scale_C[str[0] - 'a' - 1][0];
                str.erase(1,2);
            }
            else if (str[2] == 's') {
                str[0] = Scale_C[str[0] - 'a'][0];
                str.erase(1,2);
            }
        }
    }
    /*
     * because there is only a half tone between b-c and e-f, these can be simplified further
     */
    if (str.length() > 1) {
        if (str[1] == 's') {
            if (str[0] == 'b' || str[0] == 'e') {
                str[0] = Scale_C[str[0] - 'a' + 1][0];
                str.erase(1,1);
            }
        }
        else if (str[1] == 'f') {
            if (str[0] == 'c' || str[0] == 'f') {
                str[0] = Scale_C[str[0] - 1 - 'a'][0];
                str.erase(1,1);
            }
        }
    }
    if (str.size() == 1) { str += 'n';}
}

/*
 * guess the current chord based on current pitch. integers represent chord I - VII
 */
void KeySignature_T::DetermineCurrentChord(const std::string &pitch) {
    std::cout<<pitch<<std::endl;
    int pitchNum = AdjustedI(pitch[0] - keySignature[0][0]) + 1;
    switch (pitchNum){
        case 1 : currentChord = 1; break;
        case 2 : currentChord = 5; break;
        case 3 : currentChord = 1; break;
        case 4 : currentChord = 7; break;
        case 5 : currentChord = 1; break;
        case 6 : currentChord = 2; break;
        case 7 : currentChord = 5; break;
        default: currentChord = 1;
    }
    std::cout<<currentChord<<'\n';
}

std::vector<std::string> KeySignature_T::GetTonesInCurrentChord() const{
    std::vector<std::string> rvals;
    rvals = chordPitches[currentChord-1];
    for (int i = 0; i < rvals.size(); ++i){
        Simplify(rvals[i]);
    }
    return rvals;
}

/*
 * common chord progression theory, integers represent chords I - VII
 */
const std::vector<int> KeySignature_T::GetNextPossibleChords(){
    if (currentChord != -1) {
        if (keyMode == "major"){
            switch(currentChord){
                case 1 : return {1,2,3,4,5,6,7};
                case 2 : return {2,5,7};
                case 3 : return {3,6};
                case 4 : return {4,5,7};
                case 5 : return {1,5};
                case 6 : return {2,4,6};
                case 7 : return {1,3,7};
                default: return {1};
            }
        }
        else {
            switch (currentChord){
                case 1 : return {1,2,3,4,5,6,7};
                case 2 : return {5,7};
                case 3 : return {6};
                case 4 : return {5,7,8};
                case 5 : return {1};
                case 6 : return {2,3};
                case 7 : return {1};
                case 8 : return {3}; //this is a special case for all minors. they have VII diminished and VII maj in its chord progression
                                        //case 7 is VII diminished and
                default: return {1};
            }
        }
    }
    return {-1};
}

/*
 * returns a list of valid, non-repeating, simplified pitches
 */
const std::vector<std::string> KeySignature_T::GetNextPossibleNotes(){
    std::set<std::string> pitches;
    std::string adjustedPitch;
    int ct = 0, ct2 =0;
    for (auto chordNum : GetNextPossibleChords()){
        for (int pitch = 0; pitch < chordPitches[chordNum-1].size(); pitch++){
            adjustedPitch = chordPitches[chordNum-1][pitch];
            Simplify(adjustedPitch);
            pitches.insert(adjustedPitch);
        }
    }
    std::vector<std::string> rPitches;
    for (auto pitch : pitches) {
        rPitches.push_back(pitch);
    }
    return rPitches;
}


/*
 *          I   II  III IV  V   VI  VI
 *          A   B   C   D   E   F   G
 *      1 A *           *       *       I   IV  VI
 *      2 B     *           *       *   II  V   VII
 *      3 C *       *           *       I   III VI
 *      4 D     *       *           *   II  IV  VII
 *      5 E *       *       *           I   III V
 *      6 F     *       *       *       II  IV  VI
 *      7 G         *       *       *   III V   VII
 */

/*void KeySignature_T::CalculateChordName(const std::vector<int> &chord) {
    int halvesToThird = 0, halvesToFifth = 0;
    std::string first = keySignature[chord[0] - 1];
    std::string third = keySignature[chord[1] - 1];
    std::string fifth = keySignature[chord[2] - 1];
    halvesToThird = CalculateDistance(first, third);
    halvesToFifth = CalculateDistance(first, fifth);

     * Major 4:7
     * minor 3:7
     * augmented 4:8
     * diminished 3:6

    if      (halvesToThird == 4 && halvesToFifth == 7){
        chordPitches[chord[0] - 1][0][0] = (char)toupper(chordPitches[chord[0] - 1][0][0]);
    }
    else if (halvesToThird == 3 && halvesToFifth == 7){
        chordPitches[chord[0] - 1][0][0] = (char)tolower(chordPitches[chord[0] - 1][0][0]);
    }
    else if (halvesToThird == 3 && halvesToFifth == 6){
        chordPitches[chord[0] - 1][0][0] = (char)tolower(chordPitches[chord[0] - 1][0][0]);
        chordPitches[chord[0] - 1][0] += 'd';
    }
    else if (halvesToThird == 4 && halvesToFifth == 8) {
        chordPitches[chord[0] - 1][0][0] = (char) toupper(chordPitches[chord[0] - 1][0][0]);
        chordPitches[chord[0] - 1][0] += 'A';
    }
}*/

/*const int KeySignature_T::CalculateDistance(const std::string &begining, const std::string &ending) {
    int startIndex = AdjustedI(begining[0] - keySignature[0][0]);
    int endIndex   = AdjustedI(ending[0] - keySignature[0][0]);
    int distance = 0;
    int i = startIndex;
    while (i != endIndex && i < 8){
        distance += ScaleDistRef_C[i];
        i++;
        if (i % ScaleDistRef_C.Size() == 0) i = 0;
    }
    if (begining.length() > 1){
        if ( begining[1] == 's'){
            distance--;
            if (ending.length() > 1){
                if (ending[1] == 's') distance++;
                else distance--;
            }
        }
        else {
            distance++;
            if (ending.length() > 1){
                if (ending[1] == 's') distance++;
                else distance--;
            }
        }
    }
    else if (ending.length() > 1){
        if (ending[1] == 's') distance++;
        else distance--;
    }
    return distance;
}*/
