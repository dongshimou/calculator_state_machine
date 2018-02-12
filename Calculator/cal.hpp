//
// Created by skadi on 2018/2/12.
//

#ifndef CALCULATOR_CAL_HPP
#define CALCULATOR_CAL_HPP

#include "state_machine.h"

#include <string>
#include <queue>
#include <iostream>
#include <functional>
#include "tokenzied.hpp"
auto cal(std::queue<token> expression){
    auto token=[&](){
        return expression.front();
    };
    auto next=[&](){
        expression.pop();
    };
    auto match=[&](std::string c){
        if(token().string()==c){
            next();
        }
        std::cout<<" wan't "<<c<<" but "<<token().string()<<std::endl;
    };

    std::function<double(void)>expr;
    auto factor=[&](){
        if(token().string()=="("){
            match("(");
            auto value=expr();
            match(")");
        }else{
            auto value=token().number();
        }
    };
}

#endif //CALCULATOR_CAL_HPP
