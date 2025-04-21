//File: Constant.h
#ifndef CONSTANT_H
#define CONSTANT_H
#include "Expression.h"
#include "types_and_ops.h"

class Constant : public Expression {
  public:
    Constant(gamelang::Type enum_name) : intrinsic_type(enum_name) {}
    virtual const Constant*   evaluate() const=0;
    virtual int         as_int()    const {throw intrinsic_type;}
    virtual double      as_double() const {throw intrinsic_type;}
    virtual std::string as_string() const {throw intrinsic_type;}
    virtual gamelang::Type   type()      const final;
  protected:
    Constant(const Constant&)=default;
  private:
    gamelang::Type intrinsic_type;
};

class Integer_constant : public Constant {
  public:
    Integer_constant(int d) : Constant(gamelang::INT), data(d) {}
    virtual int         as_int()    const { return data; }
    virtual double      as_double() const { return data; }
    virtual std::string as_string() const { return std::to_string(data);}
    virtual const Constant*   evaluate() const;
  private:
    Integer_constant(const Integer_constant&)=default;
    int data;
};

class Double_constant : public Constant {
  public:
    Double_constant(double d) : Constant(gamelang::DOUBLE), data(d) {}
    virtual double      as_double() const { return data; }
    virtual std::string as_string() const { return std::to_string(data);}
    virtual const Constant*   evaluate() const;
  private:
    Double_constant(const Double_constant&)=default;
    double data;
};

class String_constant : public Constant {
  public:
    String_constant(const std::string& d) : Constant(gamelang::STRING), data(d) {}
    virtual std::string as_string() const { return data;}
    virtual const Constant*   evaluate() const;
  private:
    String_constant(const String_constant&)=default;
    std::string data;
};

#endif
