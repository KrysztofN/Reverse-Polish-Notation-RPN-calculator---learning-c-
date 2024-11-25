#include <iostream>
#include "../headers/kalkulator.h"
#include <string>
#include <cctype>
#include <algorithm>
#include <stack>
#include <queue>
#include <cmath>


void myCalc::greet(void){

	std::cout << R"(
    ___________________
   |  _________________  |      Witaj drogi użytkowniku !!!
   | |              0. | |	
   | |_________________| |	Przed tobą (nie)super kalkulator
   |  ___ ___ ___   ___  |
   | | 7 | 8 | 9 | | + | |	Miłego korzystania;)
   | |___|___|___| |___| |
   | | 4 | 5 | 6 | | - | |
   | |___|___|___| |___| |
   | | 1 | 2 | 3 | | x | |
   | |___|___|___| |___| |
   | | . | 0 | = | | / | |
   | |___|___|___| |___| |	Autor: Krzysztof Nowak WCY23IY2S1
   |_____________________|
    )" << std::endl;	
}

void myCalc::insert_expr(void){
	
	std::string expr;

	std::cout << "\n\nPodaj wyrażenie do obliczenia: \n";
	std::getline(std::cin, this->expr);
}

double myCalc::calculate_expr(std::queue<std::string> rpn) {

	std::cout<< "\nObliczam wyrazenie: " << this->expr << std::endl; 
	
	std::queue<std::string> rpn = myCalc::to_rp();
	std::stack<double> numbers;

	while(!rpn.empty()){
		std::string token = rpn.front();
		rpn.pop();

		if(token.length() == 1 && is_operator(token[0])){
			double b = numbers.top(); numbers.pop();
			double a = numbers.top(); numbers.pop();

			switch(token[0]){
				case '+': numbers.push(a + b); break;
				case '-': numbers.push(a - b); break;
				case '*': numbers.push(a * b); break;
				case '/': 
					if(b == 0) {
						std::cout << "Error: Division by zero!!!" << std::endl;
						return 0;
					}
					numbers.push(a / b); 
					break;
				case '^': numbers.push(a ^ b); break;
				case 'p': numbers.push(std::pow(a,b)); break;
				case '%': numbers.push(std::fmod(a,b)); break;
			}
		}
		
		else{
			numbers.push(stod(token));
		}
	}


	return numbers.empty() ? 0 : numbers.top();
}

void myCalc::remove_spaces(void){
	expr.erase(remove_if(expr.begin(), expr.end(), ::isspace), expr.end());
}

// priorytet operandów
int myCalc::get_priority(char op){
	if(op == '+' || op == '-') return 1;	
	if(op == '*' || op == '/') return 2;	
	if(op == 'p' || op == '%' || op == '^') return 3;

	// jezeli nie znaleziono
	return 0;
}

bool myCalc::is_operator(char c){
	return (c == '-' || c == '+' || c == 'p' || c == '/' || c == '*' || c == '^' || c == '%');
}

// Konwersja wyrazenia na odwrotna notacje polska
std::queue<std::string> myCalc::to_rp (void){
	std::queue<std::string> output;
	std::stack<char> operators;
	std::string number;

	// usuwanie wszystkich spacji z wyrażenia
	myCalc::remove_spaces();
	for(auto i = 0u; i < expr.length(); i++){

		// napotkalismy liczbę
		if(isdigit(expr[i])){
			number = "";
			while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')){
				number += expr[i];
				i++;
			}
			i--;
			output.push(number);
		}

		// napotkaliśmy operand
		else if (myCalc::is_operator(expr[i])){
			while(!operators.empty() && myCalc::get_priority(operators.top()) >= myCalc::get_priority(expr[i])){
				std::string op(1, operators.top());
				output.push(op);
				operators.pop();
			}
			operators.push(expr[i]);
		}

		// nawias otwierający
		else if(expr[i] == '(') operators.push(expr[i]);

		// nawias zamykający
		else if (expr[i] == ')'){
			while(!operators.empty() && operators.top() != '('){
				std::string op(1, operators.top());
				output.push(op);
				operators.pop();
			}

			if(!operators.empty()){
				operators.pop();
			}
		}
	}

	while (!operators.empty()){
		std::string op(1, operators.top());
		output.push(op);
		operators.pop();
	}

	return output;
}










