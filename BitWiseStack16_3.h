//
// Created by Matthew McKay on 8/18/15.
//

#ifndef VECTOR64VSBITSET468_BITWISESTACK16_3_H
#define VECTOR64VSBITSET468_BITWISESTACK16_3_H
#include <iostream>
#include <stack>
#include <initializer_list>
using namespace std;
class BitWiseStack16_3 : public stack<u_int16_t> {
private:
    stack<u_int16_t> bitStack;
    u_int8_t depth;
public:
    using stack::stack;
    using stack::size;
    using stack::empty;

    void Push(const u_int8_t &num){
        if (this->empty()){
            this->push(num);
            depth = 1;
        }
        else {
            u_int8_t mod = depth & (u_int8_t)7;
            if (mod == 4 || mod == 0){
                this->push(num);
                depth++;
            }
            else {
                this->top() <<= 3;
                this->top() |= num;
                depth++;
            }
        }
    }

    u_int8_t Top() const{
        return this->top() & 7;
    }

    void Pop() {
        if (this->empty()) return;
        else {
            u_int8_t mod = depth & (u_int8_t)7;
            if (mod == 4 || mod == 0){
                this->pop();
                depth--;
            }
            else {
                this->top() >>= 3;
                depth--;
            }
        }

    }
};
#endif //VECTOR64VSBITSET468_BITWISESTACK16_3_H
