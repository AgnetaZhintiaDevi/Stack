#include<iostream>
#include<stack>
#include<string>

using namespace std;

string infix_to_postfix(string ekspresi);

int TingkatOperator(char operator1, char operator2);
bool Operator(char C);
bool Operand(char C);

int main() 
{
	string ekspresi;
	cout<<"masukkan expresi infix\t= "; cin>>ekspresi;
	string postfix = infix_to_postfix(ekspresi);
	cout<<"postfixnya adalah\t= "<<postfix<<endl;
}


string infix_to_postfix(string ekspresi)
{ 
	stack<char> P;
	string postfix = ""; 
	for(int i = 0;i< ekspresi.length();i++) {

		if(ekspresi[i] == ' ' || ekspresi[i] == ',') continue; 

		else if(Operator(ekspresi[i])){
			while(!P.empty() && P.top() != '(' && TingkatOperator(P.top(),ekspresi[i])){
				postfix+= P.top();
				P.pop();
			}
			P.push(ekspresi[i]);
		}
		else if(Operand(ekspresi[i])){
			postfix +=ekspresi[i];
		}

		else if (ekspresi[i] == '('){
			P.push(ekspresi[i]);
		}

		else if(ekspresi[i] == ')'){
			while(!P.empty() && P.top() !=  '('){
				postfix += P.top();
				P.pop();
			}
			P.pop();
		}
	}

	while(!P.empty()){
		postfix += P.top();
		P.pop();
	}

	return postfix;
}

bool Operand(char C){
	if(C >= '0' && C <= '9') return true;
	if(C >= 'a' && C <= 'z') return true;
	if(C >= 'A' && C <= 'Z') return true;
	return false;
}

bool Operator(char C){
	if(C == '+' || C == '-' || C == '*' || C == '/' || C== '$')
		return true;

	return false;
}

int Awesome(char opr){
	if(opr == '$') return true;
	return false;
}
 
int carioperator(char opr){
	int destiny = -1; 
	switch(opr){
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

int TingkatOperator(char opr1, char opr2){
	int opr1Weight = carioperator(opr1);
	int opr2Weight = carioperator(opr2);
 	if(opr1Weight == opr2Weight){
		if(Awesome(opr1)) return false;
		else return true;
	}
	return opr1Weight > opr2Weight ?  true: false;
}
