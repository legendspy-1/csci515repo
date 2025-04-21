//File: Expression.h
#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <memory>
#include "types_and_ops.h"
class Constant;
class Expression {
  public:
    Expression() = default;
    virtual const Constant* evaluate() const=0;
    virtual gamelang::Type type() const=0;
    virtual ~Expression() = default;
    Expression& operator=(const Expression&) = delete;
  protected:
    Expression(const Expression&) = default;
};

class Variable : public Expression {
  public:
    Variable(const std::string& symbol_name)
      : symbol_name(symbol_name), array_index_expression(nullptr) {}

    Variable(const std::string& symbol_name, const Expression* index_expr)
      : symbol_name(symbol_name), array_index_expression(index_expr) {}

    virtual const Constant* evaluate() const override;
    virtual gamelang::Type type() const override;
    virtual ~Variable() = default;

    Variable(const Variable&) = delete;
    Variable& operator=(const Variable&) = delete;
    const std::string& get_symbol_name() const { return symbol_name; }
    bool is_whole_array_reference() const {
      return array_index_expression == nullptr;
    }

  protected:
    std::string symbol_name;
    std::unique_ptr<const Expression> array_index_expression;
};

class Binary_operator : public Expression {
  public:
    Binary_operator(const Expression* lhs, const Expression* rhs) :lhs(lhs), rhs(rhs) {}
    virtual const Constant* evaluate() const=0;
  protected:
    std::unique_ptr<const Expression> lhs;
    std::unique_ptr<const Expression> rhs;
};

class Subtract : public Binary_operator {
  public:
    Subtract(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class Add : public Binary_operator {
  public:
    Add(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class Multiply : public Binary_operator {
  public:
    Multiply(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class Divide : public Binary_operator {
  public:
      Divide(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
      virtual const Constant* evaluate() const override;
      virtual gamelang::Type type() const override;
  };

class Mod : public Binary_operator {
  public:
      Mod(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
      virtual const Constant* evaluate() const override;
      virtual gamelang::Type type() const override;
  };

class Or : public Binary_operator {
  public:
      Or(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
      virtual const Constant* evaluate() const override;
      virtual gamelang::Type type() const override;
  };

class And : public Binary_operator {
  public:
    And(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const override;
    virtual gamelang::Type type() const override;
  };

  class LessThanOrEqual : public Binary_operator {
    public:
        LessThanOrEqual(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };

  class GreaterThanOrEqual : public Binary_operator {
    public:
        GreaterThanOrEqual(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };
  

  class LessThan : public Binary_operator {
    public:
        LessThan(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };
      
  class GreaterThan : public Binary_operator {
    public:
        GreaterThan(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };

  class Equal : public Binary_operator {
    public:
        Equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };
      
  class NotEqual : public Binary_operator {
    public:
        NotEqual(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };

  class Unary_operator : public Expression {
    protected:
        const Expression* expr;
        Unary_operator(const Expression* expr) : expr(expr) {}
        virtual ~Unary_operator() { delete expr; }
    };

  class Negation : public Unary_operator {
    public:
        Negation(const Expression* expr) : Unary_operator(expr) {}
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };

  class Not : public Unary_operator {
    public:
        Not(const Expression* expr) : Unary_operator(expr) {}
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };
  
  class Sin : public Unary_operator {
    public:
        Sin(const Expression* expr) : Unary_operator(expr) {}
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };

  class Cos : public Unary_operator {
    public:
        Cos(const Expression* expr) : Unary_operator(expr) {}
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };
      
  class Tan : public Unary_operator {
    public:
      Tan(const Expression* expr) : Unary_operator(expr) {}
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };

  class Asin : public Unary_operator {
    public:
        Asin(const Expression* expr) : Unary_operator(expr) {}
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };
      
  class Acos : public Unary_operator {
    public:
        Acos(const Expression* expr) : Unary_operator(expr) {}
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };
      
  class Atan : public Unary_operator {
    public:
        Atan(const Expression* expr) : Unary_operator(expr) {}
        virtual const Constant* evaluate() const override;
        virtual gamelang::Type type() const override;
    };

  class Sqrt : public Unary_operator {
      public:
        Sqrt(const Expression* expr) : Unary_operator(expr) {}
        const Constant* evaluate() const override;
        gamelang::Type type() const override;
  };

  class Abs : public Unary_operator {
    public:
        Abs(const Expression* expr) : Unary_operator(expr) {}
        const Constant* evaluate() const override;
        gamelang::Type type() const override;
  };

  class Floor : public Unary_operator {
    public:
        Floor(const Expression* expr) : Unary_operator(expr) {}
        const Constant* evaluate() const override;
        gamelang::Type type() const override;
  };

  class Random : public Unary_operator {
    public:
        Random(const Expression* expr) : Unary_operator(expr) {}
        const Constant* evaluate() const override;
        gamelang::Type type() const override;
  };

#endif
