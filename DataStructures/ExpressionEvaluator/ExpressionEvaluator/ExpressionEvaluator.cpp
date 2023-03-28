


#include <string>
#include <iostream>
#include <stack>
#include <stdlib.h>
#include <sstream>
#include <stdio.h>



using namespace std;

///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
string Infix2Postfix(string &s) {

	string r;
	stack<char> stack1;

	for (int i = 0; i < s.size(); i++)
	{

		if (s[i] == '+' || s[i] == '-')
		{
			if ((  r[r.size() - 1] >= '0'  &&   r[r.size() - 1] <= '9') || r[r.size() - 1] == '.')
				r += ' ';
			while (!stack1.empty())
			{
				if (stack1.top() == '(')
				{
					break;
				}
				r += stack1.top();
				r += ' ';
				stack1.pop();
			}
			stack1.push(s[i]);
		}
		else if (s[i] == '*' || s[i] == '/')
		{
			if ((r[r.size() - 1] >= '0'&& r[r.size() - 1] <= '9') || r[r.size() - 1] == '.')
				r += ' ';
			while (!stack1.empty()) {
				if (stack1.top() == '*' || stack1.top() == '/')
				{
					r += stack1.top();
					r += ' ';
					stack1.pop();
				}
				else
					break;
			}
			stack1.push(s[i]);
		}
		else if (s[i] == '(')
			stack1.push(s[i]);
		else if (s[i] == ')')
		{
			if ((r[r.size() - 1] >= '0'&& r[r.size() - 1] <= '9') || r[r.size() - 1] == '.')
				r += ' ';
			while (!stack1.empty()) {
				if (stack1.top() == '(')
				{
					stack1.pop();
					break;
				}
				r += stack1.top();
				r += ' ';
				stack1.pop();
			}
		}
		else
		{
			r += s[i];
		}

	}
	if ((r[r.size() - 1] >= '0'&& r[r.size() - 1] <= '9') || r[r.size() - 1] == '.')
		r += ' ';
	while (!stack1.empty())
	{
		r += stack1.top();
		r += ' ';
		stack1.pop();
	}
	
	string result;
	result = r;
	return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {

	stack<int> stack2;
	stringstream sstrm(s);
	string temp;
	int a, b;

	while (sstrm >> temp) {
		if (temp == "+")
		{
			a = stack2.top();
			stack2.pop();
			b = stack2.top();
			stack2.pop();
			stack2.push(a + b);
		}
		else if (temp == "-")
		{
			a = stack2.top();
			stack2.pop();
			b = stack2.top();
			stack2.pop();
			stack2.push(b - a);
		}
		else if (temp == "*")
		{
			a = stack2.top();
			stack2.pop();
			b = stack2.top();
			stack2.pop();
			stack2.push(a*b);
		}
		else if (temp == "/")
		{
			a = stack2.top();
			stack2.pop();
			b = stack2.top();
			stack2.pop();
			stack2.push(b / a);
		}
		else
		{
			stack2.push(atof(temp.c_str()));
		}
	}
	return stack2.top();
}
 // end-EvaluatePostfixExpression
