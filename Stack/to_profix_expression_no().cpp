/*
후위표기식의 힌트
1. 피연산자들은 중위 표기식에 나온 순서대로 출력된다.
2. 연산자들은 중위 표기식에서의 계산되는 순서대로 출력된다.
** 피연산자들은 즉시 출력
** 연산자들은 스택에 반드시 들어와야 
   하지만 스택에 있는 것들 중에서 우선순위가 높거나 같은 것들은 꺼내고 스택에 들어간다.
** 수식이 종료되면 스택에 있는 모든 연산자들을 pop하여 출력
*/
#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
using namespace std;

const string OPERATORS = "+-*/";
const int PRECEDENCE[] = {1, 1, 2, 2};      // +, -, *, /의 우선순위를 순서대로 1, 1, 2, 2로 정의
                                            // 큰 값이 더 높은 우선순위를 가진다.

stack<char> operator_stack;

string::size_type is_operator(char ch){
    return OPERATORS.find(ch);
}

int precedence(char op){
    return PRECEDENCE[is_operator(op)];
}

string convert(string infix){
    stringstream postfix, infixstream(infix);
    string token;
    while(getline(infixstream, token, ' ')){
        if (isdigit(token[0])){
            postfix << token << ' ';
        }
        else if (is_operator(token[0]) != string::npos){
            process_op(token[0], postfix);
        }
        else runtime_error("Syntax Error: invalid character encountered.");
    }
    
    while(!operator_stack.empty()){
        char op = operator_stack.top();
        postfix << op << ' ';
        operator_stack.pop();
    }
    return postfix.str();   //stringstream을 string으로 변환해주는 방법
}

void process_op(char op, stringstream &postfix){
    if(operator_stack.empty()){
        operator_stack.push(op);
    }
    else {
        char top_op = operator_stack.top();
        if (precedence(op) > precedence(top_op)) {
            operator_stack.push(op);
        }
        else{
            while(!operator_stack.empty() && precedence(op) <= precedence(top_op)){
                operator_stack.pop();
                postfix << top_op << ' ';
                if(!operator_stack.empty()){
                    top_op = operator_stack.top();
                }
            }
            operator_stack.push(op);
        }
    }
}

int main(void){
    string expr;
    getline(cin, expr);
    cout << convert(expr) << endl;

    return 0;
}
