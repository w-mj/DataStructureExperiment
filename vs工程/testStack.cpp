#include "Stack.h"
#include "Queue.h"
#include "split.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <sstream>
using namespace std;

string hexadecimalConversion(string x, int m,int n) {
	string result = "", raw;
	stringstream ss;
	Stack<char> s;
	int dec = 0, i = 0;
	ss << x;
	ss >> raw;
	for (string::iterator iter = raw.begin(); iter != raw.end() && isalnum(*iter); iter++) {
		int nn = isdigit(*iter) ? *iter - '0' : *iter - 'A' + 10;
		dec = dec * m + nn;
	}
	while (dec != 0) {
		int o = dec % n;
		s.push(o < 10? o + '0': o + 'A' - 10);
		dec = dec / n;
	}
	while (!s.empty()) {
		result += s.pop();
	}
	return result;
}

bool parenthesesMatching(string line) {
	Stack<char> s;
	for (string::iterator iter = line.begin(); iter != line.end(); iter++) {
		char c = *iter;
		if (c == '(' || c == '[' || c == '{')
			s.push(c);
		if (c == ')')
			if (s.size() == 0 || s.pop() != '(') return false;
		if (c == ']')
			if (s.size() == 0 || s.pop() != '[') return false;
		if (c == '}')
			if (s.size() == 0 || s.pop() != '{') return false;
	}
	return true;
}

int getIndex(char theta)   
{
	int index = 0;
	switch (theta)
	{
	case '+':
		index = 0;
		break;
	case '-':
		index = 1;
		break;
	case '*':
		index = 2;
		break;
	case '/':
		index = 3;
		break;
	case '(':
		index = 4;
		break;
	case ')':
		index = 5;
		break;
	case '#':
		index = 6;
	default:break;
	}
	return index;
}
char getPriority(char theta1, char theta2)     
{
	const char priority[][7] =   
	{
		{ '>','>','<','<','<','>','>' },
		{ '>','>','<','<','<','>','>' },
		{ '>','>','>','>','<','>','>' },
		{ '>','>','>','>','<','>','>' },
		{ '<','<','<','<','<','=','0' },
		{ '>','>','>','>','0','>','>' },
		{ '<','<','<','<','<','0','=' },
	};

	int index1 = getIndex(theta1);
	int index2 = getIndex(theta2);
	return priority[index1][index2];
}
double calculate(double b, char theta, double a)   //计算b theta a  
{
	switch (theta)
	{
	case '+':
		return b + a;
	case '-':
		return b - a;
	case '*':
		return b * a;
	case '/':
		return b / a;
	default:
		return 0;
	}
}

double getAns(string line) {
	vector<double> nums = splitd(line);
	line += "#";
	string::iterator iter = line.begin();
	Stack<double> numStack;
	Stack<char> optStack;
	int i = 0;
	optStack.push('#');
	while (*iter != '#' || optStack.size() != 1) {
		if (iter != line.end() && (isdigit(*iter) || *iter == '.')) {
			numStack.push(nums[i++]);
			while (iter != line.end() && (isdigit(*iter) || *iter == '.'))
				iter++;
		}
		else {
			switch (getPriority(optStack.top(), *iter))   
			{
			case '<':             
				optStack.push(*iter);
				iter++;
				break;
			case '=':              
				optStack.pop();
				iter++;
				break;
			case '>':              
				char theta = optStack.pop();
				double a = numStack.pop();
				double b = numStack.pop();
				numStack.push(calculate(b, theta, a));
				break;
			}
		}
	}
	return numStack.top();
}

void testStack(void) {
	Stack<int> stack;
	Queue<int> queue;
	string cmd;
	vector<int> cmdN;
	bool quit = false;
	while (!quit) {
		stack.print();
		queue.print();
		cout << "请输入操作：\n1)向栈和队列中插入元素\n2)从栈和队列中删除元素\n3)进制转换\n4)括号检测\n5)表达式求值\n0)退出程序\n";
		getline(cin, cmd);
		cmdN = split(cmd);
		if (cmdN.size() != 1)
			continue;
		switch (cmdN[0]) {
		case 1:
			cout << "请输入要插入的元素\n";
			getline(cin, cmd);
			cmdN = split(cmd);
			stack.push(cmdN[0]);
			queue.push(cmdN[0]);
			break;
		case 2:
			stack.pop();
			queue.pop();
			break;
		case 3:
			cout << "把m进制的数x转化成n进制，分别输入x m n\n";
			getline(cin, cmd);
			cmdN = split(cmd);
			cout << hexadecimalConversion(cmd, cmdN[0], cmdN[1]) << endl;
			break;
		case 4:
			cout << "输入表达式\n";
			getline(cin, cmd);
			if (parenthesesMatching(cmd))
				cout << "括号匹配\n";
			else
				cout << "括号不匹配\n";
			break;
		case 5:
			cout << "输入表达式\n";
			getline(cin, cmd);
			cout << "ans=" << getAns(cmd) << endl;
			break;
		case 0:
			quit = true;
			break;
		}
	}
}