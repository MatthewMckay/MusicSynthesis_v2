//
// Created by Matthew McKay on 6/22/15.
//

#include "Basis.h"
void Basis_T::InputElem(SHP_T(Duration_T) elem) {

    if (elem->GetType() == "chord"){
        std::vector<SHP_T(Note_T)> notes = (SPC_(Chord_T)(elem))->GetNotes();
        for (auto it = notes.begin(); it != notes.end(); ++it){
            Tone_T tone;
            Dur_T dur;
            tone.pitch = toupper((*it)->GetPitch());
            tone.accid = (*it)->GetAccidental();
            octaves.insert((*it)->GetOctave());
            dur.timeFraction = (*it)->GetDurationFraction();
            dur.dur = (*it)->GetDots();
        }
    }
    else if (elem->GetType() == "note") {
        Tone_T tone;
        Dur_T dur;
        tone.pitch = toupper((SPC_(Note_T)(elem))->GetPitch());
        tone.accid = (SPC_(Note_T)(elem))->GetAccidental();
        tones.insert(tone);
        octaves.insert((SPC_(Note_T)(elem))->GetOctave());
        dur.timeFraction = (SPC_(Note_T)(elem))->GetDurationFraction();
        dur.dur = (SPC_(Note_T)(elem))->GetDots();
        nDurations.insert(dur);
    }
    else {
        rDurations.insert(elem->GetDurationFraction());
    }
}d

void Basis_T::MakeBasis() {
    for (auto tone_it = tones.begin(); tone_it != tones.end(); ++tone_it){
        for (auto oct_it = octaves.begin(); oct_it != octaves.end(); ++oct_it){
            for (auto dur_it = nDurations.begin(); dur_it != nDurations.begin(); ++dur_it){
                SHP_T(Note_T) note (new Note_T);
                note->
            }
        }
    }
}