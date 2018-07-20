/*
*	Project:Integer Calculator
*	Date:2018/7/20		Time:1:48.
*	author:Jeffmeoi.
*	这份代码并没有完善,没有处理过读入错误的情况，由于明天要去征兵体检，先睡了233。
*/
#include"stdafx.h"
#include<cstdio>
#include<iostream>
#include<stack>
#include<cctype>
#include<cstring>

#define maxn 100001
using namespace std;

char str[maxn], str2[maxn];
int cur, len;

int priority(char signal) {			/*判断运算的优先级*/
	switch (signal)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:					/*default中即判定‘(’优先级为0*/
		return 0;
	}
}

double cal(double a, double b, char sign) {		/*顾名思义即运算*/

	switch (sign)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	default:
		return 0;
	}

}

int input() {			/*输入一行并将空格等制表符删去*/

	if (NULL == gets_s(str2,maxn))
		return 0;
	int len = strlen(str2);
	int cur1 = 0, cur2 = 0;
	while (cur2 < len) {
		if (str2[cur2] != ' ' && str2[cur2] != '\t' && str2[cur2] != '\n' && str2[cur2] != '\r')
			str[cur1++] = str2[cur2++];
		else
			cur2++;
	}
	str[cur1] = '\0';
	return 1;
}

int main()
{
	printf("请输入表达式：'()'仅能为英文符号：\n");
	while (input() == 1) {

		double tempNum = 0;

		stack<double> nums;
		stack<char> signals;

		cur = 0;
		len = strlen(str);

		while (cur < len) {
			//cout << cur << endl;
			if (isalnum(str[cur])) {			/*如果下标为cur处的字符为数字字符，则读入数字*/
				sscanf_s(str + cur, "%lf", &tempNum);
				nums.push((double)tempNum);
				while (isalnum(str[++cur]) || str[cur] == '.');	/*移动光标至第一个非数字字符处*/
			}
			else {
				if (str[cur] == '(') {			/*读入左括号*/
					signals.push('(');

				}else if (str[cur] == ')') {		/*读入右括号后，则先进行“（）”内的运算再将（弹出栈中*/
					
					while (!signals.empty() && signals.top() != '(' ) {
						//cout << nums.top() << "  " << signals.top() << endl;
						double numA, numB, numC;
						char sign;
						if (!nums.empty()) {		
							numB = nums.top();	
							nums.pop();
						}
						if (!nums.empty()) {
							numA = nums.top();
							nums.pop();
							sign = signals.top();
							signals.pop();
							numC = cal(numA, numB, sign);
							//cout << numC << endl;
							nums.push(numC);
						}else {
							nums.push(numB);
						}
						
					}
					if(signals.top() == '(')		/*将‘（’弹出栈中*/
						signals.pop();

				}else if (str[cur] == '+' || str[cur] == '-' || str[cur] == '*' || str[cur] == '/') {
					//cout << str[cur] << "  " << priority(str[cur]) << "  " << signals.top() << "  " << priority(signals.top()) << endl;
					if (signals.empty() || priority(str[cur]) > priority(signals.top())) {		/*如果新读入的符号优先级大于栈顶符号的优先级，则将新符号压入栈中*/
						signals.push(str[cur]);
					}
					else {			/*否则，先将符号栈中栈顶的符号和数字栈中栈顶的两个数字弹出并进行运算后压入数字栈中，再将符号压入栈中*/
						
						double numA, numB, numC;
						char sign;
						if (!nums.empty()) {
							numB = nums.top();
							nums.pop();
						}
						if (!nums.empty()) {
							numA = nums.top();
							nums.pop();
							sign = signals.top();	signals.pop();
							numC = cal(numA, numB, sign);
							nums.push(numC);
						}
						else {
							nums.push(numB);
						}
						signals.push(str[cur]);
					}

				}
				cur++;
				//cout << cur << endl;
			}
			
		
		}
		
		while (!signals.empty()) {			/*进行完上述过程后，所有的运算必然在同一优先级上，所以只需要不断地弹出数字和符号进行运算即可得出正确答案*/
			double numA, numB, numC;
			char sign;
			numB = nums.top();	
			nums.pop();
			numA = nums.top();	
			nums.pop();
			sign = signals.top();	
			signals.pop();
			numC = cal(numA, numB, sign);
			nums.push(numC);
		}
		
		if (!nums.empty()) {
			cout << nums.top() << endl;
		}
		else {
			cout << 0 << endl;
		}
		printf("请输入表达式：'()'仅能为英文符号：\n");


	}

	return 0;
}

