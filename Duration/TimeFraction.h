//
// Created by Matthew McKay on 7/9/15.
//
#ifndef MUSICSYNTHESIS_V2_TIMEFRACTION_H
#define MUSICSYNTHESIS_V2_TIMEFRACTION_H

#include <iostream>
#include <cmath>

//#include "../Constants.h"

/**
 * rests use integers in two ways to represent time. for rests within a measure they indicate the denominator (the
 * same way notes use them). mRests, multiRests, and mSpaces use them to indicate whole measures (the numerator)
 * initialize all durations to zero time
 * overload the operator==, operator <, operator >
 */

struct TimeFraction_T {
public:
    int numerator;
    int denominator;

    //intializes all new durations to 0;
    TimeFraction_T() : numerator(0), denominator(1) {}
    TimeFraction_T(int n, int d) : numerator(n), denominator(d) {}

    void Simplify() {
        int gcf;
        gcf = Max(abs(numerator), denominator);
        while (gcf > 1){
            if ( (abs(numerator) % gcf == 0) && (denominator % gcf == 0) ) break;
            gcf--;
        }
        if (gcf > 1) {
            numerator /= gcf;
            denominator /= gcf;
        }
    }

    friend TimeFraction_T operator- (const TimeFraction_T &lhs, const TimeFraction_T& rhs){
        TimeFraction_T lt = lhs, rt = rhs;
        lt.numerator *= rt.denominator;
        rt.numerator *= lt.denominator;
        lt.denominator *= rt.denominator;
        lt.numerator -= rt.numerator;
        lt.Simplify();
        return lt;
    }
    friend TimeFraction_T operator* (const TimeFraction_T &lhs, const int &rhs){
        TimeFraction_T tf = lhs;
        tf.numerator *= rhs;
        return tf;
    }
    friend TimeFraction_T operator* (const int &lhs, const TimeFraction_T &rhs){
        TimeFraction_T tf = rhs;
        tf.numerator *= lhs;
        return tf;
    }
    TimeFraction_T& operator*= (const int &rhs){
        numerator *= rhs;
        return *this;
    }
    TimeFraction_T& operator-= (const TimeFraction_T &rhs){
        TimeFraction_T rt = rhs;
        numerator *= rt.denominator;
        rt.numerator *=denominator;
        denominator *= rt.denominator;
        numerator -= rt.numerator;
        Simplify();
        return *this;
    }

    //***************************************************************************** comparison operators
    friend bool operator== (const TimeFraction_T& lhs, const TimeFraction_T& rhs) {
        return (double)lhs.numerator/(double)lhs.denominator ==
               (double)rhs.numerator/(double)rhs.denominator;
    }
    friend bool operator!= (const TimeFraction_T& lhs, const TimeFraction_T& rhs) {
        return (double)lhs.numerator/(double)lhs.denominator !=
               (double)rhs.numerator/(double)rhs.denominator;
    }
    friend bool operator> (const TimeFraction_T& lhs, const TimeFraction_T& rhs) {
        return (double)lhs.numerator/(double)lhs.denominator >
               (double)rhs.numerator/(double)rhs.denominator;
    }
    friend bool operator< (const TimeFraction_T& lhs, const TimeFraction_T& rhs) {
        return (double)lhs.numerator/(double)lhs.denominator <
               (double)rhs.numerator/(double)rhs.denominator;
    }

    //****************************************************************************** stream operator
    friend std::ostream& operator<< (std::ostream& ostr, const TimeFraction_T& duration) {
        ostr << duration.numerator << "/" << duration.denominator;
        return ostr;
    }

    std::string ToString() const {
        std::string str = "";
        str += std::to_string(numerator);
        str += '/';
        str += std::to_string(denominator);
        return str;
    }
private:

    int Max(const int &n, const int &d) const {
        if (n > d) return n;
        return d;
    }

};
#endif //MUSICSYNTHESIS_V2_TIMEFRACTION_H
