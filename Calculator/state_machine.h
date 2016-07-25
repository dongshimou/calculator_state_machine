#pragma once
#define _STATE_MACHINE_H_
#ifdef _STATE_MACHINE_H_

#include <string>
#include <queue>
#include <stack>
#include <iostream>
enum class state
{
	BEGIN,
	INTEGER,
	FLOAT,
	SYMBOL,
	LEFT,
	RIGHT,
	EQUAL,
	END
};
class state_machine
{
private:
	state now_state;
	std::string input;
	std::stack<char> brackets;
	bool is_equal;
	void left_bracket() { brackets.push('('); }
	bool right_bracket() { if (!brackets.empty()) { brackets.pop(); return true; } else return false; }
	void p_push(char *p, const char *ptr) { *p = *ptr, p++, *p = '\0'; }
	void p_pop(char *p, char *str) { expression.push(std::string(str)); p = str; }
public:
	state_machine(std::string str);
	state_machine(const char *str);
	bool check();
	void print();
protected:
	bool is_operation(char c) { return(c == '+' || c == '-' || c == '*' || c == '/'); }
	bool is_number(char c) { return (c >= '0'&&c <= '9'); }
	bool is_symbol(char c) { return (is_operation(c) || c == '(' || c == ')'); }
	std::queue<std::string>expression;
};

state_machine::state_machine(const char *str)
{
	input = std::string(str);
}
state_machine::state_machine(std::string str)
{
	input = str;
}
void state_machine::print()
{
	auto temp = expression;
	while (!temp.empty())
	{
		std::cout << temp.front() <<" ";
		temp.pop();
	}
	std::cout << std::endl;
}
bool state_machine::check()
{
	while (!expression.empty())
	{
		expression.pop();
	}
	const char *ptr = input.c_str();
	char *str = new char[input.length() + 1];
	is_equal = false;
	now_state = state::BEGIN;
	char *p = str;

	while (*ptr)
	{
		switch (now_state)
		{
		case state::BEGIN:
			if (is_number(*ptr))
			{
				p_push(p, ptr);
				now_state = state::INTEGER;
			}
			else if (is_operation(*ptr))
			{
				p_push(p, ptr);
				now_state = state::SYMBOL;
			}
			else if (*ptr == '(')
			{
				p_push(p, ptr);
				now_state = state::LEFT;
			}
			else
			{
				p_pop(p, str);
				ptr--;
				now_state = state::END;
			}
			break;
		case state::INTEGER:
			if (is_number(*ptr))
			{
				p_push(p, ptr);
				now_state = state::INTEGER;
			}
			else if (*ptr == '.')
			{
				p_push(p, ptr);
				now_state = state::FLOAT;
			}
			else if (*ptr == ')')
			{
				p_pop(p, str);
				ptr--;
				now_state = state::RIGHT;
			}
			else if (is_operation(*ptr))
			{
				p_pop(p, str);
				ptr--;
				now_state = state::BEGIN;
			}
			else if (*ptr == '=')
			{
				p_pop(p, str);
				ptr--;
				now_state = state::EQUAL;
			}
			else
			{
				p_pop(p, str);
				ptr--;
				now_state = state::END;
			}
			break;
		case state::FLOAT:
			if (is_number(*ptr))
			{
				p_push(p, ptr);
				now_state = state::FLOAT;
			}
			else if (is_operation(*ptr))
			{
				p_pop(p, str);
				ptr--;
				now_state = state::BEGIN;
			}
			else if (*ptr == ')')
			{
				p_pop(p, str);
				ptr--;
				now_state = state::RIGHT;
			}
			else if (*ptr == '=')
			{
				p_pop(p, str);
				ptr--;
				now_state = state::EQUAL;
			}
			else
			{
				p_pop(p, str);
				ptr--;
				now_state = state::END;
			}
			break;
		case state::SYMBOL:
			if (is_number(*ptr))
			{
				p_pop(p, str);
				ptr--;
				now_state = state::BEGIN;
			}
			else if (*ptr == '(')
			{
				p_pop(p, str);
				ptr--;
				now_state = state::LEFT;
			}
			else
			{
				p_pop(p, str);
				ptr--;
				now_state = state::END;
			}
			break;
		case state::LEFT:
			if (*ptr == '(')
			{
				left_bracket();
				p_push(p, ptr);
				p_pop(p, str);
				now_state = state::LEFT;
			}
			else if (is_number(*ptr))
			{
				p_push(p, ptr);
				now_state = state::INTEGER;
			}
			else
			{
				p_pop(p, str);
				ptr--;
				now_state = state::END;
			}
			break;
		case state::RIGHT:
			if (*ptr == ')')
			{
				if (!right_bracket())
				{
					delete str;
					return false;
				}
				p_push(p, ptr);
				p_pop(p, str);
				now_state = state::RIGHT;
			}
			else if (is_operation(*ptr))
			{
				p_push(p, ptr);
				now_state = state::SYMBOL;
			}
			else if(*ptr=='=')
			{
				ptr--;
				now_state = state::EQUAL;
			}
			else
			{
				ptr--;
				now_state = state::END;
			}
			break;
		case state::EQUAL:
			if (*ptr == '=' && !is_equal)
			{
				is_equal = true;
				now_state = state::EQUAL;
			}
			else
			{
				delete str;
				return false;
			}
			break;
		default:
			delete str;
			return false;
			break;
		}
		ptr++;
	}
	delete str;
	return true;
}

#endif // _STATE_MACHINE_H_