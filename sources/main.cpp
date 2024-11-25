#include <iostream>
#include "../headers/kalkulator.h"

	

int main(){
	
	myCalc calculator;
	calculator.greet(); 
	calculator.insert_expr();
	float result = calculator.calculate_expr();
	return 0;
}
