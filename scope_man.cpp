#include "scope_man.h"
#include <sstream>

Scope_manager::Scope_manager() {
    tables.push_back(std::make_unique<Symbol_table>());
}

// Push a new symbol table (new scope)
void Scope_manager::push_table() {
    tables.push_back(std::make_unique<Symbol_table>());
}

void Scope_manager::pop_table() {
    if (tables.size() > 1) {
        tables.pop_back();
    } else {
        throw std::underflow_error("Can't pop global symbol table");
    }
}

bool Scope_manager::add_to_current_scope(Symbol* sym) {
    return tables.back()->insert(sym);
}

Symbol* Scope_manager::lookup(const std::string& name) {
    for (auto it = tables.rbegin(); it != tables.rend(); ++it) {
        Symbol* sym = (*it)->lookup(name);
        if (sym) {
            return sym;
        }
    }
    return nullptr;
}

bool Scope_manager::defined_in_current_scope(const std::string& name) {
    return tables.back()->lookup(name) != nullptr;
}

std::ostream& operator<<(std::ostream& os, const Scope_manager& sm) {
    for (auto it = sm.tables.rbegin(); it != sm.tables.rend(); ++it) {
        os << **it;
    }
    return os;
}