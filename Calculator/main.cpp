#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

#include "calculator.h"
#include "state_machine.h"

#include"tokenzied.hpp"
#include"cal.hpp"

using namespace std;


int main() {
    // 1+2*((2+3)*5)+(2-(3+5))=
    const char *str = "11+2*((2+3)*5)+(2-(3+5))=";
    printf("%s\n", str);

    token t;
    try {
        t.set<int>(1);
    } catch (...) {
        t.set<double>(2);
    }
    std::cout<<t.number()<<endl;

    cin.get();
//    calculator cal(str);
//    bool flag = cal.check();
//    cal.state_machine::print();
//    cal.do_suffix();
//    cal.print();
//
//    if (cal.solve())
//        cout << cal.get_answer() << endl;
}
