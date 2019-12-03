/*******************************************************************************
* File name: SyntaticalAnalyzer.cpp                                            *
* Project: CS 460 Project 2 Fall 2019                                          *
* Author(s): Cole Nicholson-Rubidoux                                           *
* Date: November 27, 2019                                                      *
* Description: This file contains                                              *
*******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
  string name = filename;
  lex = new LexicalAnalyzer (filename);
  string p2outname = filename;
  p2outname += ".p2";
  p2out.open(p2outname);
  int totalErrors = program ();
  token_type t;
  int errors = program();
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
  p2out.close();
  delete lex;
}

int SyntacticalAnalyzer::program ()
{
  int errors = 0;
  p2out << "Using Rule 1\n";
  t = lex->GetToken();
  string token = lex->GetToken(t)
  lexeme = lex->GetLexeme();
  p2file << "Entering Program function; current token is: " << tok << ", lexeme: " << lexeme << endl;

  if(t == LPAREN_T)
    {
      t = lex->GetToken();
      errors += define();
      t = lex->GetToken();
      if(t == LPAREN_T)
	{
	  p2file << "Using Rule 1\n";
	  t = lex->GetToken();
	  errors += more_defines();
	  t = lex->GetToken();
	  if(t == EOF_T)
	    {
	      return errors;
	    }
	  else{
	  lex->ReportError ("left parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
	    errors++;
	  }
	}
      else{
	  lex->ReportError ("EOF token expected, '" + lex->GetTokenName(token) + "' found.");
	errors++;
      }
    }
  else{
      lex->ReportError ("left parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
    errors++;
  }
  return errors;
}

int SyntacticalAnalyzer::more_defines ()
{
  string token = lex->GetToken(t)
  lexeme = lex->GetLexeme();
  int errors = 0;
  if(t == IDENT_T)
    {
      p2out << "Using Rule 3\n";
      t = lex->GetToken();
      errors += stmt_list();
      if(t == RPAREN_T)
	{
	  return errors;
	}
      else{
	  lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
	errors++;
      }
    }
  else if(t == DEFINE_T)
    {
      p2out << "Using Rule 2\n";
      errors += define();
      t = lex->GetToken();
      if(t == LPAREN_T)
	{
	  t = lex->GetToken();
	  lex->ReportError ("left parenthesis expected, '" + lex->GetTokenName(token) + "' found.");
	}
      else{
      lex->ReportError ("IDENT_T or DEFINE_T expected, '" + lex->GetTokenName(token) + "' found.");
	errors++;
      }
    }
  else{
      lex->ReportError ("IDENT_T or DEFINE_T expected, '" + lex->GetTokenName(token) + "' found.");
    errors++;
  }
  return errors;
}

int SyntacticalAnalyzer::define ()
{
  int errors = 0;
  p2out << "Using Rule 4\n";
  if(t == DEFINE_T)
    {
      t = lex->GetToken();
      if(t == LPAREN_T)
	{
	  t = lex->GetToken();
	  if(t == IDENT_T)
	    {
	      t = lex->GetToken();
	      errors += param_list();
	      if(t == RPAREN_T)
		{
		  t = lex->GetToken();
		  errors += stmt();
		  t = lex->GetToken();
		  errors += stmt_list();
		  if(t == RPAREN_T){
		    return errors;
		  }
		  else{
		   lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");

		    errors++;
		  }
		}
	      else{
	        lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");

		errors++;
	      }
	    }
	  else{
	    lex->ReportError ("IDENT_T token expected, '" + lex->GetTokenName(token) + "' found.");

	    errors++;
	  }
	}
      else{
        lex->ReportError ("left parenthesis expected, '" + lex->GetTokenName(token) + "' found.");

	errors++;
      }
    }
  else{
      lex->ReportError ("DEFINE_T token expected, '" + lex->GetTokenName(token) + "' found.");
    errors++;
  }
  return errors;
}

int SyntacticalAnalyzer::stmt_list ()
{ // Has branching non leaf
  string token = lex->GetTokenName(t)
  lexeme = lex->GetLexeme();

  int errors = 0;
  if(t == IDENT_T || t == LPAREN_T || t == NUMLIT_T || t == STRLIT_T || t == SQUOTE_T) // if(stmt)
    {
      p2out << "Using Rule 5\n";
      errors += stmt();
      t = lex->GetToken();
      errors += stmt_list();
    }
  else
    {
      p2out << "Using Rule 6\n";
      return errors;
    }
  return errors;
}

int SyntacticalAnalyzer::stmt ()
{
  int errors = 0;
  string token = lex->GetTokenName(t)
  lexeme = lex->GetLexeme();
  if(t == IDENT_T)
    {
      p2out << "Using Rule 8\n";
      return errors;
    }
  else if(t == LPAREN_T)
    {
      p2out << "Using Rule 9\n";
      t = lex->GetToken();
      if(t == DEFINE_T)
	{ // Had to add a rule since grammar did not support in-function function definitions... Rule simply loops back to more_defines()
	  p2out << "Using Rule 82\n";
	  errors += more_defines();
	}
      errors += action();
      if(nonclosure == false)
	t = lex->GetToken();
      else
	nonclosure = false;
      if(t == RPAREN_T)
	{
	  return errors;
	}
      else{
	lex->ReportError("Error: Expected ')'\n");
	errors++;
      }
    }
  else if(t == NUMLIT_T || t == STRLIT_T || t == SQUOTE_T)
    {
      p2out << "Using Rule 7\n";
      errors += literal();
    }
  else{
   lex->ReportError ("right parenthesis expected, '" + lex->GetTokenName(token) + "' found.");

    errors++;
  }
  return errors;
}

int SyntacticalAnalyzer::literal ()
{
  int errors = 0;
  if(t == NUMLIT_T)
    {
      p2out << "Using Rule 10\n";
      return errors;
    }
  else if(t == STRLIT_T)
    {
      p2out << "Using Rule 11\n";
      return errors;
    }
  else if(t == SQUOTE_T)
    {
      p2out << "Using Rule 12\n";
      t = lex->GetToken();
      errors += quoted_lit();
      return errors;
    }
  else{
    lex->ReportError("Error: Expected numeric, string, or single quote\n");
    errors++;
  }
  return errors;
}

int SyntacticalAnalyzer::quoted_lit ()
{
  int errors = 0;
  p2out << "Using Rule 13\n";
  errors += any_other_token();
  return errors;
}

int SyntacticalAnalyzer::more_tokens ()
{ // Has branching non leaf
  int errors = 0;
  if(t == IDENT_T || t == NUMLIT_T || t == STRLIT_T || t == LISTOP2_T || t == IF_T || t == DISPLAY_T || t == NEWLINE_T || t == LISTOP1_T || t == AND_T || t == OR_T || t == NOT_T || t == DEFINE_T || t == NUMBERP_T || t == LISTP_T || t == ZEROP_T || t == NULLP_T || t == STRINGP_T || t == PLUS_T || t == MINUS_T || t == DIV_T || t == MULT_T || t == MODULO_T || t ==  ROUND_T || t == EQUALTO_T || t == GT_T || t == LT_T || t == GTE_T || t == LTE_T || t == COND_T || t == ELSE_T || t == LPAREN_T || t == SQUOTE_T) // if(any_other_token)
    {
      p2out << "Using Rule 14\n";
      errors += any_other_token();
      t = lex->GetToken();
      errors += more_tokens();
    }
  else
    {
      p2out << "Using Rule 15\n";
      return errors;
    }
  return errors;
}

int SyntacticalAnalyzer::param_list ()
{
  int errors = 0;
  if(t == IDENT_T)
    {
      p2out << "Using Rule 16\n";
      t = lex->GetToken();
      errors += param_list();
    }
  else // lambda?
    {
      p2out << "Using Rule 17\n";
      return errors;
    }
  return errors;
}

int SyntacticalAnalyzer::else_part ()
{
  int errors = 0;
  if(t == IDENT_T || t == LPAREN_T || t == NUMLIT_T || t == STRLIT_T || t == SQUOTE_T) // if(stmt)
    {
      p2out << "Using Rule 18\n";
      errors += stmt();
    }
  else
    {
      p2out << "Using Rule 19\n";
      return errors;
    }
  return errors;
}

int SyntacticalAnalyzer::stmt_pair ()
{
  int errors = 0;
  if(t == LPAREN_T)
    {
      p2out << "Using Rule 20\n";
      t = lex->GetToken();
      errors += stmt_pair_body();
    }
  else
    {
      p2out << "Using Rule 21\n";
      return errors;
    }
  return errors;
}

int SyntacticalAnalyzer::stmt_pair_body ()
{
  int errors = 0;
  if(t == ELSE_T)
    {
      p2out << "Using Rule 23\n";
      t = lex->GetToken();
      errors += stmt();
      t = lex->GetToken();
      if(t == RPAREN_T)
	{
	  return errors;
	}
      else{
	lex->ReportError("Error: Expected else\n");
	errors++;
      }
    }
  else if(t == IDENT_T || t == LPAREN_T || t == NUMLIT_T || t == STRLIT_T || t == SQUOTE_T)
    {
      p2out << "Using Rule 22\n";
      errors += stmt();
      t = lex->GetToken();
      errors += stmt();
      t = lex->GetToken();
      if(t == RPAREN_T)
	{
	  t = lex->GetToken();
	  errors += stmt_pair();
	}
      else{
	lex->ReportError("Error: Expected ')'\n");
	errors++;
      }
    }
  else{
    lex->ReportError("Error: Expected input not found \n");
    errors++;
  }
  return errors;
}

int SyntacticalAnalyzer::action ()
{
  int errors = 0;
  if(t == IF_T)
    {
      p2out << "Using Rule 24\n";
      t = lex->GetToken();
      errors += stmt();
      t = lex->GetToken();
      errors += stmt();
      t = lex->GetToken();
      errors += else_part();
    }
  else if(t == COND_T)
    {
      p2out << "Using Rule 25\n";
      t = lex->GetToken();
      if(t == LPAREN_T)
	{
	  t = lex->GetToken();
	  errors += stmt_pair_body();
	}
    }
  else if(t == LISTOP1_T)
    {
      p2out << "Using Rule 26\n";
      t = lex->GetToken();
      errors += stmt();
    }
  else if(t == LISTOP2_T)
    {
      p2out << "Using Rule 27\n";
      t = lex->GetToken();
      errors += stmt();
      t = lex->GetToken();
      errors += stmt();
    }
  else if(t == AND_T)
    {
      p2out << "Using Rule 28\n";
      t = lex->GetToken();
      errors += stmt_list();
      nonclosure = true;
    }
  else if(t == OR_T)
    {
      p2out << "Using Rule 29\n";
      t = lex->GetToken();
      errors += stmt_list();
      nonclosure = true;
    }
  else if(t == NOT_T)
    {
      p2out << "Using Rule 30\n";
      t = lex->GetToken();
      errors += stmt();
    }
  else if(t == NUMBERP_T)
    {
      p2out << "Using Rule 31\n";
      t = lex->GetToken();
      errors += stmt();
    }
  else if(t == LISTP_T)
    {
      p2out << "Using Rule 32\n";
      t = lex->GetToken();
      errors += stmt();
    }
  else if(t == ZEROP_T)
    {
      p2out << "Using Rule 33\n";
      t = lex->GetToken();
      errors += stmt();
    }
  else if(t == NULLP_T)
    {
      p2out << "Using Rule 34\n";
      t = lex->GetToken();
      errors += stmt();
    }
  else if(t == STRINGP_T)
    {
      p2out << "Using Rule 35\n";
      t = lex->GetToken();
      errors += stmt();
    }
  else if(t == PLUS_T)
    {
      p2out << "Using Rule 36\n";
      t = lex->GetToken();
      errors += stmt_list();
      nonclosure = true;
    }
  else if(t == MINUS_T)
    {
      p2out << "Using Rule 37\n";
      t = lex->GetToken();
      errors += stmt();
      t = lex->GetToken();
      errors += stmt_list();
      nonclosure = true;
    }
  else if(t == DIV_T)
    {
      p2out << "Using Rule 38\n";
      t = lex->GetToken();
      errors += stmt();
      t = lex->GetToken();
      errors += stmt_list();
      nonclosure = true;
    }
  else if(t == MULT_T)
    {
      p2out << "Using Rule 39\n";
      t = lex->GetToken();
      errors += stmt_list();
      nonclosure = true;
    }
  else if(t == MODULO_T)
    {
      p2out << "Using Rule 40\n";
      t = lex->GetToken();
      errors += stmt();
      t = lex->GetToken();
      errors += stmt();
    }
  else if(t == ROUND_T)
    {
      p2out << "Using Rule 41\n";
      t = lex->GetToken();
      errors += stmt();
    }
  else if(t == EQUALTO_T)
    {
      p2out << "Using Rule 42\n";
      t = lex->GetToken();
      errors += stmt_list();
      nonclosure = true;
    }
  else if(t == GT_T)
    {
      p2out << "Using Rule 43\n";
      t = lex->GetToken();
      errors += stmt_list();
      nonclosure = true;
    }
  else if(t == LT_T)
    {
      p2out << "Using Rule 44\n";
      t = lex->GetToken();
      errors += stmt_list();
      nonclosure = true;
    }
  else if(t == GTE_T)
    {
      p2out << "Using Rule 45\n";
      t = lex->GetToken();
      errors += stmt_list();
      nonclosure = true;
    }
  else if(t == LTE_T)
    {
      p2out << "Using Rule 46\n";
      t = lex->GetToken();
      errors += stmt_list();
      nonclosure = true;
    }
  else if(t == IDENT_T)
    {
      p2out << "Using Rule 47\n";
      t = lex->GetToken();
      errors += stmt_list();
      nonclosure = true;
    }
  else if(t == DISPLAY_T)
    {
      p2out << "Using Rule 48\n";
      t = lex->GetToken();
      errors += stmt();
    }
  else if(t == NEWLINE_T)
    {
      p2out << "Using Rule 49\n";
      return errors;
    }
  else{
    lex->ReportError("Error: Expected operator \n");
    errors++;
  }
  return errors;
}

int SyntacticalAnalyzer::any_other_token ()
{
  int errors = 0;
  if(t == LPAREN_T)
    {
      p2out << "Using Rule 50\n";
      t = lex->GetToken();
      errors += more_tokens();
      if(t == RPAREN_T)
	return errors;
      else{
	lex->ReportError("Error: Expected ')'\n");
	return errors++;
      }
    }
  else if(t == SQUOTE_T)
    {
      p2out << "Using Rule 79\n";
      t = lex->GetToken();
      errors += any_other_token();
    }
  else if(t == IDENT_T)
    {
      p2out << "Using Rule 51\n";
    }
  else if(t == NUMLIT_T)
    {
      p2out << "Using Rule 52\n";
    }
  else if(t == STRLIT_T)
    {
      p2out << "Using Rule 53\n";
    }
  else if(t == LISTOP2_T)
    {
      p2out << "Using Rule 54\n";
    }
  else if(t == IF_T)
    {
      p2out << "Using Rule 55\n";
    }
  else if(t == DISPLAY_T)
    {
      p2out << "Using Rule 56\n";
    }
  else if(t == NEWLINE_T)
    {
      p2out << "Using Rule 57\n";
    }
  else if(t == LISTOP1_T)
    {
      p2out << "Using Rule 58\n";
    }
  else if(t == AND_T)
    {
      p2out << "Using Rule 59\n";
    }
  else if(t == OR_T)
    {
      p2out << "Using Rule 60\n";
    }
  else if(t == NOT_T)
    {
      p2out << "Using Rule 61\n";
    }
  else if(t == DEFINE_T)
    {
      p2out << "Using Rule 62\n";
    }
  else if(t == NUMBERP_T)
    {
      p2out << "Using Rule 63\n";
    }
  else if(t == LISTP_T)
    {
      p2out << "Using Rule 64\n";
    }
  else if(t == ZEROP_T)
    {
      p2out << "Using Rule 65\n";
    }
  else if(t == NULLP_T)
    {
      p2out << "Using Rule 66\n";
    }
  else if(t == STRINGP_T)
    {
      p2out << "Using Rule 67\n";
    }
  else if(t == PLUS_T)
    {
      p2out << "Using Rule 68\n";
    }
  else if(t == MINUS_T)
    {
      p2out << "Using Rule 69\n";
    }
  else if(t == DIV_T)
    {
      p2out << "Using Rule 70\n";
    }
  else if(t == MULT_T)
    {
      p2out << "Using Rule 71\n";
    }
  else if(t == MODULO_T)
    {
      p2out << "Using Rule 72\n";
    }
  else if(t == ROUND_T)
    {
      p2out << "Using Rule 73\n";
    }
  else if(t == EQUALTO_T)
    {
      p2out << "Using Rule 74\n";
    }
  else if(t == GT_T)
    {
      p2out << "Using Rule 75\n";
    }
  else if(t == LT_T)
    {
      p2out << "Using Rule 76\n";
    }
  else if(t == GTE_T)
    {
      p2out << "Using Rule 77\n";
    }
  else if(t == LTE_T)
    {
      p2out << "Using Rule 78\n";
    }
  else if(t == COND_T)
    {
      p2out << "Using Rule 80\n";
    }
  else if(t == ELSE_T)
    {
      p2out << "Using Rule 81\n";
    }
  else{
    lex->ReportError("Error: Expected operator\n");
    errors++;
  }
  return errors;
}

