// File: Expression.cpp
#include "Expression.h"
#include "Constant.h"
#include "error.h"
#include "scope_man.h"
#include<string>
#include <cmath>
#include <numbers>
using std::string;

extern Scope_manager sm;


const Constant* Add::evaluate() const
{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  if(lht==gamelang::STRING || rht==gamelang::STRING)
    return new String_constant(lhs_constant->as_string() + //<--addition
                               rhs_constant->as_string());
  if(lht==gamelang::DOUBLE || rht==gamelang::DOUBLE)
    return new Double_constant(lhs_constant->as_double() + //<--addition
                               rhs_constant->as_double());
  return new Integer_constant(lhs_constant->as_int() +     //<--addition
                              rhs_constant->as_int());
}

gamelang::Type Add::type() const
{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  if(lht==gamelang::STRING || rht==gamelang::STRING)
    return gamelang::STRING;
  if(lht==gamelang::DOUBLE || rht==gamelang::DOUBLE)
    return gamelang::DOUBLE;
  return gamelang::INT; 
}

const Constant* Multiply::evaluate() const
{
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  if(lhs->type()==gamelang::DOUBLE || rhs->type()==gamelang::DOUBLE)
    return new Double_constant(lhs_constant->as_double() * //<--multiply
                               rhs_constant->as_double());
  return new Integer_constant(lhs_constant->as_int() *     //<--multiply
                              rhs_constant->as_int());
}

gamelang::Type Multiply::type() const
{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  if(lht==gamelang::DOUBLE || rht==gamelang::DOUBLE)
    return gamelang::DOUBLE;
  return gamelang::INT;
}

const Constant* Subtract::evaluate() const {
  gamelang::Type lht = lhs->type();
  gamelang::Type rht = rhs->type();
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  
  if (lht == gamelang::DOUBLE || rht == gamelang::DOUBLE) {
    return new Double_constant(lhs_constant->as_double() - rhs_constant->as_double());
  }
  return new Integer_constant(lhs_constant->as_int() - rhs_constant->as_int());
}

gamelang::Type Subtract::type() const {
  gamelang::Type lht = lhs->type();
  gamelang::Type rht = rhs->type();
  if (lht == gamelang::DOUBLE || rht == gamelang::DOUBLE) {
    return gamelang::DOUBLE;
  }
  return gamelang::INT;
}

const Constant* Divide::evaluate() const {
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  
  if (lhs->type() == gamelang::DOUBLE || rhs->type() == gamelang::DOUBLE) {
      double rhs_val = rhs_constant->as_double();
      if (!gamelang::runtime() && rhs_val == 0.0) {
          gamelang::error(gamelang::DIVIDE_BY_ZERO_AT_PARSE_TIME);
          return new Integer_constant(0);
      }
      return new Double_constant(lhs_constant->as_double() / rhs_val);
  }
  
  int rhs_val = rhs_constant->as_int();
  if (!gamelang::runtime() && rhs_val == 0) {
      gamelang::error(gamelang::DIVIDE_BY_ZERO_AT_PARSE_TIME);
      return new Integer_constant(0);
  }
  return new Integer_constant(lhs_constant->as_int() / rhs_val);
}

gamelang::Type Divide::type() const {
  gamelang::Type lht = lhs->type();
  gamelang::Type rht = rhs->type();
  if (lht == gamelang::DOUBLE || rht == gamelang::DOUBLE) {
      return gamelang::DOUBLE;
  }
  return gamelang::INT;
}

const Constant* Mod::evaluate() const {
  bool left_invalid = (lhs->type() != gamelang::INT);
    bool right_invalid = (rhs->type() != gamelang::INT);
    
    if (left_invalid || right_invalid) {
        if (left_invalid) {
            gamelang::error(gamelang::INVALID_LEFT_OPERAND_TYPE, "%");
        }
        if (right_invalid) {
            gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "%");
        }
        return new Integer_constant(0);
    }

    std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
    std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
    
    int rhs_val = rhs_constant->as_int();
    if (!gamelang::runtime() && rhs_val == 0) {
        gamelang::error(gamelang::MOD_BY_ZERO_AT_PARSE_TIME);
        return new Integer_constant(0);
    }
    return new Integer_constant(lhs_constant->as_int() % rhs_val);
}

gamelang::Type Mod::type() const {
  return gamelang::INT; 
}

