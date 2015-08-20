//
// Created by Matthew McKay on 8/18/15.
//

#ifndef VECTOR64VSBITSET468_BITWISE32INT_3_H
#define VECTOR64VSBITSET468_BITWISE32INT_3_H

#include <iostream>
#include <list>
//#include <bitset>
using namespace std;

class U_Int32_Stack {
public:
    unsigned int intStack;

    U_Int32_Stack(const list<unsigned int> &myList) : intStack(0) {
        for (list<unsigned int>::const_iterator i = myList.begin(); i != myList.end(); ++i){
            //cout<<*i<<"\t";
            this->Push(*i);
        }
    }

    void Push(const u_int8_t &num){
        if (intStack == 0) intStack |= num;
        else {
            intStack <<= 3;
            intStack |= num;
        }
        //bitset<32> x (intStack);
        //cout<<x<<endl;
    }

    u_int8_t Top() const {
        return intStack & 7;
    }

    void Pop() {
        intStack >>= 3;
    }
};
#endif //VECTOR64VSBITSET468_BITWISE32INT_3_H
