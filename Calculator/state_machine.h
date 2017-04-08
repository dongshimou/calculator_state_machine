#pragma once
#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <cstring>

class state_machine
{
    enum class state
    {
        BEGIN,
        INTEGER,
        FLOAT,
        SYMBOL,
        LEFT,
        RIGHT,
        EQUAL,
        END
    };
    ///todo
    /*
     * parse to tokens
     */
private:
    state now_state = state::BEGIN;
    std::string input;
    std::stack<char> brackets;
    bool is_equal = false;
    void left_bracket() { brackets.push('('); }
    bool right_bracket()
    {
        if (!brackets.empty()) {
            brackets.pop();
            return true;
        }
        else
            return false;
    }
public:
    state_machine(std::string str);
    state_machine(const char* str);
    bool check();
    void print() const;

protected:
    static bool is_operation(char c)
    {
        return ( c == '+' || c == '-' || c == '*' || c == '/' );
    }
    static bool is_number(char c) { return ( c >= '0' && c <= '9' ); }
    static bool is_symbol(char c) { return ( is_operation(c) || c == '(' || c == ')' ); }
    std::queue<std::string> expression;
};

inline state_machine::state_machine(const char* str)
{
    input = std::string(str);
}

inline state_machine::state_machine(std::string str)
{
    input = str;
}

inline void state_machine::print() const
{
    auto temp = expression;
    while (!temp.empty()) {
        std::cout << temp.front() << " ";
        temp.pop();
    }
    std::cout << std::endl;
}
bool state_machine::check()
{
    now_state = state::BEGIN;
    is_equal = false;
    while (!expression.empty()) {
        expression.pop();
    }
    const char* ptr = input.c_str();
    char* str = new char[input.length() + 1];
    memset(str, 0, sizeof(str));
    char* p = str;
    auto p_push = [&p, &ptr]() {
        *p = *ptr, p++, *p = '\0';
    };
    auto p_pop = [&p, &str, this] {
        expression.push(std::string(str));
        p = str;
    };
    while (*ptr) {
        switch (now_state) {
        case state::BEGIN:
            if (is_number(*ptr)) {
                p_push();
                now_state = state::INTEGER;
            }
            else if (is_operation(*ptr)) {
                p_push();
                now_state = state::SYMBOL;
            }
            else if (*ptr == '(') {
                p_push();
                now_state = state::LEFT;
            }
            else {
                p_pop();
                ptr--;
                now_state = state::END;
            }
            break;
        case state::INTEGER:
            if (is_number(*ptr)) {
                p_push();
                now_state = state::INTEGER;
            }
            else if (*ptr == '.') {
                p_push();
                now_state = state::FLOAT;
            }
            else if (*ptr == ')') {
                p_pop();
                ptr--;
                now_state = state::RIGHT;
            }
            else if (is_operation(*ptr)) {
                p_pop();
                ptr--;
                now_state = state::BEGIN;
            }
            else if (*ptr == '=') {
                p_pop();
                ptr--;
                now_state = state::EQUAL;
            }
            else {
                p_pop();
                ptr--;
                now_state = state::END;
            }
            break;
        case state::FLOAT:
            if (is_number(*ptr)) {
                p_push();
                now_state = state::FLOAT;
            }
            else if (is_operation(*ptr)) {
                p_pop();
                ptr--;
                now_state = state::BEGIN;
            }
            else if (*ptr == ')') {
                p_pop();
                ptr--;
                now_state = state::RIGHT;
            }
            else if (*ptr == '=') {
                p_pop();
                ptr--;
                now_state = state::EQUAL;
            }
            else {
                p_pop();
                ptr--;
                now_state = state::END;
            }
            break;
        case state::SYMBOL:
            if (is_number(*ptr)) {
                p_pop();
                ptr--;
                now_state = state::BEGIN;
            }
            else if (*ptr == '(') {
                p_pop();
                ptr--;
                now_state = state::LEFT;
            }
            else {
                p_pop();
                ptr--;
                now_state = state::END;
            }
            break;
        case state::LEFT:
            if (*ptr == '(') {
                left_bracket();
                p_push();
                p_pop();
                now_state = state::LEFT;
            }
            else if (is_number(*ptr)) {
                p_push();
                now_state = state::INTEGER;
            }
            else {
                p_pop();
                ptr--;
                now_state = state::END;
            }
            break;
        case state::RIGHT:
            if (*ptr == ')') {
                if (!right_bracket()) {
                    delete[] str;
                    return false;
                }
                p_push();
                p_pop();
                now_state = state::RIGHT;
            }
            else if (is_operation(*ptr)) {
                p_push();
                now_state = state::SYMBOL;
            }
            else if (*ptr == '=') {
                ptr--;
                now_state = state::EQUAL;
            }
            else {
                ptr--;
                now_state = state::END;
            }
            break;
        case state::EQUAL:
            if (*ptr == '=' && !is_equal) {
                is_equal = true;
                now_state = state::EQUAL;
            }
            else {
                delete[] str;
                return false;
            }
            break;
        default:
            delete[] str;
            return false;
        }
        ptr++;
    }
    delete[] str;
    return true;
}

#endif // _STATE_MACHINE_H_
