//
// Created by Matthew McKay on 6/22/15.
//

#ifndef MUSICSYNTHESIS_V2_TYPE_H
#define MUSICSYNTHESIS_V2_TYPE_H

#include <string>
#include <typeinfo>

std::string demangle(const char* name);

template <class T>
std::string type(const T& t) { return demangle(typeid(t).name()); }

#endif //MUSICSYNTHESIS_V2_TYPE_H
