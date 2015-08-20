//
// Created by Matthew McKay on 8/14/15.
//

#ifndef VECTOR64VSBITSET468_BITWISEVECT64_H
#define VECTOR64VSBITSET468_BITWISEVECT64_H
#include <iostream>
#include <deque>
#include <exception>
#include <cstdlib>
using namespace std;


const u_int8_t modulous = 4;
const u_int8_t modBits = 7;
const u_int16_t ERASER = 8191;
template <class T, size_t N>
class BitWiseDeque64 : public deque<T>{
private:
    u_int8_t elementDepth;
public:
    using deque<T>::size;
    using deque<T>::empty;
    using deque<T>::deque;

    void Append(const u_int64_t &appendV){
        if (this->empty()){
            this->push_front(appendV);
            elementDepth = 1;
        }
        else{
            u_int8_t mod = elementDepth & modBits;
            if (mod == modulous || mod == 0){
                this->push_front(appendV);
                elementDepth++;
            }
            else {
                mod &= (modBits >> 1);
                this->front() += (appendV << (N * mod));
                elementDepth++;

            }
        }
    }
    void Truncate(){
        if (this->empty()) return;
        else {
            u_int8_t mod = ((elementDepth) & 3);
            u_int64_t eraser = ERASER;
            if (mod == 01) {
                this->pop_front();
                elementDepth--;
            }
            else if (mod == 0){
                eraser <<= 39;
                eraser &= this->front() & eraser;
                this->front() ^= eraser;
                elementDepth--;
            }
            else {
                eraser <<= (N * (mod-1));
                eraser &= this->front() & eraser;
                this->front() ^= eraser;
                elementDepth--;
            }

        }
    }

    bool Find_id(const u_int64_t &id){
        u_int64_t i = this->size();
        u_int64_t si = modulous;
        bool notFound = true;
        while (i && notFound) {
            --i;
            while (si && notFound) {
                --si;
                notFound = id ^ (((*this)[i] & (8191 << ((si+1) * 13))) >> (si * 13));
            }
            si = 4;
        }
        return not notFound;
    }

    friend bool operator> (const BitWiseDeque64<T,N> &lhs, const BitWiseDeque64<T,N> &rhs){
        if (lhs.size() != rhs.size()) return lhs.size() > rhs.size();
        else {
            u_int8_t i = 0;
            while (lhs[i] == rhs[i] && i < lhs.size()-1) ++i;
            return lhs[i] > rhs[i];
        }
    }

    friend bool operator< (const BitWiseDeque64<T,N> &lhs, const BitWiseDeque64<T,N> &rhs){
        if (lhs.size() != rhs.size()) return lhs.size() < rhs.size();
        else {
            u_int8_t i = 0;
            while (lhs[i] == rhs[i] && i < lhs.size()-1) ++i;
            return lhs[i] < rhs[i];
        }
    }

    friend bool operator== (const BitWiseDeque64<T,N> &lhs, const BitWiseDeque64<T,N> &rhs){
        return lhs == rhs;
    }
};


#endif //VECTOR64VSBITSET468_BITWISEVECT64_H
