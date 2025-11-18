#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
using namespace std;

const string OPERATORS = "+-*/";
stack<int> operand_stack;

string::size_type is_operator(char ch){
    return OPERATORS.find(ch); // 검색을 해준 다음 해당 index를 return 해줌  *아무것도 없다면 string::npos
}

int eval(string expr){
     stringstream exprstream(expr);
    string token;
    while(getline(exprstream, token, ' ')){
        if (isdigit(token[0])){         // 피연산자
            operand_stack.push(stoi(token));
        }
        else if (is_operator(token[0]) != string::npos){    // 연산자
            int result = eval_op(token[0]);
            operand_stack.push(result);
        }
        else{
            throw runtime_error("Syntax Error: invalid character encountered.");
        }
    }
    if (operand_stack.empty()) throw runtime_error("Syntax Error: Stack empty in eval_op.");
    
    int answer = operand_stack.top();
    operand_stack.pop();
    if (operand_stack.empty()) return answer;
    else throw runtime_error("Syntax Error: Stack should be empty");
}

int eval_op(char op){
    if (operand_stack.empty()) throw runtime_error("Syntax Error: Stack empty in eval_op.");
    int rhs = operand_stack.top();
    operand_stack.pop();
    
    if (operand_stack.empty()) throw runtime_error("Syntax Error: Stack empty in eval_op.");
    int lhs = operand_stack.top();
    operand_stack.pop();
    
    int result = 0;
    switch(op){
        case '+': result = lhs + rhs; break;
        case '-': result = lhs - rhs; break;
        case '*': result = lhs * rhs; break;
        case '/': result = lhs / rhs; break;
    }    
    return result;
}

int main(void){
    string expr;
    cout << "Enter a postfix expression: ";
    getline(cin, expr);
    try{
        cout << eval(expr) << endl;
    } catch(exception &e){ // 모든 종류의 error를 throw한 것을 catch한다
        cout << e.what() << endl; // error 메시지 출력
    }
    return 0;
}