#include"stdafx.h"
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cctype>
#include<stack>

#define maxn 1000001

using namespace std;

char expr[maxn];		//expr为中缀表达式
char ans[maxn];			//ans为后缀表达式的结果

int input() {			/*输入一行并将空格等制表符删去*/

	memset(expr, 0, sizeof(expr));
	memset(ans, 0, sizeof(ans));

	if (NULL == gets_s(expr, maxn))
		return 0;
	int len = strlen(expr);
	int cur1 = 0, cur2 = 0;
	while (cur2 < len) {
		if (expr[cur2] != ' ' && expr[cur2] != '\t' && expr[cur2] != '\n' && expr[cur2] != '\r')
			expr[cur1++] = expr[cur2++];
		else
			cur2++;
	}
	if (expr[cur1 - 1] == '=')
		expr[cur1 - 1] = '\0';
	else
		expr[cur1] = '\0';

	return 1;
}

int priority(char sign) {	/*判断优先级*/
	
	switch (sign)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	}

	return 0;
}

int transform() {		/*计算*/

	stack<char> signals;
	int cur = 0, index = 0;
	int len = strlen(expr);
	while (cur < len) {
		if (isalpha(expr[cur])) {
			ans[index++] = expr[cur];
		}
		else{
			if (signals.empty()) {
				signals.push(expr[cur]);
			}
			else if (expr[cur] == '(') {
				signals.push(expr[cur]);
			}
			else if (expr[cur] == ')') {
				while (signals.top() != '(') {
					ans[index++] = signals.top();
					signals.pop();
				}
				if (signals.top() == '(') {
					signals.pop();
				}
			}
			else if (expr[cur] == '+' || expr[cur] == '-' || expr[cur] == '*' || expr[cur] == '/') {
				while (!signals.empty() && priority(expr[cur]) <= priority(signals.top())) {
					ans[index++] = signals.top();
					signals.pop();
				}
				signals.push(expr[cur]);
			}
		}
		
		cur++;
	}
	while (!signals.empty()) {
		ans[index++] = signals.top();
		signals.pop();
	}
	cout << ans << endl;

	return 0;

}

int main(int argc, char* argv[]) {

	while (input()) {
		transform();
	}
	
	return 0;

}