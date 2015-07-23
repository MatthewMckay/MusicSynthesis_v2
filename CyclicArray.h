//
// Created by Matthew McKay on 7/19/15.
//

#ifndef CYCLICARRAY_CYCLICARRAY_H
#define CYCLICARRAY_CYCLICARRAY_H
#include <iostream>
#include <array>
#include <vector>
#include <initializer_list>


/*
 * this class makes a circular vector
 */
template <class T>
class CyclicArray_T {
public:
    std::vector<T> data; //holds the data

    CyclicArray_T(){}
    CyclicArray_T(std::vector<T> d) : data(d) {} //can be initialized with a vector
    CyclicArray_T(std::initializer_list<T> init) : data(init) {} //can be initialized with a list

    //these set data after the cyclicArray has been instantiated
    void Data(const std::vector<T> &d) { data = d; }
    void Data(const std::initializer_list<T> &init) { data = init; }
    //                                                           actual index: 0 1 2 3 4 5  6
    //overloaded access operators i.e CyclicArray A{a,b,c,d,e} A[0] = a A[6] = a b c d e a (b)
    //                                                         modified index: 0 1 2 3 4 0  1
    // the modified index fits in data
    T& operator[] (int i) { return data[i % data.size()]; }

    const T& operator[] (int i) const{ return data[i % data.size()]; }

    // changes the beginning index
    void Shift(const int &amt) {
        CyclicArray_T<T> temp;
        for (int i = 0; i < data.size(); i++){
            temp.data.push_back((*this)[i+amt]);
        }
        *this = temp;
    }

    const int Size() const {return (int)data.size();}

    friend std::ostream& operator<< (std::ostream &ostr, const CyclicArray_T<T> &cA){
        for (int i = 0; i < cA.Size() - 1; i++) ostr << cA[i] << '\t';
        ostr << cA[cA.Size()-1];
        return ostr;
    }
};

#endif //CYCLICARRAY_CYCLICARRAY_H
