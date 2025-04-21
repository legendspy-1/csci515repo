/* 
 * gamelang::Type      enumeration of the types in Game Programming Language
 * gamelang::Operator  enumeration of the operators in Game Programming Language
 * gamelang::to_string() overloaded utility function to convert the enumerations to strings
 */

#ifndef TYPES_AND_OPS_H
#define TYPES_AND_OPS_H

#include <string>

namespace gamelang {

  // Assigned powers of 2 so that bitwise operations can be used
  // Use the enumerated value (e.g. CIRCLE), never the numbers (e.g. 48)
  // 
  enum Type {
    NO_TYPE         =    0,
    INT             =    1,
    DOUBLE          =    2,
    STRING          =    4,
    ANIMATION_BLOCK =    8,
    GAME_OBJECT     =   16,
    CIRCLE          =   32 + GAME_OBJECT, //  48
    RECTANGLE       =   64 + GAME_OBJECT, //  80
    TRIANGLE        =  128 + GAME_OBJECT, // 144
    TEXTBOX         =  256 + GAME_OBJECT, // 272
    PIXMAP          =  512 + GAME_OBJECT, // 528
  };

  std::string to_string(gamelang::Type tp);


  // NOTE: 
  //   ++ and -- are statements in Game Programming Language, 
  //   not arithmetic operators
  enum Operator {
    NO_OP,
    PLUS, MINUS, MULTIPLY, DIVIDE, MOD,
    UNARY_MINUS, NOT,
    AND, OR,
    EQUAL, NOT_EQUAL,
    LESS_THAN, LESS_EQUAL,
    GREATER_THAN, GREATER_EQUAL,
    NEAR, TOUCHES,
    SIN, COS, TAN,
    ASIN, ACOS, ATAN,
    SQRT, FLOOR, ABS, RANDOM
  };

  std::string to_string(gamelang::Operator op);
}
#endif
