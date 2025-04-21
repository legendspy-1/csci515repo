#include "symbol.h"
#include <cassert>

Symbol::Symbol(const std::string& name, double* val) : name(name), type(gamelang::DOUBLE), count(1) {
    value.double_pointer = val;
}

Symbol::Symbol(const std::string& name, double* array, int count) : name(name), type(gamelang::DOUBLE), count(count) {
    value.double_pointer = array;
}

Symbol::Symbol(const std::string& name, int* val) : name(name), type(gamelang::INT), count(1) {
    value.int_pointer = val;
}

Symbol::Symbol(const std::string& name, int* array, int count) : name(name), type(gamelang::INT), count(count) {
    value.int_pointer = array;
}

Symbol::Symbol(const std::string& name, std::string* val) : name(name), type(gamelang::STRING), count(1) {
    value.string_pointer = val;
}

Symbol::Symbol(const std::string& name, std::string* array, int count) : name(name), type(gamelang::STRING), count(count) {
    value.string_pointer = array;
}

Symbol::~Symbol() {
    if (count <= 0) return;  
    
    switch (type) {
        case gamelang::DOUBLE:
            if (value.double_pointer) {
                count > 1 ? delete[] value.double_pointer : delete value.double_pointer;
                value.double_pointer = nullptr;  
            }
            break;
        case gamelang::INT:
        if (value.int_pointer) {
            count > 1 ? delete[] value.int_pointer : delete value.int_pointer;
            value.int_pointer = nullptr;  
        }
        break;
        case gamelang::STRING:
        if (value.string_pointer) {
            count > 1 ? delete[] value.string_pointer : delete value.string_pointer;
            value.string_pointer = nullptr;  
        }
        break;
        default:
            assert(false);
    }
}

std::ostream& operator<<(std::ostream& os, const Symbol& sym) {
    auto print_type = [&os, &sym]() {
        switch(sym.type) {
            case gamelang::INT:
                os << "int";
                break;
            case gamelang::DOUBLE:
                os << "double";
                break;
            case gamelang::STRING:
                os << "string";
                break;
            default:
                assert(false);
                break;
        }
    };
    // For a scalar symbol
    if (sym.count == 1) {
        print_type();
        os << " " << sym.name << " = ";
        switch(sym.type) {
            case gamelang::INT:
                os << *sym.value.int_pointer;
                break;
            case gamelang::DOUBLE:
                os << *sym.value.double_pointer;
                break;
            case gamelang::STRING:
                os << "\"" << *sym.value.string_pointer << "\"";
                break;
            default:
                assert(false); // Unexpected type
        }
    }
    // For array 
    else {
        for (int i = 0; i < sym.count; ++i) {
            print_type();
            os << " " << sym.name << "[" << i << "] = ";
            switch(sym.type) {
                case gamelang::INT:
                    os << sym.value.int_pointer[i];
                    break;
                case gamelang::DOUBLE:
                    os << sym.value.double_pointer[i];
                    break;
                case gamelang::STRING:
                    os << "\"" << sym.value.string_pointer[i] << "\"";
                    break;
                default:
                    assert(false);
            }
            if (i < sym.count - 1)
                os << std::endl;
        }
    }
    return os;
}

const Constant* Symbol::as_constant() const {
    if (count != 1) return nullptr;

    switch (type) {
        case gamelang::INT:
            return new Integer_constant(*value.int_pointer);
        case gamelang::DOUBLE:
            return new Double_constant(*value.double_pointer);
        case gamelang::STRING:
            return new String_constant(*value.string_pointer);
        default:
            throw type; // New types like RECTANGLE will trigger this
    }
}

const Constant* Symbol::as_constant(int index) const {
    if (index < 0 || index >= count) return nullptr;

    switch (type) {
        case gamelang::INT:
            return new Integer_constant(value.int_pointer[index]);
        case gamelang::DOUBLE:
            return new Double_constant(value.double_pointer[index]);
        case gamelang::STRING:
            return new String_constant(value.string_pointer[index]);
        default:
            throw type;
    }
}