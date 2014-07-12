//
//  parser.cpp
//  Project2
//
//  Created by Michael Bird on 7/10/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include "parser.h"
#include <string>
#include <sstream>
#include <iostream>

vector<predicate> schemes;
vector<predicate> facts;
vector<predicate> queries;
vector <rule> rules;

parser::parser(vector<LexAn> &tokenlist): tokenlist(tokenlist){}

parser ::~parser() { }



void parser::parse() {
    
    //get_token();
    int index = 0;

    current_token_type = tokenlist[index++].get_token_type();
    
    match("SCHEMES");
    match("COLON");
    schemelist();
    match("FACTS");
    match("COLON");
    factlist();
    match("RULES");
    match("COLON");
    rulelist();
    match("QUERIES");
    match("COLON");
    querylist();
   
}

void parser::get_token_type() {
    current_token_type = tokenlist[index].get_token_type();
}

void parser::match( string match_token) {
    get_token_type();
    index++;
    if(match_token == current_token_type) {
        // celecrate!!!
    }
    else
        error();
}


void parser::error() {
    stringstream ss;
    ss << "(" << tokenlist[index-1].get_token_type() << ",\"" << tokenlist[index-1].get_token_value() << "\"," << tokenlist[index-1].get_line_number() << ")";
    string error = ss.str();
    throw error;
}
void parser::schemelist() {
    scheme();
    get_token_type();
    if(current_token_type == "ID")
        schemelist();
}
void parser::scheme() {
    predicate();
}
void parser::predicate() {
    match("ID");
    match("LEFT_PAREN");
    parameterlist();
    match("RIGHT_PAREN");
        if(current_token_type == "COMMA") {
        match("COMMA");
        predicate();
    }
    else if (current_token_type == "PERIOD")
        match("PERIOD");
}
void parser::parameterlist() {
    parameter();
    get_token_type();
    if(current_token_type == "COMMA"){
        match("COMMA");
        parameterlist();
    }
}
void parser::parameter() {
    get_token_type();
    if (current_token_type == "ID") {
        match("ID");
    }
    else if (current_token_type == "STRING")
        match("STRING");
}
void parser::factlist() {
    fact();
    get_token_type();
    if(current_token_type == "ID")
        factlist();
    else if(current_token_type == "PERIOD")
        match("PERIOD");
    get_token_type();
        if(current_token_type == "ID")
            factlist();
}
void parser::fact() {
    predicate();
}
void parser::rulelist() {
    rule();
    get_token_type();
    if(current_token_type == "ID")
        rulelist();
    else if(current_token_type == "COLON_DASH") {
        match("COLON_DASH");
        rulelist();
    }
    else if(current_token_type == "COMMA") {
        match("COMMA");
        rulelist();
    }
    else if(current_token_type == "PERIOD")
        match("PERIOD");
    get_token_type();
    if(current_token_type == "ID")
        rulelist();
}
void parser::rule() {
    predicate();
}
void parser::querylist() {
    query();
    get_token_type();
    if(current_token_type == "ID")
        querylist();
    else if(current_token_type == "Q_MARK")
        match("Q_MARK");
    get_token_type();
    if(current_token_type == "ID")
        querylist();
}
void parser::query() {
    predicate();
}
/*

void parser::predicatelist() {
    
}


*/