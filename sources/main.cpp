#include "../headers/kalkulator.h"
#include <iostream>

int main() {
    myCalc calc;
    calc.greet();
    
    while(true) {
        calc.insert_expr();
        std::queue<std::string> rpn = calc.to_rp();
        calc.calculate_expr(rpn);
        calc.print_result();
    }
    
    return 0;
}