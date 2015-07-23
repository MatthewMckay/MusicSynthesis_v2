//
// Created by Matthew McKay on 7/20/15.
//

#ifndef MUSICSYNTHESIS_V2_CYCLICARRAY_H
#define MUSICSYNTHESIS_V2_CYCLICARRAY_H
#include <iostream>
#include <array>
#include <vector>
#include <initializer_list>

template <class T>
class CyclicArray_T {
private:
    CyclicArray_T(){}
public:
    std::vector<T> data;

    CyclicArray_T(std::vector<T> d) : data(d) {}
    CyclicArray_T(std::initializer_list<T> init) : data(init) {}

    std::pair<T,int> operator[] (int i) const {
        int lap = 0;
        if ( (i / (data.size()) > 0) ) lap = i / (int)(data.size());
        std::pair<T, int> p = {data[i % data.size()], lap};
        return p;
    }
};

template <class T, class A>
std::ostream& operator<< (std::ostream& ostr, const std::pair<T,A>& p){
    ostr << p.first;
    return ostr;
}
#endif //MUSICSYNTHESIS_V2_CYCLICARRAY_H
