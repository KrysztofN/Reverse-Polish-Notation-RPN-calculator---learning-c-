#pragma once
#include <queue>
#include <stack>
#include <string>
#include <map>

class myCalc {
    std::string expr;
    double result;
    std::stack<double> numbers;
    double memory;  
    std::map<char, char> operatorReplacements;  
    std::map<std::string, std::string> numberReplacements; 
    
public:
    myCalc() : expr(""), result(0), memory(0) {
        operatorReplacements['+'] = '+';
        operatorReplacements['-'] = '-';
        operatorReplacements['*'] = '*';
        operatorReplacements['/'] = '/';
        operatorReplacements['s'] = 's';
        operatorReplacements['%'] = '%';
    }
    
    ~myCalc(){};
    
    void memoryAdd();     
    void memorySubtract(); 
    void memoryClear();    
    void memoryRecall();  
    double getMemory() const { return memory; }
    
    
    void setOperatorReplacement(char original, char replacement) {
        operatorReplacements[original] = replacement;
    }
    
    
    void setNumberReplacement(const std::string& original, const std::string& replacement) {
        numberReplacements[original] = replacement;
    }
    
    // Ot
    void greet(void);
    void insert_expr(void);
    int get_priority(char op);
    bool is_operator(char c);
    void calculate_expr(std::queue<std::string> rpn);
    std::queue<std::string> to_rp(void);
    void add_numbers();
    void substr_numbers();
    void mult_numbers();
    void div_numbers();
    void mod_numbers();
    void pow_numbers();
    void remove_spaces(void);
    void print_result(void);
    double getResult() const { return result; }
};
