//
//  Parameter.cpp
//  Project2
//
//  Created by Michael Bird on 7/3/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include "Parameter.h"
#include <sstream>

Parameter::Parameter() {}
Parameter::~Parameter() {}

string Parameter::add_domain(string domain) {
    domains.push_back(domain);
    return domain;
}

string Parameter::toString() {
    stringstream ss;
    ss << "Domain(";
    ss << domains.size() << "):" << endl;
    for(auto domain : domains)
        ss << "   '" << domain << "'"<<endl;
    
    //cout << ss.str();
    return ss.str();
}