#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <memory>
#include "types_and_ops.h"
#include "Constant.h"

class Symbol {
private:
    std::string name;
    gamelang::Type type;
    int count;
    
    union symbol_type {
        double* double_pointer;
        int* int_pointer;
        std::string* string_pointer;

        symbol_type(double* val) : double_pointer(val) {}
        symbol_type(int* val) : int_pointer(val) {}
        symbol_type(std::string* val) : string_pointer(val) {}
        symbol_type() : double_pointer(nullptr) {}
    } value;

public:
    Symbol(const std::string& name, double* value);
    Symbol(const std::string& name, double* value, int count);
    Symbol(const std::string& name, int* value);
    Symbol(const std::string& name, int* value, int count);
    Symbol(const std::string& name, std::string* value);
    Symbol(const std::string& name, std::string* value, int count);
    ~Symbol();

    gamelang::Type get_type() const { return type; }
    std::string get_name() const { return name; }
    int get_count() const { return count; }

    const Constant* as_constant() const;
    const Constant* as_constant(int index) const;

    friend std::ostream& operator<<(std::ostream& os, const Symbol& sym);
    
    Symbol(const Symbol&) = delete;
    Symbol& operator=(const Symbol&) = delete;
    bool is_valid() const {
        if (count <= 0) return false;
        switch(type) {
            case gamelang::DOUBLE: return value.double_pointer != nullptr;
            case gamelang::INT: return value.int_pointer != nullptr;
            case gamelang::STRING: return value.string_pointer != nullptr;
            default: return false;
        }
    }
};

#endif