#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <queue>
#include "calculator.h"
#include "state_machine.h"

#include"tokenzied.hpp"
#include"cal.hpp"

using namespace std;


int main() {

    string str = string("11.1+2*((2+3)*5)+(2-(3+5))");
    cout<<str<<endl;

    //后缀表达式
    calculator ccc(str);
    bool flag = ccc.check();
    ccc.state_machine::print();
    ccc.do_suffix();
    ccc.print();
    if (ccc.solve())
        cout << ccc.get_answer() << endl;


    //递归下降
    queue<token> tokens;
    try {
        tokens =tokenzied(str);
        auto v=cal(tokens);
        cout<<v<<endl;
    }catch (const char* t){
        std::cout<<t;
    }


    cin.get();

}
