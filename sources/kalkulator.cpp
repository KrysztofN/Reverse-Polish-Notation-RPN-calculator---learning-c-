#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <algorithm>
#include <stack>
#include <queue>
#include <cmath>
#include "../headers/kalkulator.h"

void myCalc::greet(void) {
    std::cout << R"(
    ___________________
   |  _________________  |      Witaj drogi użytkowniku !!!
   | |              0. | |	
   | |_________________| |	Przed tobą (nie)super kalkulator
   |  ___ ___ ___   ___  |
   | | 7 | 8 | 9 | | + | |	Miłego korzystania;)
   | |___|___|___| |___| |
   | | 4 | 5 | 6 | | - | |     Opcje pamięci:
   | |___|___|___| |___| |     M+ (dodaj do pamięci)
   | | 1 | 2 | 3 | | x | |     M- (odejmij od pamięci)
   | |___|___|___| |___| |     MC (wyczyść pamięć)
   | | . | 0 | = | | / | |     MR (przywołaj z pamięci)
   | |___|___|___| |___| |	
   |_____________________|     Autor: Krzysztof Nowak WCY23IY2S1
    )" << std::endl;	
}

void myCalc::insert_expr(void) {
    std::cout << "\n\nWyjdź (E)";
    std::cout << "\nWyczyść kalkulator (C)";
    std::cout << "\nOperacje pamięci:";
    std::cout << "\n  M+ (dodaj do pamięci)";
    std::cout << "\n  M- (odejmij od pamięci)";
    std::cout << "\n  MC (wyczyść pamięć)";
    std::cout << "\n  MR (przywołaj z pamięci)";
    std::cout << "\nPodaj wyrażenie do obliczenia: ";
    std::getline(std::cin, expr);

    if(expr == "E" || expr == "e") {
        std::cout << "\nDziekuję za skorzystanie z kalkulatora!\n";
        exit(0);
    }
    // Handle memory operations
    else if(expr == "M+") {
        memoryAdd();
        return;
    }
    else if(expr == "M-") {
        memorySubtract();
        return;
    }
    else if(expr == "MC") {
        memoryClear();
        return;
    }
    else if(expr == "MR") {
        memoryRecall();
        return;
    }
    else if(expr == "C" || expr == "c") {
        result = 0;
        memory = 0;
        std::cout << "Kalkulator wyczyszczony!\n";
        return;
    }
    
    // Apply number replacements
    for(const auto& replacement : numberReplacements) {
        size_t pos = 0;
        while((pos = expr.find(replacement.first, pos)) != std::string::npos) {
            expr.replace(pos, replacement.first.length(), replacement.second);
            pos += replacement.second.length();
        }
    }
    
    // Apply operator replacements
    for(size_t i = 0; i < expr.length(); i++) {
        if(is_operator(expr[i])) {
            auto it = operatorReplacements.find(expr[i]);
            if(it != operatorReplacements.end()) {
                expr[i] = it->second;
            }
        }
    }
}

void myCalc::calculate_expr(std::queue<std::string> rpn) {
    std::cout << "\nObliczam wyrazenie: " << this->expr << std::endl; 

    while(!rpn.empty()) {
        std::string token = rpn.front();
        rpn.pop();

        if(token.length() == 1 && is_operator(token[0])) {
            // Check if we have enough numbers in stack
            if(numbers.size() < 2 && token[0] != 's') {  // 's' is square and needs only one number
                std::cout << "Error: Nieprawidłowa składnia wyrażenia!" << std::endl;
                return;
            }

            switch(token[0]) {
                case '+': add_numbers(); break;
                case '-': substr_numbers(); break;
                case '*': mult_numbers(); break;
                case '/': div_numbers(); break;
                case 's': pow_numbers(); break;
                case '%': mod_numbers(); break;
            }
        } else {
            try {
                numbers.push(stod(token));
            } catch (const std::invalid_argument& e) {
                std::cout << "Error: Nieprawidłowa liczba w wyrażeniu!" << std::endl;
                return;
            }
        }
    }

    this->result = numbers.empty() ? 0 : numbers.top();
    numbers = std::stack<double>();  // Clear the stack for next calculation
}

