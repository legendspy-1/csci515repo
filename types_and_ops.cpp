//Wed Oct 20 10:08:38 PM PDT 2021

#include "types_and_ops.h"

#include<cassert>
namespace gamelang {

  std::string to_string(gamelang::Type tp)
  {
    switch (tp)
    {
      case NO_TYPE:         return "no type";
      case INT:             return "int";
      case DOUBLE:          return "double";
      case STRING:          return "string";
      case ANIMATION_BLOCK: return "animation block";
      case GAME_OBJECT:     return "game_object";
      case CIRCLE:          return "circle";
      case RECTANGLE:       return "rectangle";
      case TRIANGLE:        return "triangle";
      case TEXTBOX:         return "textbox";
      case PIXMAP:          return "pixmap";
      default: assert(false);
    }
    return ""; // to prevent a compilation warning
  }

  std::string to_string(gamelang::Operator op)
  {
    switch(op)
    {
      case PLUS:          return "+";
      case MINUS:         return "-";
      case DIVIDE:        return "/";
      case MULTIPLY:      return "*";
      case MOD:           return "%";
      case UNARY_MINUS:   return "-";
      case NOT:           return "!";
      case AND:           return "&&";
      case OR:            return "||";
      case EQUAL:         return "==";
      case NOT_EQUAL:     return "!=";
      case LESS_THAN:     return "<";
      case LESS_EQUAL:    return "<=";
      case GREATER_THAN:  return ">";
      case GREATER_EQUAL: return ">=";
      case NEAR:          return "near";
      case TOUCHES:       return "touches";
      case SIN:           return "sin";
      case COS:           return "cos";
      case TAN:           return "tan";
      case ASIN:          return "asin";
      case ACOS:          return "acos";
      case ATAN:          return "atan";
      case SQRT:          return "sqrt";
      case ABS:           return "abs";
      case FLOOR:         return "floor";
      case RANDOM:        return "random"; 
      default: assert(false);
    }
    return ""; // to prevent a compilation warning
  }
}
