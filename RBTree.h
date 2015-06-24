//
// Created by Matthew McKay on 6/23/15.
//

#ifndef MUSICSYNTHESIS_V2_RBTREE_H
#define MUSICSYNTHESIS_V2_RBTREE_H
#include <iostream>
#include "Note.h"
#include "Rest.h"
#include <boost/intrusive/rbtree.hpp>
template <class T>
class X : public boost::intrusive::set_base_hook<boost::intrusive::optimize_size<true> >
{
    T t_;
public:
    boost::intrusive::set_member_hook<> member_hook_;
    X(T i) : t_(i)
    {}
    friend bool operator< (const X &a, const X &b)
    {  return a.t_ < b.t_;  }
    friend bool operator> (const X &a, const X &b)
    {  return a.t_ > b.t_;  }
    friend bool operator== (const X &a, const X &b)
    {  return a.t_ == b.t_;  }
    friend std::ostream& operator<< (std::ostream& ostr, X &a)
    {  ostr << a.t_;
        return ostr;}
    T t()const{return t_;}
};
#endif //MUSICSYNTHESIS_V2_RBTREE_H
