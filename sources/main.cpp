#include <iostream>
#include "../headers/kalkulator.h"

	

int main(){
	
	myCalc calculator;
	calculator.greet();

	bool continue_calc = true;
	while(continue_calc) {

		calculator.insert_expr();
		calculator.calculate_expr(calculator.to_rp());
		calculator.print_result();
		continue_calc = calculator.ask_continue();
	}
	return 0;
}
