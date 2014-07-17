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

void Predicate::add_id(string _id) {
    id = _id;
}

void Predicate::add_param(string param) {
    Par.add_param(param);
}

string Predicate::toString() {
    stringstream ss;
    ss << id << "(";
    ss << Par.toString();
    for(auto param : parameter)
        ss << "fdsa";
    ss << ")";
    return ss.str();
}

void Predicate::clear() {
    id = "";
    Par.clear();
}