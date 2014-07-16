//
//  Predicate.cpp
//  Project2
//
//  Created by Michael Bird on 7/3/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//
#include <sstream>

#include "Predicate.h"

Predicate::Predicate() {}

Predicate::~Predicate() {}

string Predicate::add_id(string _id) {
    id = _id;
   // cout << _id << endl;
    return _id;
}

string Predicate::add_param(string param) {
    parameter.push_back(param);
    return param;
}
string Predicate::toString() {
    stringstream ss;
    ss << id << "(";
    for(auto param : parameter)
        ss << param;
    ss << ")";
    return ss.str();
}
void Predicate::clear() {
    
    id = "";
    parameter.clear();
    
}