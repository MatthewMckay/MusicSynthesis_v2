//
// Created by Matthew McKay on 7/1/15.
//

#include "Chord.h"

/**
 * used when the chord has a duration attribute
 */
void Chord_T::SetDuration( int d ) {
    if ( d == 1 ) duration.numerator = d;
    else {
        duration.numerator = 1;
        duration.denominator = d;
    }
}

/**
 * used when the chord copies the duration from its notes
 */
void Chord_T::SetDuration(TimeFraction_T dur) {
    duration = dur;
}

/**
 * dots (number of dots n) modify the original duration (dur) with the following equation
 * dur * (2 - (1 / (2^n))) == dur * ((2^(n+1)-1)/(2^n))
 * TODO add check to avoid double modifications
 */
void Chord_T::DotModify(int dots ) {
    if ( dots == 0 ) return;
    else{
        duration.numerator = ( duration.numerator << ( dots + 1 ) ) - 1;
        duration.denominator = duration.denominator << dots;
    }
}

/**
 * reverses DotModiy()
 * dur = ((dur + 1) / 2^-(n+1)) / 2^-n
 * TODO add check to avoid double modifications
 */
TimeFraction_T Chord_T::ReverseDotModify() const{
    TimeFraction_T tf;
    if (dots == 0 || duration == tf) return duration;
    else {
        tf = duration;
        tf.numerator = ( tf.numerator + 1 ) >> ( dots + 1 );
        tf.denominator = tf.denominator >> dots;
        return tf;
    }
}
