//
// Created by Matthew McKay on 7/7/15.
//

#include "StaffGroup.h"

Staff_T * StaffGroup_T::FindStaff(std::string n) {
    strStfMapIt_T it = staffs.find(n);
    try {
        if (it != staffs.end()) return it->(&second);
        else if (!staffGroup.empty()) {
            for (auto it = staffGroup.begin(); it != staffGroup.end(); ++it) {
                return *it->FindStaff(n);
            }
        }
        throw 10;
    }
    catch (int e){
        std::cerr << ERR_CLRS << "ERR: invalid staff name" << DFLT_CLRS << '\n';
    }
}

std::ostream& StaffGroup_T::operator<< (std::ostream& ostr, const StaffGroup_T& staffGrp){
    ostr << "StaffGrp:\n";
    if (!staffs.empty) {
        for (strStfMapIt_T it = staffs.begin(); it != staffs.end(); ++it) {
            ostr << it->second;
        }
    }
    if (!staffGrp.empty){
        for (auto it = staffGrp.begin(); it != staffGrp.end(); ++it){
            ostr << *it;
        }
    }
}