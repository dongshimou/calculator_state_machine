//
// Created by skadi on 2018/2/12.
//

#ifndef CALCULATOR_CAL_HPP
#define CALCULATOR_CAL_HPP

#include <string>
#include <queue>
#include <iostream>
#include <functional>
#include "tokenzied.hpp"

enum class Operation{
    Add,
    Sub,
    Mul,
    Div,
};

template <Operation O,typename T>
auto opera(T&&a,T&&b){
    switch (O){
        case Operation::Add:
            return a+b;
        case Operation::Sub:
            return a-b;
        case Operation::Mul:
            return a*b;
        case Operation::Div:
            return a/b;
    }
};

auto cal(std::queue<token> expression){
     auto get_token=[&](){
        return expression.front();
    };
     auto get_next=[&](){
        expression.pop();
    };
     auto get_match=[&](std::string c){
        if(get_token().type==token::Symbol&&get_token().string()==c){
            get_next();
            return;
        }
        throw "match error";
    };

    std::function<double(void)>expr;
    std::function<double(double)>expr_tail;
    std::function<double(void)>factor;
    std::function<double(double)>term_tail;
    std::function<double(void)>term;
    factor=[&](){
        if(get_token().type==token::Symbol) {
            if (get_token().string() == "(") {
                get_match("(");
                auto value = expr();
                get_match(")");
                return value;
            }
        }else{
            auto token=get_token();
            if(token.type==token::Number){
                get_next();
                return token.number();
            }
        }
        throw "wan't number";
    };
    term_tail=[&](double&& lvalue){
        if(get_token().type==token::Symbol&&get_token().string()=="*"){
            get_next();
            return term_tail(opera<Operation::Mul>(std::forward<double>(lvalue),factor()));
        }else if(get_token().type==token::Symbol&&get_token().string()=="/"){
            get_next();
            return term_tail(opera<Operation::Div>(std::forward<double>(lvalue),factor()));
        }else{
            return std::forward<double>(lvalue);
        }
    };
    term=[&]() {
        return term_tail(factor());
    };
    expr_tail=[&](double&& lvalue){
        if(get_token().type==token::Symbol&&get_token().string()=="+"){
            get_next();
            return expr_tail(opera<Operation::Add>(std::forward<double>(lvalue),term()));
        }else if(get_token().type==token::Symbol&&get_token().string()=="-"){
            get_next();
            return expr_tail(opera<Operation::Sub>(std::forward<double>(lvalue),term()));
        }else{
            return std::forward<double>(lvalue);
        }
    };
    expr=[&](){
        return expr_tail(term());
    };

    return expr();
}

#endif //CALCULATOR_CAL_HPP