const Constant* Or::evaluate() const {
  bool left_invalid = (lhs->type() == gamelang::STRING);
    bool right_invalid = (rhs->type() == gamelang::STRING);
    
    if (left_invalid || right_invalid) {
        if (left_invalid) {
            gamelang::error(gamelang::INVALID_LEFT_OPERAND_TYPE, "||");
        }
        if (right_invalid) {
            gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "||");
        }
        return new Integer_constant(0);
    }

    std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
    bool lhs_true = false;
    
    switch(lhs->type()) {
        case gamelang::INT: 
            lhs_true = (lhs_constant->as_int() != 0); 
            break;
        case gamelang::DOUBLE: 
            lhs_true = (lhs_constant->as_double() != 0.0); 
            break;
        default:
            break; 
    }
    
    if (lhs_true) {
        return new Integer_constant(1);
    }
    
    std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
    bool rhs_true = false;
    switch(rhs->type()) {
        case gamelang::INT: 
            rhs_true = (rhs_constant->as_int() != 0); 
            break;
        case gamelang::DOUBLE: 
            rhs_true = (rhs_constant->as_double() != 0.0); 
            break;
        default:
            break; 
    }
    
    return new Integer_constant(rhs_true ? 1 : 0);
}

gamelang::Type Or::type() const {
  return gamelang::INT;  //returns (0 or 1)
}

const Constant* And::evaluate() const {
  bool left_invalid = (lhs->type() == gamelang::STRING);
  bool right_invalid = (rhs->type() == gamelang::STRING);
  
  if (left_invalid || right_invalid) {
      if (left_invalid) {
          gamelang::error(gamelang::INVALID_LEFT_OPERAND_TYPE, "&&");
      }
      if (right_invalid) {
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "&&");
      }
      return new Integer_constant(0);
  }

  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  bool lhs_true = false;
  
  switch(lhs->type()) {
      case gamelang::INT: 
          lhs_true = (lhs_constant->as_int() != 0); 
          break;
      case gamelang::DOUBLE: 
          lhs_true = (lhs_constant->as_double() != 0.0); 
          break;
      default:
          break; 
  }
  
  if (!lhs_true) {
      return new Integer_constant(0);
  }
  
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  bool rhs_true = false;
  switch(rhs->type()) {
      case gamelang::INT: 
          rhs_true = (rhs_constant->as_int() != 0); 
          break;
      case gamelang::DOUBLE: 
          rhs_true = (rhs_constant->as_double() != 0.0); 
          break;
      default:
          break; 
  }
  
  return new Integer_constant(rhs_true ? 1 : 0);
}

gamelang::Type And::type() const {
  return gamelang::INT;  // returns (0 or 1)
}

const Constant* LessThanOrEqual::evaluate() const {
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  
  if (lhs->type() == gamelang::STRING || rhs->type() == gamelang::STRING) {
      std::string lhs_str = lhs_constant->as_string();
      std::string rhs_str = rhs_constant->as_string();
      return new Integer_constant(lhs_str <= rhs_str ? 1 : 0);
  }
  
  if (lhs->type() == gamelang::DOUBLE || rhs->type() == gamelang::DOUBLE) {
      return new Integer_constant(lhs_constant->as_double() <= rhs_constant->as_double() ? 1 : 0);
  }
  
  return new Integer_constant(lhs_constant->as_int() <= rhs_constant->as_int() ? 1 : 0);
}

gamelang::Type LessThanOrEqual::type() const {
  return gamelang::INT;  
}

const Constant* GreaterThanOrEqual::evaluate() const {
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  
  // string comparisons
  if (lhs->type() == gamelang::STRING || rhs->type() == gamelang::STRING) {
      // If both string
      std::string lhs_str = lhs_constant->as_string();
      std::string rhs_str = rhs_constant->as_string();
      return new Integer_constant(lhs_str >= rhs_str ? 1 : 0);
  }
  
  if (lhs->type() == gamelang::DOUBLE || rhs->type() == gamelang::DOUBLE) {
      return new Integer_constant(lhs_constant->as_double() >= rhs_constant->as_double() ? 1 : 0);
  }
  
  return new Integer_constant(lhs_constant->as_int() >= rhs_constant->as_int() ? 1 : 0);
}

gamelang::Type GreaterThanOrEqual::type() const {
  return gamelang::INT;  
}

