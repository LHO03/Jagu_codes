#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <stdexcept>
using namespace std;

// 연산자 판정
bool is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// 연산자 우선순위 반환
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 두 피연산자에 연산자 적용
void apply_op(stack<double>& vals, char op) {
    if (vals.size() < 2) {
        throw runtime_error("Syntax Error: malformed expression.");
    }
    
    double rhs = vals.top();
    vals.pop();
    double lhs = vals.top();
    vals.pop();
    
    double result = 0;
    switch(op) {
        case '+': result = lhs + rhs; break;
        case '-': result = lhs - rhs; break;
        case '*': result = lhs * rhs; break;
        case '/':
            if (rhs == 0) {
                throw runtime_error("Math Error: division by zero.");
            }
            result = lhs / rhs;
            break;
    }
    
    vals.push(result);
}

// 중위표기식 계산
double evaluate_infix(const string& expr) {
    stack<double> vals;      // 피연산자 스택
    stack<char> ops;         // 연산자 스택
    
    int i = 0;
    int len = expr.length();
    
    while (i < len) {
        // 공백 무시
        if (isspace(expr[i])) {
            i++;
            continue;
        }
        
        // 숫자 토큰 파싱 (단항 음수 포함)
        if (isdigit(expr[i]) || expr[i] == '.') {
            string num_str;
            while (i < len && (isdigit(expr[i]) || expr[i] == '.')) {
                num_str += expr[i];
                i++;
            }
            vals.push(stod(num_str));
        }
        // 단항 음수 처리: 식의 시작, 여는 괄호 뒤, 연산자 뒤
        else if (expr[i] == '-') {
            bool is_unary = false;
            
            // 이전 의미있는 문자 찾기
            int j = i - 1;
            while (j >= 0 && isspace(expr[j])) j--;
            
            if (j < 0 || expr[j] == '(' || is_operator(expr[j])) {
                is_unary = true;
            }
            
            if (is_unary) {
                // 단항 음수: 숫자의 일부로 파싱
                i++;
                // 공백 건너뛰기
                while (i < len && isspace(expr[i])) i++;
                
                if (i >= len) {
                    throw runtime_error("Syntax Error: invalid character.");
                }
                
                // 괄호 뒤의 단항 음수인 경우
                if (expr[i] == '(') {
                    vals.push(0);  // 0을 푸시
                    ops.push('-'); // 이항 연산자로 처리
                    continue;
                }
                
                // 숫자 파싱
                string num_str = "-";
                if (isdigit(expr[i]) || expr[i] == '.') {
                    while (i < len && (isdigit(expr[i]) || expr[i] == '.')) {
                        num_str += expr[i];
                        i++;
                    }
                    vals.push(stod(num_str));
                } else {
                    throw runtime_error("Syntax Error: invalid character.");
                }
            } else {
                // 이항 연산자로 처리
                // 스택 top의 연산자보다 우선순위가 낮거나 같으면 pop하여 계산
                while (!ops.empty() && ops.top() != '(' && 
                       precedence(ops.top()) >= precedence('-')) {
                    apply_op(vals, ops.top());
                    ops.pop();
                }
                ops.push('-');
                i++;
            }
        }
        // 여는 괄호: 무조건 스택에 push (스택 내 어떤 연산자도 pop하지 않음)
        else if (expr[i] == '(') {
            ops.push('(');
            i++;
        }
        // 닫는 괄호: 여는 괄호를 만날 때까지 pop하여 계산
        else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                apply_op(vals, ops.top());
                ops.pop();
            }
            if (ops.empty()) {
                throw runtime_error("Syntax Error: unmatched parenthesis.");
            }
            ops.pop(); // 여는 괄호 제거
            i++;
        }
        // 일반 연산자 (+, *, /)
        else if (is_operator(expr[i])) {
            char op = expr[i];
            // 스택 top의 연산자와 우선순위 비교
            // 여는 괄호가 있으면 비교하지 않고 push
            // 우선순위가 높으면 push
            // 낮거나 같으면 pop하여 계산 후 push
            while (!ops.empty() && ops.top() != '(' && 
                   precedence(ops.top()) >= precedence(op)) {
                apply_op(vals, ops.top());
                ops.pop();
            }
            ops.push(op);
            i++;
        }
        else {
            throw runtime_error("Syntax Error: invalid character.");
        }
    }
    
    // 남은 연산자를 모두 처리
    while (!ops.empty()) {
        if (ops.top() == '(') {
            throw runtime_error("Syntax Error: unmatched parenthesis.");
        }
        apply_op(vals, ops.top());
        ops.pop();
    }
    
    // 최종 결과 반환
    if (vals.size() != 1) {
        throw runtime_error("Syntax Error: malformed expression.");
    }
    
    return vals.top();
}

int main() {
    string expr;
    getline(cin, expr);
    
    try {
        double result = evaluate_infix(expr);
        cout.precision(15);
        cout << result << '\n';
    } catch (exception& e) {
        cout << e.what() << '\n';
    }
    
    return 0;
}