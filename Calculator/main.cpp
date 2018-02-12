#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

#include "calculator.h"
#include "state_machine.h"
using namespace std;


int main() {
    // 1+2*((2+3)*5)+(2-(3+5))=
    char *str = "11+2*((2+3)*5)+(2-(3+5))=";
    printf("%s\n", str);

    state_machine::token t;

    t.set<double>(2);

    std::cout<<t.number()<<endl;

//    calculator cal(str);
//    bool flag = cal.check();
//    cal.state_machine::print();
//    cal.do_suffix();
//    cal.print();
//
//    if (cal.solve())
//        cout << cal.get_answer() << endl;
}