const Constant* LessThan::evaluate() const {
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  
  if (lhs->type() == gamelang::STRING || rhs->type() == gamelang::STRING) {
      std::string lhs_str = lhs_constant->as_string();
      std::string rhs_str = rhs_constant->as_string();
      return new Integer_constant(lhs_str < rhs_str ? 1 : 0);
  }
  
  if (lhs->type() == gamelang::DOUBLE || rhs->type() == gamelang::DOUBLE) {
      return new Integer_constant(lhs_constant->as_double() < rhs_constant->as_double() ? 1 : 0);
  }
  
  return new Integer_constant(lhs_constant->as_int() < rhs_constant->as_int() ? 1 : 0);
}

gamelang::Type LessThan::type() const {
  return gamelang::INT;
}

const Constant* GreaterThan::evaluate() const {
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  
  if (lhs->type() == gamelang::STRING || rhs->type() == gamelang::STRING) {
      std::string lhs_str = lhs_constant->as_string();
      std::string rhs_str = rhs_constant->as_string();
      return new Integer_constant(lhs_str > rhs_str ? 1 : 0);
  }
  
  if (lhs->type() == gamelang::DOUBLE || rhs->type() == gamelang::DOUBLE) {
      return new Integer_constant(lhs_constant->as_double() > rhs_constant->as_double() ? 1 : 0);
  }
  
  return new Integer_constant(lhs_constant->as_int() > rhs_constant->as_int() ? 1 : 0);
}

gamelang::Type GreaterThan::type() const {
  return gamelang::INT;
}

const Constant* Equal::evaluate() const {
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  
  if (lhs->type() == gamelang::STRING || rhs->type() == gamelang::STRING) {
      std::string lhs_str = lhs_constant->as_string();
      std::string rhs_str = rhs_constant->as_string();
      return new Integer_constant(lhs_str == rhs_str ? 1 : 0);
  }
  
  if (lhs->type() == gamelang::DOUBLE || rhs->type() == gamelang::DOUBLE) {
      return new Integer_constant(lhs_constant->as_double() == rhs_constant->as_double() ? 1 : 0);
  }
  
  return new Integer_constant(lhs_constant->as_int() == rhs_constant->as_int() ? 1 : 0);
}

gamelang::Type Equal::type() const {
  return gamelang::INT;
}

const Constant* NotEqual::evaluate() const {
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  
  if (lhs->type() == gamelang::STRING || rhs->type() == gamelang::STRING) {
      std::string lhs_str = lhs_constant->as_string();
      std::string rhs_str = rhs_constant->as_string();
      return new Integer_constant(lhs_str != rhs_str ? 1 : 0);
  }
  
  if (lhs->type() == gamelang::DOUBLE || rhs->type() == gamelang::DOUBLE) {
      return new Integer_constant(lhs_constant->as_double() != rhs_constant->as_double() ? 1 : 0);
  }
  
  return new Integer_constant(lhs_constant->as_int() != rhs_constant->as_int() ? 1 : 0);
}

gamelang::Type NotEqual::type() const {
  return gamelang::INT;
}

const Constant* Negation::evaluate() const {
  std::unique_ptr<const Constant> expr_constant(expr->evaluate());
  
  switch(expr->type()) {
      case gamelang::INT:
          return new Integer_constant(-expr_constant->as_int());
      case gamelang::DOUBLE:
          return new Double_constant(-expr_constant->as_double());
      default:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "-");
          return new Integer_constant(0);
  }
}

gamelang::Type Negation::type() const {
  return expr->type(); 
}

const Constant* Not::evaluate() const {
  std::unique_ptr<const Constant> expr_constant(expr->evaluate());
  
  switch(expr->type()) {
      case gamelang::INT:
          return new Integer_constant(expr_constant->as_int() == 0 ? 1 : 0);
      case gamelang::DOUBLE:
          return new Integer_constant(expr_constant->as_double() == 0.0 ? 1 : 0);
      case gamelang::STRING:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "!", "string");
          return new Integer_constant(0);
      default:
          return new Integer_constant(0);
  }
}

gamelang::Type Not::type() const {
  return gamelang::INT; 
}

const Constant* Sin::evaluate() const {
  std::unique_ptr<const Constant> expr_constant(expr->evaluate());
    
    double radians;
    switch(expr->type()) {
        case gamelang::INT:
            radians = expr_constant->as_int() * (std::numbers::pi / 180.0);
            return new Double_constant(sin(radians));
        case gamelang::DOUBLE:
            radians = expr_constant->as_double() * (std::numbers::pi / 180.0);
            return new Double_constant(sin(radians));
        case gamelang::STRING:
            gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "sin");
            return nullptr;
        default:
            gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "sin");
            return nullptr;
    }
}

gamelang::Type Sin::type() const {
  return gamelang::DOUBLE;
}

