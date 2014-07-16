//
//  parser.h
//  Project2
//
//  Created by Michael Bird on 7/10/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#ifndef __Project2__parser__
#define __Project2__parser__

#include <iostream>
#include <string>
#include <vector>
#include "LexicalAnalyzer.h"
#include "Predicate.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Parameter.h"

using namespace std;

/*
 <Datalog Program>  ->  Schemes : <Scheme List>
 Facts   : <Fact List>
 Rules   : <Rule List>
 Queries : <Query List>
 EOF
 
 <Scheme List>     ->  <Scheme> <Scheme List>
 <Scheme List>     ->  <Scheme>
 <Scheme>          ->  <Predicate>
 
 <Fact List>       ->  <Fact> <Fact List>
 <Fact List>       ->  e
 <Fact>            ->  <Predicate> .
 
 <Rule List>       ->  <Rule> <Rule List>
 <Rule List>       ->  e
 <Rule>            ->  <Predicate> :- <Predicate List> .
 
 <Query List>      ->  <Query> <Query List>
 <Query List>      ->  <Query>
 <Query>           ->  <Predicate> ?
 
 <Predicate List>  ->  <Predicate> , <Predicate List>
 <Predicate List>  ->  <Predicate>
 <Predicate>       ->  Identifier ( <Parameter List> )
 
 <Parameter List>  ->  <Parameter> , <Parameter List>
 <Parameter List>  ->  <Parameter>
 <Parameter>       ->  String | Identifier
 */

//vector<predicate> schemes;

class parser {
    
public:

	parser(vector<LexAn> &tokenlist);
	~parser();
    void parse();
    void get_token_type();
    string get_token_value();
    void update_token();
    string current_token_type;
    string current_token_value;
    int index=0;
    Predicate P;
    DataLog D;
    Rule R;
    Parameter Par;

    
private:

    void error();
    void match(string token_type);
    void schemelist();
    void scheme();
    void factlist();
    void fact();
    void rulelist();
    void rule();
    void querylist();
    void query();
    void predicatelist();
    void predicate();
    void parameterlist();
    void parameter();

    vector<LexAn> &tokenlist;
};

#endif /* defined(__Project2__parser__) */
