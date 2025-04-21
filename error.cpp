#include "error.h"

#include <iostream>
using std::cerr;
using std::endl;
using std::string;


extern int line_count; // the line number of current token

namespace gamelang {

static bool m_runtime = false;
static int  m_num_errors = 0;

void starting_execution() {m_runtime = true;}
int num_errors() {return m_num_errors;}
bool runtime() {return m_runtime;}


void error_header() {
  if (m_runtime) cerr << "Runtime error: ";
  else cerr << "Semantic error on line " << line_count  << ": ";
}

void error(Error_type type, string s1, string s2, string s3) {
  m_num_errors++;
  switch (type)
  {
    case ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD:
      error_header();
      cerr << "The animation block's parameter type ("<<s1<<") does not match "
           << "the parameter type specified in the forward statement ("<<s2<<")."
           << endl;
      break;
    case ARRAY_INDEX_MUST_BE_AN_INTEGER:
      error_header();
        cerr << "A " << s2
             << " expression is not a legal array index. The array is '"
             << s1 << "'.";
        if (m_runtime)
          cerr << "  Element '" << s1 <<"[0]' will be used instead.";
        cerr << endl;
      break;
    case ARRAY_SIZE_MUST_BE_AN_INTEGER:
      error_header();
        cerr << "The given expression is not a legal type for the size of array <" 
        << s2 
        << ">.  The size must be an integer.  Given expression is of type " 
        << s1 << ".";
        cerr << endl;
      break;

    case ARRAY_INDEX_OUT_OF_BOUNDS:
      error_header();
        cerr << "Index value '" << s2
             << "' is out of bounds for array '"
             << s1 << "'.";
        if (m_runtime)
          cerr << "  Element '" << s1 <<"[0]' will be used instead.";
        cerr << endl;
      break;
    case ASSIGNMENT_TYPE_ERROR:
      error_header();
      cerr << "Cannot assign an expression of type '" << s2
           << "' to a variable of type '" << s1 << "'."
           << endl;
      break;
    case LHS_IS_NON_ASSIGNABLE:
      error_header();
      cerr << "The lefthand side is a non-assignable rvalue." << endl;
      break;
    case GAME_OBJECT_ANIMATION_BLOCK_PARAMETER_TYPE_ERROR:
      error_header();
      cerr << "Cannot initialize the animation_block attribute of a '" << s1
           << "' with an animation block designed for a '" << s2 << "'."
           << endl;
      break;
    case ANIMATION_BLOCK_ASSIGNMENT_PARAMETER_TYPE_ERROR:
      error_header();
      cerr << "Cannot assign an animation block with parameter of type '" << s2
           << "' to an animation block with parameter of type '" << s1 << "'."
           << endl;
      break;
    // some attributes (such as h & w in a circle) cannot be changed
    case EXIT_STATUS_MUST_BE_AN_INTEGER:
      error_header();
      cerr << "Value passed to exit() must be an integer. "
           << "Value passed was of type '" << s1  << "'."
           << endl;
      break;

    // this error originates from gpl.y when it finds an illegal token
    case ILLEGAL_TOKEN:
      cerr << "Syntax error on line "
           << line_count
           << " '" << s1 << "'" << " is not a legal token."
           << endl;
      break;
    case INCORRECT_CONSTRUCTOR_PARAMETER_TYPE:
      error_header();
      cerr << "Incorrect type for parameter '"
           << s2 << "' of object " << s1  << "."
           << endl;
      break;
    case INVALID_ARRAY_SIZE:
      error_header();
      cerr << "The array '" << s1 << "' was declared with illegal size '"
           << s2 << "'. Arrays sizes must be integers of 1 or larger."
           << endl;
      break;
    // everything but a game object is a legal LHS of assignment
    case INVALID_LHS_OF_ASSIGNMENT:
      error_header();
      cerr << "LHS of assignment must be "
           << "(INT || DOUBLE || STRING || ANIMATION_BLOCK)."
           << "  Variable '" << s1 << "' is of type '"  << s2 << "'."
           << endl;
      break;
    case INVALID_LHS_OF_PLUS_ASSIGNMENT:
      error_header();
      cerr << "LHS of plus-assignment must be (INT || DOUBLE || STRING)."
           << "  Variable '" << s1 << "' is of type '"  << s2 << "'."
           << endl;
      break;
    case INVALID_LHS_OF_MINUS_ASSIGNMENT:
      error_header();
      cerr << "LHS of minus-assignment must be (INT || DOUBLE)."
           << "  Variable '" << s1 << "' is of type '"  << s2 << "'."
           << endl;
      break;
    case INVALID_LHS_OF_PLUS_PLUS:
      error_header();
      cerr << "LHS of ++ must be INT."
           << "  Variable '" << s1 << "' is of type '"  << s2 << "'."
           << endl;
      break;
    case INVALID_LHS_OF_MINUS_MINUS:
      error_header();
      cerr << "LHS of -- must be INT."
           << "  Variable '" << s1 << "' is of type '"  << s2 << "'."
           << endl;
      break;
    case INVALID_LEFT_OPERAND_TYPE:
      error_header();
      cerr << "Invalid left operand for operator '" << s1 << "'."
           << endl;
      break;
    case INVALID_RIGHT_OPERAND_TYPE:
      error_header();
      cerr << "Invalid right operand for operator '" << s1 << "'."
           << endl;
      break;
    case INVALID_TYPE_FOR_INITIAL_VALUE:
      error_header();
      cerr << "Incorrect type (" <<  s1 << ") for initial value of variable '"
           << s2 << "' of type (" << s3 << ")."
           << endl;
      break;
    case INVALID_TYPE_FOR_FOR_STMT_EXPRESSION:
      error_header();
      cerr << "Incorrect type for expression in for statement."
           << "  Expressions in for statements must be of type INT."
           << endl;
      break;
    case INVALID_TYPE_FOR_IF_STMT_EXPRESSION:
      error_header();
      cerr << "Incorrect type for expression in an if statement."
           << "  Expressions in if statements must be of type INT."
           << endl;
      break;
    case INVALID_TYPE_FOR_PRINT_STMT_EXPRESSION:
      error_header();
      cerr << "Incorrect type for expression in a print statement."
           << "  Expressions in print statements must be"
           << " of type INT, DOUBLE, or STRING."
           << endl;
      break;
    case INVALID_TYPE_FOR_RESERVED_VARIABLE:
      error_header();
      cerr << "Incorrect type for reserved variable '" << s1
           << "'. It was declared with type '" << s2
           << "'. It must be of type '" << s3 << "'."
           << endl;
      break;
    case INVALID_ARGUMENT_FOR_RANDOM:
      // This is an unusual error.  If evaluated at parse time, the program
      // is terminated as with all other errors.
      // If evaluated at run time, the program issues the error and 
      // using 2 as the default.
      error_header();
      cerr << "Illegal argument to random()<" << s1 << ">.  Must be >= 2.";
      if (m_runtime)
           cerr << "  Using 2 as the range.";
      cerr << endl;
      break;
    case LHS_OF_PERIOD_MUST_BE_OBJECT:
      error_header();
      cerr << "Variable '" << s1 << "' is not an object."
           << "  Only objects may be on the left of a period."
           << endl;
      break;
    case MINUS_ASSIGNMENT_TYPE_ERROR:
      error_header();
      cerr << "Cannot -= an expression of type '" << s2
           << "' from a variable of type '" << s1 << "'."
           << endl;
      break;
    case NO_BODY_PROVIDED_FOR_FORWARD:
      error_header();
      cerr << "No body was provided for animation block '" << s1
           << "' which was declared in a forward statement."
           << endl;
      break;

    // game objects are the only valid operands for near and touches
    // s1 should be either "Left" or "Right"
    case OPERAND_MUST_BE_A_GAME_OBJECT:
      error_header();
      cerr << s1 << " operand to geometric operators must be a Game_object "
           << "(circle, rectangle, triangle, etc.)"
           << endl;
      break;
    // only called in gpl.cpp when parser finds an error
    // called from yyerror()
    case PARSE_ERROR:
      cerr << "Parse error on line "
           << line_count
           << " reported by parser: "
           << s1 << "."
           << endl;
      break;
    case PLUS_ASSIGNMENT_TYPE_ERROR:
      error_header();
      cerr << "Cannot += an expression of type '" << s2
           << "' to a variable of type '" << s1 << "'."
           << endl;
      break;
    case PREVIOUSLY_DECLARED_VARIABLE:
      error_header();
      cerr << "Variable '"<< s1 << "'" << " previously declared."
           << endl;
      break;
    case PREVIOUSLY_DEFINED_ANIMATION_BLOCK:
      error_header();
      cerr << "Multiple definitions of animation block '"<< s1 << "'." << endl;
      break;
    case TYPE_MISMATCH_BETWEEN_ANIMATION_BLOCK_AND_OBJECT:
      error_header();
      cerr << "The type of object '"<< s1 << "'"
           << " does not match the type of the parameter to the "
           << "animation block '" << s2 << "'"
           << endl;
      break;
    case UNDECLARED_MEMBER:
      error_header();
      cerr << "Object '" << s1 << "'"
           << " does not contain the member variable '"
           << s2 << "'."
           << endl;
      break;
    case UNDECLARED_VARIABLE:
      error_header();
      cerr << "Variable '" << s1 << "'"
           << " was not declared before it was used."
           << endl;
      break;
    case UNKNOWN_CONSTRUCTOR_PARAMETER:
      error_header();
      cerr << "Game object '" << s1 << "' does not have a parameter called '"
           << s2 << "'."
           << endl;
      break;
    case VARIABLE_NOT_AN_ARRAY:
      error_header();
      cerr << "Variable '" << s1 << "' is not an array."
           << endl;
      break;
    case VARIABLE_IS_AN_ARRAY:
      error_header();
      cerr << "Variable '" << s1 << "' is an array."
           << endl;
      break;
    case DIVIDE_BY_ZERO_AT_PARSE_TIME:
      error_header();
      cerr << "Arithmetic divide by zero at parse time. "
           << "Using zero as the result so parse can continue."
           << endl;
      break;
    case MOD_BY_ZERO_AT_PARSE_TIME:
      error_header();
      cerr << "Arithmetic mod by zero at parse time. "
           << "Using zero as the result so parse can continue."
           << endl;
      break;
    case REDECLARATION_OF_SYMBOL_AS_ANIMATION_BLOCK:
      error_header();
      cerr << "Redeclaration of symbol " << s1 
           << " as animation_block."
           << endl;
      break;
    case UNDEFINED_ERROR:
      error_header();
      cerr << "Undefined error passed to Error::error(). "
           << "This is probably because error.cpp was not updated "
           << "when a new error was added to error.h."
           << endl;
      break;
    default:
      cerr << "Unknown error sent to class Error::error()."
           << endl;
      break;
  }
}

}
