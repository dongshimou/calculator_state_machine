#pragma once

#include<variant>
#include<string>
#include <queue>
class token {
public:
    enum Type {
        Number,
        Symbol,
    };
    Type type;
private:
    std::variant<double, std::string_view>value;
private:
    template <typename T>
    T get() {
        auto ptr = std::get_if<T>(&value);
        if (ptr == nullptr) {
            throw "get type error";
        }
        return *ptr;
    };
    template <typename V,auto T>
    void set(V&& v) {
        value=v;
        type=T;
    }
public:
    double number() {
        return get<double>();
    }
    std::string_view string() {
        return get<std::string_view>();
    }
    void set(double&& v){
        set<double,Number>(std::forward<double>(v));
    }
    void set(std::string_view&& v){
        set<std::string_view ,Symbol>(std::forward<std::string_view>(v));
    }
};

std::queue<token> tokenzied(const std::string& input){
    constexpr auto is_opera=[](int v){
        return v=='+'||v=='-'||v=='*'||v=='/';
    };
    constexpr auto is_number=[](int v){
        return v>='0'&&v<='9';
    };
    constexpr auto is_symbol=[](int v){
        return is_opera(v)||v=='('||v==')';
    };
    constexpr auto is_dot=[](int v){
        return v=='.';
    };
    constexpr auto is_space=[](int v){
        return isspace(v);
    };
    auto ptr_head=0;
    auto ptr_tail=ptr_head;
    std::queue<token>q;

    enum Status{
        Begin,
        Int,
        Float,
        Symbol,
        End,
        Error,
    };
    Status s=Begin;
    auto trim_space=[&](){
        while (ptr_head<input.size()){
            if(is_space(input[ptr_head])){
                ptr_head++;
                continue;
            }
            ptr_tail=ptr_head;
            return Begin;
        }
        return End;
    };
    auto push_token=[&](Status sss){
        token temp;
        auto sv=std::string_view(&input[ptr_tail],ptr_head-ptr_tail);
        if (sss==Int||sss==Float){
            temp.set(std::atof(sv.data()));
        }else if(sss==Symbol){
            temp.set(std::move(sv));
        }
        ptr_tail=ptr_head-1;
        q.push(std::move(temp));
    };
    auto is_begin=[&](){
        if (trim_space()==End){
            return End;
        }
        if(is_symbol(input[ptr_head])){
            return Symbol;
        } else if(is_number(input[ptr_head])){
            return Int;
        }
        return Error;
    };
    auto is_int=[&](){
        while (ptr_head<input.size()){
            if(isnumber(input[ptr_head])){
                ptr_head++;
                continue;
            }else if(is_dot(input[ptr_head])){
                ptr_head++;
                return Float;
            }else{
                push_token(Int);
                return Begin;
            }
        }
        push_token(Int);
        return End;
    };
    auto is_symbols=[&](){
        ptr_head++;
        push_token(Symbol);
        return Begin;
    };
    auto is_float=[&](){
        while (ptr_head<input.size()){
            if(isnumber(input[ptr_head])){
                ptr_head++;
                continue;
            }else{
                push_token(Float);
                return Begin;
            }
        }
        push_token(Float);
        return End;
    };

    while (true) {
        switch (s) {
            case Begin:
                s = is_begin();
                break;
            case Int:
                s = is_int();
                break;
            case Float:
                s=is_float();
                break;
            case Symbol:
                s=is_symbols();
                break;
            case End:
                return q;
            default:
                throw "tokenized error";
        }
    }
}