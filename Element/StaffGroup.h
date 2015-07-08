//
// Created by Matthew McKay on 7/7/15.
//

#ifndef MUSICSYNTHESIS_V2_STAFFGROUP_H
#define MUSICSYNTHESIS_V2_STAFFGROUP_H

#include <vector>
#include <unordered_map>
#include <exception>
#include <iostream>

#include "Staff.h"
#include "../Constants.h"

class StaffGroup_T {
    friend class Processing_T;
    typedef std::unordered_map<std::string, Staff_T> strStfMap_T;
    std::unordered_map<std::string, Staff_T>::iterator strStfMapIt_T;
private:
    int * level;
    std::vector<StaffGroup_T> staffGroup;
    strStfMap_T staffs;
public:
    void FindStaff();
    friend std::ostream& operator<< (std::ostream& ostr, const StaffGroup_T& staffGrp);
};


#endif //MUSICSYNTHESIS_V2_STAFFGROUP_H
