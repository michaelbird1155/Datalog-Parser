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

using namespace std;

class Predicate {
    
   
    
public:
    
    Predicate();
    ~Predicate();
    
    string id;
    string toString();
    string add_id(string id);
    string add_param(string param);
    void clear();
    
private:
    
    string pred_value;
    vector<string> parameter;
   // vector<string> domain;
    
    
    
};






#endif /* defined(__Project2__Predicate__) */
