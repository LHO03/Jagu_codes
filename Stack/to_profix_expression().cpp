/* 여는 괄호의 규칙
1. 여는 괄호는 무조건 스택에 push한다. 이때 스택 내의 어떤 연산자도 pop하지 않는다. 
2. 어떤 연산자를 스택에 push할 때 스택의 top에 여는 괄호가 있으면 아무도 pop하지 않고 그냥 push한다.
3. 입력에 닫는 괄호가 나오면 스택에서 여는 괄호가 나올 때까지 pop하여 출력한다. 닫는 괄호는 스택에 push하지 않는다.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

const string OPERATORS = "+-*/()";
const int PRECEDENCE[] = {1, 1, 2, 2, -1, -1};  // 여는 괄호의 우선순위를 -1로 하면 2번 규칙을 예외로 처리할 필요가 없음.
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
        else{
            throw runtime_error("Syntax Error: invalid character encountered.");
        }
    }
    while(!operator_stack.empty()){
        char op = operator_stack.top();
        if(op == '(') throw runtime_error("Unmatched parenthesis.");
        postfix << op << ' ';
        operator_stack.pop();
    }
    return postfix.str();
}

void process_op(char op, stringstream &postfix){
    if (operator_stack.empty() || op == '('){
        operator_stack.push(op);
    }
    else{
        char top_op = operator_stack.top();
        if(precedence(op) > precedence(top_op)){
            operator_stack.push(op);
        }
        else{
            while(!operator_stack.empty() && precedence(op) <= precedence(top_op)){
                operator_stack.pop();
                if(top_op == '(') break; // op의 우선순위가 top_op보다 낮거나 같은데 top_op가 닫는 괄호라면 op는 닫는 괄호라는 의미 (이면 처음 if에서 걸림
                postfix << top_op << ' ';
                if (!operator_stack.empty()) top_op = operator_stack.top();
            }
            if (op!= ')') operator_stack.push(op);
        }
    }
}

int main(void){
    string expr;
    cout << "Enter an infix expression: ";
    getline(cin, expr);
    cout << convert(expr) << endl;

    return 0;
}