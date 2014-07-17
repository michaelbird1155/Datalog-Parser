//
//  Predicate.h
//  Project2
//
//  Created by Michael Bird on 7/3/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//



#ifndef __Project2__Predicate__
#define __Project2__Predicate__

#include <iostream>
#include <vector>
#include "Parameter.h"

using namespace std;

class Predicate {
    
   
    
public:
    
    Predicate();
    ~Predicate();
    
    string id;
    string toString();
    void add_id(string id);
    void add_param(string param);
    void clear();
    Parameter Par;
    
private:
    
    string pred_value;
    vector<Parameter> parameter;
    
};






#endif /* defined(__Project2__Predicate__) */
