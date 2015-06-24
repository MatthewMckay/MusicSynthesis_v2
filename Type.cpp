//
// Created by Matthew McKay on 6/22/15.
//

#include "Type.h"
#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

std::string demangle(const char* name) {

    int status = -4; // some arbitrary value to eliminate the compiler warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, decltype(std::free)*> res {
            abi::__cxa_demangle(name, NULL, NULL, &status),
            std::free
    };
    return (status==0) ? res.get() : name;
}

#else

// does nothing if not g++
std::string demangle(const char* name) {return name;}

#endif