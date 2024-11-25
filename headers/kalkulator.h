#pragma once 
#include <queue>

class myCalc {
	
	std::string expr;

public:

	void greet(void);
	void insert_expr(void);
	int get_priority(char op);
	bool is_operator(char c); 
	double myCalc::calculate_expr(std::queue<std::string> rpn)
	std::queue<std::string> to_rp (void);
	void remove_spaces(void);
	myCalc() : expr("") {};
	~myCalc(){};
};
	
