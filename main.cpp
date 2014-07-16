//
//  main.cpp
//  Project1
//
//  Created by Michael Bird on 6/25/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "LexicalAnalyzer.h"
#include "parser.h"

using namespace std;

int main (int argc, char *argv[])
{
    ifstream inputFile("/Users/birdman/Documents/Project2/Project2/input.txt");
    ofstream outputFile("/Users/birdman/Documents/Project2/Project2/output.txt");
    //ifstream inputFile(argv[1]);
    //ofstream outputFile(argv[2]);
    string line;

        int token=SPACE;
        int linecount = 0;
        int tokencount = 0;
        vector<LexAn> tokenlist;
    
        //  Use getline to handle the input line by line which will make it easy to get the line numbers
    
        while(getline(inputFile, line)) {
            
            linecount++;
        
            LexAn LA(line, linecount);
            
            //  keeps reading in characters until the endline STOP token appears
            
            while (token != STOP) {
                
                tokencount++;
                token = LA.lex();
                
                if (token == STOP)
                    break; //do not show any end of line (STOP) tokens
                else if(token == PLUS_CODE) {
                    outputFile << "Input Error on line " << linecount << endl;
                    return 0;
                }
                else if (LA.get_token_type() == "ERROR") {
                    outputFile << "Input Error on line " << linecount << endl;
                    return 0;
                }
                else {
                    outputFile << "(" << LA.get_token_type() << ",\"" << LA.get_token_value() << "\"," << LA.get_line_number() << ")" << endl;
                    
                    // add object to token vector
                    
                    //LA.get_token_type();
                    //LA.get_token_value();
                    //LA.get_line_number();
                    
                    tokenlist.push_back(LA);
                }
            }
            token = 0; //resets the token so that the getline while loop moves to the next line.
        }
        outputFile << "Total Tokens = " << tokencount - linecount << endl;
    
    parser PA(tokenlist);
   
    try {
        PA.parse();
    }
    catch (string e){
        cout << "Failure!"<<endl;
        cout << "   " << e << endl;
    }
}



