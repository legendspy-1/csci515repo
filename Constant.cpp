//File: Constant.cpp
#include "Constant.h"

gamelang::Type  Constant::type() const 
{ return intrinsic_type; }

const Constant*   Integer_constant::evaluate() const
{ return new Integer_constant(*this); }

const Constant*   Double_constant::evaluate() const
{ return new Double_constant(*this); }

const Constant*   String_constant::evaluate() const
{ return new String_constant(*this); }
