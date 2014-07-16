//
//  parser.cpp
//  Project2
//
//  Created by Michael Bird on 7/10/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include "parser.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>



parser::parser(vector<LexAn> &tokenlist): tokenlist(tokenlist) {
 
}

parser::~parser() { }

void parser::parse() {
    
    //get_token();
    
    //current_token_value = tokenlist[index].get_token_value();
    //current_token_type = tokenlist[index].get_token_type();
    
    
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
    D.toString();

}

void parser::get_token_type() {
    current_token_type = tokenlist[index].get_token_type();
}
string parser::get_token_value() {
    current_token_value = tokenlist[index-1].get_token_value();
    return current_token_value;
    index++;index++;
}
void parser::update_token() {
    index++;
    current_token_type = tokenlist[index].get_token_type();
}

void parser::match( string match_token) {
    get_token_type();
    get_token_value();
    index++;
    if(match_token == current_token_type) {
      // cout << current_token_value;
        get_token_type();
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

void parser::predicatelist() {
    predicate();
    R.add_rule(P);
    if (current_token_type == "COMMA") {
        match("COMMA");
        predicatelist();
    }
}
void parser::predicate() {
    match("ID");
    P.clear();
        P.add_id(get_token_value());
    match("LEFT_PAREN");
    parameterlist();
    match("RIGHT_PAREN");
    
    //add predicate to datalog program
}
void parser::parameterlist() {
    parameter();
    if(current_token_type == "COMMA"){
        match("COMMA");
        P.add_param(get_token_value());
        parameterlist();
    }
    /*
    if(current_token_type == "STRING"){
        match("STRING");
        parameterlist();
    }*/
}
void parser::parameter() {
    if (current_token_type == "ID") {
        match("ID");
        P.add_param(get_token_value());
    }
    else if (current_token_type == "STRING") {
        match("STRING");
        P.add_param("'");
        P.add_param(get_token_value());
        P.add_param("'");
        Par.add_domain(get_token_value());
    }
    else
        match("ERROR");
   
}
void parser::schemelist() {
    scheme();
    D.add_to_schemes(P);
    get_token_type();
    if(current_token_type == "ID")
        schemelist();
}
void parser::scheme() {
    predicate();
}
void parser::factlist() {
    fact();
    if(current_token_type == "ID")
        factlist();
}
void parser::fact() {
    predicate();
    match("PERIOD");
    D.add_to_facts(P);
    D.add_to_domains(Par);
    if (current_token_type == "ID") {
        predicate();
        match("PERIOD");
        D.add_to_facts(P);
        D.add_to_domains(Par);
    }
}
void parser::rulelist() {
    rule();
    match("PERIOD");
    D.add_to_rules(R);
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
    else {}
}
void parser::rule() {
    
    R.clear();
    predicate();
    R.add_head(P);
    match("COLON_DASH");
    predicatelist();
}
void parser::querylist() {
    query();
    D.add_to_queries(P);
    if(current_token_type == "ID")
        querylist();
}
void parser::query() {
    predicate();
    match("Q_MARK");
    D.add_to_queries(P);
    if (current_token_type == "ID") {
        predicate();
        match("Q_MARK");
        D.add_to_queries(P);
    }
}