const Constant* Cos::evaluate() const {
  std::unique_ptr<const Constant> expr_constant(expr->evaluate());
  
  switch(expr->type()) {
      case gamelang::INT:
          {
              double radians = expr_constant->as_int() * (std::numbers::pi / 180.0);
              return new Double_constant(cos(radians));
          }
      case gamelang::DOUBLE:
          {
              double radians = expr_constant->as_double() * (std::numbers::pi / 180.0);
              return new Double_constant(cos(radians));
          }
      case gamelang::STRING:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "cos");
          return nullptr;
      default:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "cos");
          return nullptr;
  }
}

gamelang::Type Cos::type() const {
  return gamelang::DOUBLE;
}

const Constant* Tan::evaluate() const {
  std::unique_ptr<const Constant> expr_constant(expr->evaluate());
  
  switch(expr->type()) {
      case gamelang::INT:
          {
              double radians = expr_constant->as_int() * (std::numbers::pi / 180.0);
              return new Double_constant(tan(radians));
          }
      case gamelang::DOUBLE:
          {
              double radians = expr_constant->as_double() * (std::numbers::pi / 180.0);
              return new Double_constant(tan(radians));
          }
      case gamelang::STRING:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "tan");
          return nullptr;
      default:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "tan");
          return nullptr;
  }
}

gamelang::Type Tan::type() const {
  return gamelang::DOUBLE;
}

const Constant* Asin::evaluate() const {
  std::unique_ptr<const Constant> expr_constant(expr->evaluate());

  switch (expr->type()) {
    case gamelang::INT: {
      double value = expr_constant->as_int();
      double radians = asin(value); // asin() will return nan if out-of-range
      return new Double_constant(radians * (180.0 / std::numbers::pi));
    }
    case gamelang::DOUBLE: {
      double value = expr_constant->as_double();
      double radians = asin(value); // same here
      return new Double_constant(radians * (180.0 / std::numbers::pi));
    }
    case gamelang::STRING:
      gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "asin");
      return nullptr;
    default:
      gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "asin");
      return nullptr;
  }
}

gamelang::Type Asin::type() const {
  return gamelang::DOUBLE;
}

const Constant* Acos::evaluate() const {
  std::unique_ptr<const Constant> expr_constant(expr->evaluate());

  switch (expr->type()) {
    case gamelang::INT: {
      double value = expr_constant->as_int();
      double radians = acos(value);  // will return nan if out of [-1, 1]
      return new Double_constant(radians * (180.0 / std::numbers::pi));
    }
    case gamelang::DOUBLE: {
      double value = expr_constant->as_double();
      double radians = acos(value);  // will return nan if out of [-1, 1]
      return new Double_constant(radians * (180.0 / std::numbers::pi));
    }
    case gamelang::STRING:
      gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "acos");
      return nullptr;
    default:
      gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "acos");
      return nullptr;
  }
}

gamelang::Type Acos::type() const {
  return gamelang::DOUBLE;
}

const Constant* Atan::evaluate() const {
  std::unique_ptr<const Constant> expr_constant(expr->evaluate());
  
  switch(expr->type()) {
      case gamelang::INT:
          {
              double radians = atan(expr_constant->as_int());
              return new Double_constant(radians * (180.0 / std::numbers::pi)); 
          }
      case gamelang::DOUBLE:
          {
              double radians = atan(expr_constant->as_double());
              return new Double_constant(radians * (180.0 / std::numbers::pi)); 
          }
      case gamelang::STRING:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "atan");
          return nullptr;
      default:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "atan");
          return nullptr;
  }
}

gamelang::Type Atan::type() const {
  return gamelang::DOUBLE;
}

const Constant* Sqrt::evaluate() const {
  std::unique_ptr<const Constant> expr_constant(expr->evaluate());
  
  switch(expr->type()) {
      case gamelang::INT: {
          int value = expr_constant->as_int();
          if (value < 0) {
              gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "sqrt");
              return new Double_constant(std::numeric_limits<double>::quiet_NaN());
          }
          return new Double_constant(sqrt(static_cast<double>(value)));
      }
      case gamelang::DOUBLE: {
          double value = expr_constant->as_double();
          if (value < 0) {
              gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "sqrt");
              return new Double_constant(std::numeric_limits<double>::quiet_NaN());
          }
          return new Double_constant(sqrt(value));
      }
      case gamelang::STRING:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "sqrt");
          return nullptr;
      default:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "sqrt");
          return nullptr;
  }
}

gamelang::Type Sqrt::type() const {
  return gamelang::DOUBLE;
}

