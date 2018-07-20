/*
*	Project:Integer Calculator
*	Date:2018/7/20		Time:1:48.
*	author:Jeffmeoi.
*	��ݴ��벢û������,û�д�������������������������Ҫȥ������죬��˯��233��
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

int priority(char signal) {			/*�ж���������ȼ�*/
	switch (signal)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:					/*default�м��ж���(�����ȼ�Ϊ0*/
		return 0;
	}
}

double cal(double a, double b, char sign) {		/*����˼�弴����*/

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

int input() {			/*����һ�в����ո���Ʊ��ɾȥ*/

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
	printf("��������ʽ��'()'����ΪӢ�ķ��ţ�\n");
	while (input() == 1) {

		double tempNum = 0;

		stack<double> nums;
		stack<char> signals;

		cur = 0;
		len = strlen(str);

		while (cur < len) {
			//cout << cur << endl;
			if (isalnum(str[cur])) {			/*����±�Ϊcur�����ַ�Ϊ�����ַ������������*/
				sscanf_s(str + cur, "%lf", &tempNum);
				nums.push((double)tempNum);
				while (isalnum(str[++cur]) || str[cur] == '.');	/*�ƶ��������һ���������ַ���*/
			}
			else {
				if (str[cur] == '(') {			/*����������*/
					signals.push('(');

				}else if (str[cur] == ')') {		/*���������ź����Ƚ��С��������ڵ������ٽ�������ջ��*/
					
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
					if(signals.top() == '(')		/*������������ջ��*/
						signals.pop();

				}else if (str[cur] == '+' || str[cur] == '-' || str[cur] == '*' || str[cur] == '/') {
					//cout << str[cur] << "  " << priority(str[cur]) << "  " << signals.top() << "  " << priority(signals.top()) << endl;
					if (signals.empty() || priority(str[cur]) > priority(signals.top())) {		/*����¶���ķ������ȼ�����ջ�����ŵ����ȼ������·���ѹ��ջ��*/
						signals.push(str[cur]);
					}
					else {			/*�����Ƚ�����ջ��ջ���ķ��ź�����ջ��ջ�����������ֵ��������������ѹ������ջ�У��ٽ�����ѹ��ջ��*/
						
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
		
		while (!signals.empty()) {			/*�������������̺����е������Ȼ��ͬһ���ȼ��ϣ�����ֻ��Ҫ���ϵص������ֺͷ��Ž������㼴�ɵó���ȷ��*/
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
		printf("��������ʽ��'()'����ΪӢ�ķ��ţ�\n");


	}

	return 0;
}

