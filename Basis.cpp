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
            tones.insert(tone);
            octaves.insert((*it)->GetOctave());
            dur.timeFraction = (*it)->GetDurationFraction();
            dur.dots = (*it)->GetDots();
            nDurations.insert(dur);
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
        dur.dots = (SPC_(Note_T)(elem))->GetDots();
        nDurations.insert(dur);
    }
    else {
        rDurations.insert(elem->GetDurationFraction());
    }
}

void Basis_T::MakeBasis() {
    for (auto tone_it = tones.begin(); tone_it != tones.end(); ++tone_it){
        for (auto oct_it = octaves.begin(); oct_it != octaves.end(); ++oct_it){
            for (auto dur_it = nDurations.begin(); dur_it != nDurations.end(); ++dur_it){
                SHP_T(Note_T) note (new Note_T);
                global_shpCt++;
                note->SetPitch(tone_it->pitch);
                note->SetAccidental(tone_it->accid);
                note->SetOctave(*oct_it);
                note->SetDuration(dur_it->timeFraction);
                note->SetDots(dur_it->dots);
                completeBasis.push_back(note);
            }
        }
    }
    for (auto rest_it = rDurations.begin(); rest_it != rDurations.end(); ++rest_it){
        SHP_T(Rest_T) rest (new Rest_T);
        global_shpCt++;
        rest->SetDuration(*rest_it);
        completeBasis.push_back(rest);
    }
}