/*******************************************************************************
* File name: SytacticalAnalyzer.h                                              *
* Project: CS 460 Project 2 Fall 2019                                          *
* Author(s): Cole Nicholson-Rubidoux                                           *
* Date: November 27, 2019                                                      *
* Description: This file contains                                              *
*******************************************************************************/

#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"

using namespace std;

class SyntacticalAnalyzer 
{
    public:
	SyntacticalAnalyzer (char * filename);
	~SyntacticalAnalyzer ();
    private:
	LexicalAnalyzer * lex;
	token_type t;
	ofstream p2out;
	bool nonclosure = false; // Added bool to account for some cases within action() where function call exits without processing token
	int program ();
	int more_defines ();
	int define ();
	int stmt_list ();
	int stmt ();
	int literal ();
	int quoted_lit ();
	int more_tokens ();
	int param_list ();
	int else_part ();
	int stmt_pair ();
	int stmt_pair_body ();
	int action ();
	int any_other_token ();
};
	
#endif
