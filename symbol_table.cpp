#include "symbol_table.h"
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <sstream>

Symbol* Symbol_table::lookup(const std::string& name) {
    auto it = symbols.find(name);
    return (it != symbols.end()) ? it->second.get() : nullptr;
}

bool Symbol_table::insert(Symbol* sym) {
    if (!sym || symbols.find(sym->get_name()) != symbols.end()) {
        return false;
    }
    symbols[sym->get_name()] = std::unique_ptr<Symbol>(sym);
    return true;
}

std::ostream& operator<<(std::ostream& os, const Symbol_table& symtab) {
    std::vector<std::string> names;
    for (const auto& pair : symtab.symbols) {
        names.push_back(pair.first);
    }
    std::sort(names.begin(), names.end());

    for (const std::string& name : names) {
        const Symbol* sym = symtab.symbols.at(name).get();
        os << *sym << std::endl;
    }

    return os;
}