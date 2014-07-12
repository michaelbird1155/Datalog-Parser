
//
//  LexicalAnalyzer.h
//  Project1
//
//  Created by Michael Bird on 6/25/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.

#ifndef __Project2__LexicalAnalyzer__
#define __Project2__LexicalAnalyzer__

#include <iostream>
#include <string>


using namespace std;

//  list of enum types

enum {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, SEMI_COLON, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, DASH, QUOTATION, COMMENT, BACK_SLASH, DIGIT, UNDERSCORE, TAB, LETTER, INTEGER, ERROR, SPACE, STOP, PLUS_CODE, EPSILON};

//  the class and its public and private methods and values

class LexAn  
{

public:
	char next_char;
	int char_class;
    int line;
    string token_type;
	string lexeme;
    string tokenizer(int token);
    string get_token_value();
    string get_token_type();
    void line_number(int linecount);
    int get_line_number();
    int lex();
    int rule1();
    int rule2();
    int rule3();
	void new_input(string in);
	LexAn(string in="", int linecount = 0);
	virtual ~LexAn();

private:
	string input;
    
    void add_char();
	void get_char();


};
#endif /* defined(__Project2__LexicalAnalyzer__) */