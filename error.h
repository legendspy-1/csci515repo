#ifndef ERROR_H
#define ERROR_H

/*
  Printing error messages using the error function unifies error
  messages, easing testing and grading.

  To issue an error message, call the following function

    void error(Error_type type,
             string s1 = "",
             string s2 = "",
             string s3 = "");

    gamelang::error(gamelang::PREVIOUSLY_DECLARED_VARIABLE, name);

  Most error messages don't use all three string arguments. Consult
  error.cpp to see how the arguments are used for a particular message.

*/
#include <string>

namespace gamelang {
    enum Error_type {
             GAME_OBJECT_ANIMATION_BLOCK_PARAMETER_TYPE_ERROR,
             ANIMATION_PARAM_DOES_NOT_MATCH_FORWARD,
             ARRAY_INDEX_MUST_BE_AN_INTEGER,
             ARRAY_SIZE_MUST_BE_AN_INTEGER,
             ARRAY_INDEX_OUT_OF_BOUNDS,
             ASSIGNMENT_TYPE_ERROR,
             LHS_IS_NON_ASSIGNABLE,
             ANIMATION_BLOCK_ASSIGNMENT_PARAMETER_TYPE_ERROR,
             EXIT_STATUS_MUST_BE_AN_INTEGER,
             ILLEGAL_TOKEN,
             INCORRECT_CONSTRUCTOR_PARAMETER_TYPE,
             INVALID_ARRAY_SIZE,
             INVALID_LHS_OF_ASSIGNMENT,
             INVALID_LHS_OF_PLUS_ASSIGNMENT,
             INVALID_LHS_OF_MINUS_ASSIGNMENT,
             INVALID_LHS_OF_PLUS_PLUS,
             INVALID_LHS_OF_MINUS_MINUS,
             INVALID_RIGHT_OPERAND_TYPE,
             INVALID_LEFT_OPERAND_TYPE,
             INVALID_TYPE_FOR_INITIAL_VALUE,
             INVALID_TYPE_FOR_FOR_STMT_EXPRESSION,
             INVALID_TYPE_FOR_IF_STMT_EXPRESSION,
             INVALID_TYPE_FOR_PRINT_STMT_EXPRESSION,
             INVALID_TYPE_FOR_RESERVED_VARIABLE,
             INVALID_ARGUMENT_FOR_RANDOM,
             LHS_OF_PERIOD_MUST_BE_OBJECT,
             MINUS_ASSIGNMENT_TYPE_ERROR,
             NO_BODY_PROVIDED_FOR_FORWARD,
             OPERAND_MUST_BE_A_GAME_OBJECT,
             PARSE_ERROR,
             PLUS_ASSIGNMENT_TYPE_ERROR,
             PREVIOUSLY_DECLARED_VARIABLE,
             PREVIOUSLY_DEFINED_ANIMATION_BLOCK,
             TYPE_MISMATCH_BETWEEN_ANIMATION_BLOCK_AND_OBJECT,
             UNDECLARED_MEMBER,
             UNDECLARED_VARIABLE,
             UNKNOWN_CONSTRUCTOR_PARAMETER,
             VARIABLE_NOT_AN_ARRAY,
             VARIABLE_IS_AN_ARRAY,
             DIVIDE_BY_ZERO_AT_PARSE_TIME,
             MOD_BY_ZERO_AT_PARSE_TIME,
             REDECLARATION_OF_SYMBOL_AS_ANIMATION_BLOCK,
             UNDEFINED_ERROR
            };

   void error(Error_type type, std::string s1 = "", std::string s2 = "", std::string s3 = "");
   void starting_execution();
   int num_errors();
   bool runtime();
}
#endif // #ifndef ERROR_H
