#include <iostream>
#include "../headers/kalkulator.h"

	

int main(){
	
	myCalc calculator;
	calculator.greet(); 
	calculator.insert_expr();
	calculator.calculate_expr(calculator.to_rp());
	calculator.print_result(); 
	return 0;
}
