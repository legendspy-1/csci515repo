#ifndef SCOPE_MANAGER_H
#define SCOPE_MANAGER_H

#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "symbol_table.h"

class Scope_manager {
public:
    Scope_manager(); 

    void push_table();
    void pop_table();
    bool add_to_current_scope(Symbol* sym);
    Symbol* lookup(const std::string& name);
    bool defined_in_current_scope(const std::string& name);

    friend std::ostream& operator<<(std::ostream& os, const Scope_manager& sm);

private:
    std::vector<std::unique_ptr<Symbol_table>> tables;
};

#endif