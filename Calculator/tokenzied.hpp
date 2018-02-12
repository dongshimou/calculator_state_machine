#pragma once

#include<variant>
#include<string>
class token {
public:
    enum Type {
        Number,
        Symbol,
    };
    Type type;
private:
    std::variant<double, std::string>value;
private:
    template <typename T>
    T get() {
        auto ptr = std::get_if<T>(&value);
        if (ptr == nullptr) {
            throw "get type error";
        }
        return *ptr;
    };
public:
    double number() {
        return get<double>();
    }
    std::string string() {
        return get<std::string>();
    }
    template <typename T>
    void set(T&& v) {
        if (std::is_same<double, T>::value) {
            type = Number;
        } else if (std::is_same<std::string, T>::value) {
            type = Symbol;
        } else {
            throw "set type error";
        }
        value = v;
    }
};
