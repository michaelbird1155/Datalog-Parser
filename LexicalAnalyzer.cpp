

//
//  LexicalAnalyzer.cpp
//  Project1
//
//  Created by Michael Bird on 6/25/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include "LexicalAnalyzer.h"

//  initialize the constructor

LexAn::LexAn(string in, int linecount) : input(in), line(linecount), char_class(ERROR), next_char(' '), lexeme("")
{
	get_char();
}

//  deconstruct the constructor

LexAn::~LexAn()
{
}

// gets the new input char

void LexAn::new_input(string in)
{
	input=in;
	get_char();
    
}

// gets the input char from new_input() and assigns its a character class

void LexAn::get_char()
{
	if (input.size()>0) {
        next_char = input[0];
        input.erase(0,1);
	}
	else
        next_char = '\n';
    
	char_class = ERROR;
    
    switch (next_char) {
        case 65 ... 90:
            char_class = LETTER;
            break;
        case 96 ... 123:
            char_class = LETTER;
            break;
        case 48 ... 57:
            char_class = DIGIT;
            break;
        case ' ':
            char_class = SPACE;
            break;
        case '\n':
            char_class = STOP;
            break;
        case '+':
            char_class = PLUS_CODE;
            break;
        case '?':
            char_class = Q_MARK;
            break;
        case ',':
            char_class = COMMA;
            break;
        case '.':
            char_class = PERIOD;
            break;
        case '(':
            char_class = LEFT_PAREN;
            break;
        case ')':
            char_class = RIGHT_PAREN;
            break;
        case ':':
            char_class = COLON;
            break;
        case ';':
            char_class = SEMI_COLON;
            break;
        case '-':
            char_class = DASH;
            break;
        case '#':
            char_class = COMMENT;
            break;
        case 39:
            char_class = QUOTATION;
            break;
        case 92:
            char_class = BACK_SLASH;
            break;
        case '_':
            char_class = UNDERSCORE;
            break;
        case 9:
            char_class = SPACE;
            break;
        default:
            char_class = ERROR;
            break;
    }
}

//  adds the character to the lexeme string

void LexAn::add_char()
{
	lexeme+=next_char;
}

//
int LexAn::rule1() {
    
    while (char_class == LETTER || char_class == DIGIT) {
        add_char();
        get_char();
    }
    
    if (lexeme == "Queries") {
        token_type = "QUERIES";
        return QUERIES;
    }
    if (lexeme == "Schemes") {
        token_type = "SCHEMES";
        return SCHEMES;
    }
    if (lexeme == "Rules") {
        token_type = "RULES";
        return RULES;
    }
    if (lexeme == "Facts") {
        token_type = "FACTS";
        return FACTS;
    }
    else {
        token_type = "ID";
        return ID;
    }
}

int LexAn::rule2() {
    
    while (char_class != QUOTATION && char_class != STOP) {
        add_char();
        get_char();
    }
    add_char();
    get_char();
    lexeme.erase( 0, 1 ); // erase the first character
    if (lexeme.back() == 39) {
        lexeme.erase( lexeme.size() - 1 ); // erase the last character
        token_type = "STRING";
        return STRING;
    }
    else
        return ERROR;
} 

int LexAn::rule3() {
    
    while (char_class == LETTER || char_class == DASH) {
        add_char();
        get_char();
    }
    if (lexeme == "\n")
        return SPACE;
    else {
        token_type = "ID";
        return ID;
    }
}

int LexAn::lex()
{
    
    lexeme="";
    token_type="";
    
    while (char_class == SPACE)   //  moves to the next character if there is a space. Does not add to the lexeme
        get_char();
    
    if (char_class == ERROR) {    //  simply throws an error if the character isnt recognized
        add_char();
        get_char();
        token_type = "ERROR";
        return ERROR;
    }
    if (char_class == STOP) {      //  when line reaches the end, it produces a STOP token
        token_type = "STOP";
        return STOP;
    }
    switch (char_class) {         // switch statement for the other character classes.
        case LETTER:
            add_char();
            get_char();
            return rule1();
            break;
        case DIGIT:
            add_char();
            get_char();
            while (char_class == DIGIT) {
                add_char();
                get_char();
            }
            token_type = "INTEGER";
            return INTEGER;
            break;
        case PLUS_CODE:
            add_char();
            get_char();
            token_type = "ERROR";
            return PLUS_CODE;
            break;
        case COMMA:
            add_char();
            get_char();
            token_type = "COMMA";
            return COMMA;
            break;
        case PERIOD:
            add_char();
            get_char();
            token_type = "PERIOD";
            return PERIOD;
            break;
        case Q_MARK:
            add_char();
            get_char();
            token_type = "Q_MARK";
            return Q_MARK;
            
            break;
        case LEFT_PAREN:
            add_char();
            get_char();
            token_type = "LEFT_PAREN";
            return LEFT_PAREN;
            break;
        case RIGHT_PAREN:
            add_char();
            get_char();
            token_type = "RIGHT_PAREN";
            return RIGHT_PAREN;
            break;
        case COLON:
            add_char();
            get_char();
            while(char_class == DASH) {
                add_char();
                get_char();
            }
            if (lexeme == ":-") {
                token_type = "COLON_DASH";
                return COLON_DASH;
            }
            else {
                token_type = "COLON";
                return COLON;
            }
            break;
        case DASH:
            add_char();
            get_char();
            token_type = "DASH";
            return DASH;
            break;
        case COLON_DASH:
            add_char();
            get_char();
            token_type = "COLON_DASH";
            return COLON_DASH;
            break;
        case SEMI_COLON:
            add_char();
            get_char();
            token_type = "ERROR";
            return ERROR;
            break;
        case COMMENT:
            add_char();
            get_char();
            token_type = "STOP";
            return STOP;
            break;
        case QUOTATION:
            add_char();
            get_char();
            return rule2();
            //return STRING;
            break;
        case BACK_SLASH:
            add_char() ;
            get_char();
            return rule3();
            break;
        case UNDERSCORE:
            add_char() ;
            get_char();
            token_type = "ERROR";
            return ERROR;
            break;
        default:
            token_type = "ERROR";
            return ERROR;
    } 
    
}
string LexAn::get_token_value() {
    return lexeme;
}
string LexAn::get_token_type() {
    return token_type;
}
void LexAn::line_number(int linecount) {
    int line = linecount;
}
int LexAn::get_line_number() {
    return line;
}
