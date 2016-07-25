#pragma once
#define _CALCULATOR_H_
#ifdef _CALCULATOR_H_
#include "state_machine.h"
#define eps 1e-8
class calculator:public state_machine
{
private:
	double answer;
	std::queue<std::string>suffix;
	std::stack<char>symbol;
	double operation(double & a,char c,double b);
	int symbol_priority(char c)
	{
		if (c == '(')return 0;
		else if (c == '+' || c == '-')return 1;
		else if (c == '*' || c == '/')return 2;
		else if (c == ')')return 3;
		else return -1;
	}
	bool is_high(char c)
	{
		if (symbol.empty())return true;
		else if (c == '(')return true;
		else if (symbol_priority(symbol.top())<symbol_priority(c))return true;
		else return false;
	}
public:
	calculator(std::string str)
		:state_machine(str){}
	calculator(const char* str)
		:state_machine(str){}
	double get_answer() { return answer; }
	void do_suffix();
	bool count();
	bool solve()
	{
		if (!check())
			return false;
		do_suffix();
		return count();
	}
	void print()
	{
		auto temp = suffix;
		while (!temp.empty())
		{
			std::cout << temp.front();
			temp.pop();
		}
		std::cout << std::endl;
	}
};
double calculator::operation(double & a, char c, double b)
{
	if (c == '+')a += b;
	else if (c == '-')a -= b;
	else if (c == '*')a *= b;
	else if (c == '/')
	{
		if (abs(b) <= eps)return false;
		else return a /= b;
	}
	else return false;
	return true;
}
void calculator::do_suffix()
{
	while (!expression.empty())
	{
		std::string str = expression.front();
		expression.pop();
		if (is_symbol(str[0]))
		{
			if (is_high(str[0]))
			{
				if (str[0] == ')')
				{
					while (symbol.top() != '(')
					{
						std::string temp = "";
						suffix.push(temp+=symbol.top());
						symbol.pop();
					}
					symbol.pop();
				}
				else
					symbol.push(str[0]);
			}
			else
			{
				while (!symbol.empty())
				{
					if (is_high(str[0]))
					{
						break;
					}
					std::string temp = "";
					suffix.push(temp += symbol.top());
					symbol.pop();
				}
			}
		}
		else
		{
			suffix.push(str);
		}
	}
	while (!symbol.empty())
	{
		std::string temp = "";
		suffix.push(temp += symbol.top());
		symbol.pop();
	}
}
bool calculator::count()
{
	std::stack<double>number;
	while (!suffix.empty())
	{
		std::string temp = suffix.front();
		suffix.pop();
		if (!is_symbol(temp[0]))
		{
			number.push(atof(temp.c_str()));
		}
		else
		{
			double temp1 = number.top(); number.pop();
			double temp2 = number.top(); number.pop();
			if (!operation(temp2,temp[0],temp1))
			{
				return false;
			}
			else
			{
				number.push(temp2);
			}
		}
	}
	answer = number.top();
	number.pop();
	return true;
}
#endif // _CALCULATOR_H_