void myCalc::add_numbers(void) {
    if(numbers.size() >= 2) {
        double b = numbers.top(); numbers.pop();
        double a = numbers.top(); numbers.pop();
        numbers.push(a + b);
    }
}

void myCalc::substr_numbers(void) {
    if(numbers.size() >= 2) {
        double b = numbers.top(); numbers.pop();
        double a = numbers.top(); numbers.pop();
        numbers.push(a - b);
    }
}

void myCalc::mult_numbers(void) {
    if(numbers.size() >= 2) {
        double b = numbers.top(); numbers.pop();
        double a = numbers.top(); numbers.pop();
        numbers.push(a * b);
    }
}

void myCalc::div_numbers(void) {
    if(numbers.size() >= 2) {
        double b = numbers.top(); numbers.pop();
        double a = numbers.top(); numbers.pop();
        if(b == 0) {
            std::cout << "Error: Dzielenie przez zero!!!" << std::endl;
            numbers.push(a);  // Put back the number
            return;
        }
        numbers.push(a / b);
    }
}

void myCalc::pow_numbers() {
    if(!numbers.empty()) {
        double a = numbers.top(); numbers.pop();
        numbers.push(std::pow(a, 2));
    }
}

void myCalc::mod_numbers() {
    if(numbers.size() >= 2) {
        double b = numbers.top(); numbers.pop();
        double a = numbers.top(); numbers.pop();
        if(b == 0) {
            std::cout << "Error: Modulo przez zero!!!" << std::endl;
            numbers.push(a);  // Put back the number
            return;
        }
        numbers.push(std::fmod(a, b));
    }
}

void myCalc::remove_spaces(void) {
    expr.erase(remove_if(expr.begin(), expr.end(), ::isspace), expr.end());
}

int myCalc::get_priority(char op) {
    switch(op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case 's': case '%': return 3;
        default: return 0;
    }
}

bool myCalc::is_operator(char c) {
    return (c == '-' || c == '+' || c == 's' || c == '/' || c == '*' || c == '%');
}

std::queue<std::string> myCalc::to_rp(void) {
    std::queue<std::string> output;
    std::stack<char> operators;
    std::string number;

    remove_spaces();

    // Handle memory operations before conversion
    if(expr == "MR") {
        output.push(std::to_string(memory));
        return output;
    }

    for(auto i = 0u; i < expr.length(); i++) {
        if(isdigit(expr[i]) || (expr[i] == '-' && (i == 0 || expr[i-1] == '('))) {
            number = "";
            if(expr[i] == '-') {
                number += '-';
                i++;
            }
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                number += expr[i];
                i++;
            }
            i--;
            output.push(number);
        }
        else if (is_operator(expr[i])) {
            while(!operators.empty() && operators.top() != '(' && 
                  get_priority(operators.top()) >= get_priority(expr[i])) {
                std::string op(1, operators.top());
                output.push(op);
                operators.pop();
            }
            operators.push(expr[i]);
        }
        else if(expr[i] == '(') {
            operators.push(expr[i]);
        }
        else if(expr[i] == ')') {
            while(!operators.empty() && operators.top() != '(') {
                std::string op(1, operators.top());
                output.push(op);
                operators.pop();
            }
            if(!operators.empty()) operators.pop();  // Remove '('
        }
    }

    while(!operators.empty()) {
        if(operators.top() != '(') {
            std::string op(1, operators.top());
            output.push(op);
        }
        operators.pop();
    }

    return output;
}

void myCalc::print_result(void) {
    std::cout << std::fixed;
    std::cout << std::setprecision(6);
    std::cout << "\nWynik działania: " << this->result << std::endl;
    if(memory != 0) {
        std::cout << "Wartość w pamięci: " << this->memory << std::endl;
    }
}

// Memory operations implementation
void myCalc::memoryAdd() {
    memory += result;
    std::cout << "Dodano do pamięci. Aktualna wartość: " << memory << std::endl;
}

void myCalc::memorySubtract() {
    memory -= result;
    std::cout << "Odjęto od pamięci. Aktualna wartość: " << memory << std::endl;
}

void myCalc::memoryClear() {
    memory = 0;
    std::cout << "Pamięć wyczyszczona" << std::endl;
}

void myCalc::memoryRecall() {
    result = memory;
    std::cout << "Przywołano z pamięci: " << memory << std::endl;
}