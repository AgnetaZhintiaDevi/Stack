#include<iostream>
#include <string.h>
#include<stack>
#include<string>
#include <stdlib.h>
using namespace std;


string infix_to_postfix(string ekspresi);
int TingkatOperator(char operator1, char operator2);
bool Operator(char C);
bool Operand(char C);


string infix_to_postfix(string ekspresi)
{ 
	stack<char> P;
	string postfix = ""; 
	for(int i = 0;i< ekspresi.length();i++) {

		if(ekspresi[i] == ' ' || ekspresi[i] == ',') continue; 

		else if(Operator(ekspresi[i])) 
		{
			while(!P.empty() && P.top() != '(' && TingkatOperator(P.top(),ekspresi[i]))
			{
				postfix+= P.top();
				P.pop();
			}
			P.push(ekspresi[i]);
		}
		else if(Operand(ekspresi[i]))
		{
			postfix +=ekspresi[i];
		}

		else if (ekspresi[i] == '(') 
		{
			P.push(ekspresi[i]);
		}

		else if(ekspresi[i] == ')') 
		{
			while(!P.empty() && P.top() !=  '(') {
				postfix += P.top();
				P.pop();
			}
			P.pop();
		}
	}

	while(!P.empty()) {
		postfix += P.top();
		P.pop();
	}

	return postfix;
}

bool Operand(char C) 
{
	if(C >= '0' && C <= '9') return true;
	if(C >= 'a' && C <= 'z') return true;
	if(C >= 'A' && C <= 'Z') return true;
	return false;
}

bool Operator(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/' || C== '$')
		return true;

	return false;
}

int Awesome(char opr)
{
	if(opr == '$') return true;
	return false;
}
 
int carioperator(char opr)
{
	int destiny = -1; 
	switch(opr)
	{
	case '+':
	case '-':
		destiny = 1;
		break;
	case '*':
	case '/':
		destiny = 2;
		break;
	case '$':
		destiny = 3;
	}
	return destiny;
}

int TingkatOperator(char opr1, char opr2)
{
	int opr1Weight = carioperator(opr1);
	int opr2Weight = carioperator(opr2);
 
	if(opr1Weight == opr2Weight)
	{
		if(Awesome(opr1)) return false;
		else return true;
	}
	return opr1Weight > opr2Weight ?  true: false;
}




struct Stack
{
    int top;
    unsigned capacity;
    int* array;
};
 
struct Stack* createStack( unsigned capacity )
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
 
    if (!stack) return NULL;
 
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int*) malloc(stack->capacity * sizeof(int));
 
    if (!stack->array) return NULL;
 
    return stack;
}
 
int isEmpty(struct Stack* stack)
{
    return stack->top == -1 ;
}
 
char peek(struct Stack* stack)
{
    return stack->array[stack->top];
}
 
char pop(struct Stack* stack)
{
    if (!isEmpty(stack))
        return stack->array[stack->top--] ;
    return '$';
}
 
void push(struct Stack* stack, char op)
{
    stack->array[++stack->top] = op;
}
 
 
int evaluatePostfix(char* exp)
{
    struct Stack* stack = createStack(strlen(exp));
    int i;
 
    if (!stack) return -1;
 
    for (i = 0; exp[i]; ++i)
    {
        if (isdigit(exp[i]))
            push(stack, exp[i] - '0');
        else
        {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (exp[i])
            {
             case '+': push(stack, val2 + val1); break;
             case '-': push(stack, val2 - val1); break;
             case '*': push(stack, val2 * val1); break;
             case '/': push(stack, val2/val1);   break;
            }
        }
    }
    return pop(stack);
}
 
int main()
{
	string ekspresi;
	string postfix;
	cout<<"masukkan expresi infix = ";cin>>ekspresi;
	postfix = infix_to_postfix(ekspresi);
	cout<<"menjadi postfix = "<<postfix<<endl;
    char exp[] = "postfix";
    cout<<"hasil dari "<<exp<<" adalah "<< evaluatePostfix(exp);
    return 0;
}