const Constant* Abs::evaluate() const {
  std::unique_ptr<const Constant> expr_constant(expr->evaluate());
  
  switch(expr->type()) {
      case gamelang::INT:
          return new Integer_constant(abs(expr_constant->as_int()));
      case gamelang::DOUBLE:
          return new Double_constant(fabs(expr_constant->as_double()));
      case gamelang::STRING:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "abs");
          return nullptr;
      default:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "abs");
          return nullptr;
  }
}

gamelang::Type Abs::type() const {
  return expr->type(); 
}

const Constant* Floor::evaluate() const {
  std::unique_ptr<const Constant> expr_constant(expr->evaluate());

  switch(expr->type()) {
    case gamelang::INT:
      return new Integer_constant(expr_constant->as_int());

    case gamelang::DOUBLE: {
      double result = floor(expr_constant->as_double());

      if (result == floor(result)) {
        return new Integer_constant(static_cast<int>(result));
      } else {
        return new Double_constant(result);
      }
    }

    case gamelang::STRING:
      gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "floor");
      return new Integer_constant(0);  

    default:
      gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "floor");
      return new Integer_constant(0);
  }
}

gamelang::Type Floor::type() const {
  std::unique_ptr<const Constant> val(expr->evaluate());
  // if type is int
  if (expr->type() == gamelang::INT) {
    return gamelang::INT;
  }
  double floored = floor(val->as_double());
  if (floored == static_cast<int>(floored)) {
    return gamelang::INT;
  } else {
    return gamelang::DOUBLE;
  }
}

const Constant* Random::evaluate() const {
  std::unique_ptr<const Constant> expr_constant(expr->evaluate());
  double value;
  std::string value_str;

  switch (expr->type()) {
      case gamelang::INT:
          value = expr_constant->as_int();
          value_str = std::to_string(static_cast<int>(value)); // integer string
          break;
      case gamelang::DOUBLE:
          value = expr_constant->as_double();
          value_str = std::to_string(value); // double string
          break;
      case gamelang::STRING:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "random");
          return new Integer_constant(0);
      default:
          gamelang::error(gamelang::INVALID_RIGHT_OPERAND_TYPE, "random");
          return new Integer_constant(0);
  }

  if (value < 2) {
      gamelang::error(gamelang::INVALID_ARGUMENT_FOR_RANDOM, value_str);
      value = 2;
  }

  int result = rand() % static_cast<int>(floor(value));
  return new Integer_constant(result);
}

gamelang::Type Random::type() const {
  return gamelang::INT; // always an int
}


const Constant* Variable::evaluate() const {
  if (symbol_name.empty()) {
    return new Integer_constant(0); // fallback
  }

  Symbol* symbol = sm.lookup(symbol_name);
  if (!symbol) {
    std::string display_name = symbol_name;
    if (array_index_expression) {
        display_name += "[]";
    }
    gamelang::error(gamelang::UNDECLARED_VARIABLE, display_name);
    return new Integer_constant(0); // fallback
  }

  if (!array_index_expression) {
    return symbol->as_constant();  // scalar access
  }

  // If the symbol is not an array, emit a semantic error
  if (symbol->get_count() == 1) {
    gamelang::error(gamelang::VARIABLE_NOT_AN_ARRAY, symbol_name);
    return new Integer_constant(0); // fallback
  }

  std::unique_ptr<const Constant> index_const(array_index_expression->evaluate());
  if (!index_const) {
    gamelang::error(gamelang::ARRAY_INDEX_MUST_BE_AN_INTEGER, symbol_name,
                    gamelang::to_string(index_const->type()));
    return new Integer_constant(0); // fallback
  }

  if (index_const->type() != gamelang::INT) {
    gamelang::error(gamelang::ARRAY_INDEX_MUST_BE_AN_INTEGER, symbol_name, 
                    gamelang::to_string(index_const->type()));
    return new Integer_constant(0); // fallback
  }

  int index = index_const->as_int();
  if (index < 0 || index >= symbol->get_count()) {
    gamelang::error(gamelang::ARRAY_INDEX_OUT_OF_BOUNDS, symbol_name, std::to_string(index) );
    return new Integer_constant(0); // fallback
  }

  return symbol->as_constant(index);
}

gamelang::Type Variable::type() const {
  if (symbol_name.empty()) {
      return gamelang::INT;
  }

  Symbol* symbol = sm.lookup(symbol_name);
  if (!symbol) {
    return gamelang::INT; 
  }
  return symbol->get_type();
}