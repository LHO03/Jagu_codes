/**
 * 문제 5: 중위표기식 계산기 (Infix Expression Evaluator)
 * 
 * [문제 설명]
 * - 중위 표기식(일반적인 수학 표기)을 입력받아 계산
 * - 음수, 실수 피연산자 지원
 * - 토큰 사이 공백 제약 없음 (붙여쓰기, 띄어쓰기 모두 허용)
 * - 후위표기식 변환과 계산을 동시에 수행
 * 
 * [지원 기능]
 * - 연산자: +, -, *, /
 * - 괄호: (, )
 * - 피연산자: 정수, 실수, 음수
 * 
 * [알고리즘: Shunting-Yard 알고리즘 변형]
 * - 두 개의 스택 사용: 피연산자 스택, 연산자 스택
 * - 후위표기식으로 변환하면서 바로 계산
 */

#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <stdexcept>
using namespace std;

/**
 * is_operator(ch)
 * 
 * [역할] 문자가 연산자인지 판별
 * [지원 연산자] +, -, *, /
 */
bool is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

/**
 * precedence(op)
 * 
 * [역할] 연산자의 우선순위 반환
 * 
 * [우선순위]
 * - +, -: 1 (낮음)
 * - *, /: 2 (높음)
 * - 그 외: 0 (괄호 등)
 * 
 * [우선순위 규칙]
 * - 높은 우선순위 연산자가 먼저 계산됨
 * - 같은 우선순위는 왼쪽에서 오른쪽으로 (좌결합)
 */
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

/**
 * apply_op(vals, op)
 * 
 * [역할] 피연산자 스택에서 두 값을 꺼내 연산 수행 후 결과를 다시 push
 * 
 * [매개변수]
 * - vals: 피연산자 스택 (참조)
 * - op: 적용할 연산자
 * 
 * [동작]
 * 1. 스택에서 오른쪽 피연산자(rhs) pop
 * 2. 스택에서 왼쪽 피연산자(lhs) pop
 * 3. lhs op rhs 계산
 * 4. 결과를 스택에 push
 * 
 * [주의]
 * - pop 순서: 먼저 pop한 것이 오른쪽 피연산자
 * - 뺄셈, 나눗셈은 순서가 중요!
 * - 0으로 나누기 예외 처리
 */
void apply_op(stack<double>& vals, char op) {
    if (vals.size() < 2) {
        throw runtime_error("Syntax Error: malformed expression.");
    }
    
    double rhs = vals.top();  // 오른쪽 피연산자 (먼저 pop)
    vals.pop();
    double lhs = vals.top();  // 왼쪽 피연산자
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

/**
 * evaluate_infix(expr)
 * 
 * [역할] 중위표기식을 계산하여 결과 반환
 * 
 * [매개변수]
 * - expr: 중위표기식 문자열
 * 
 * [반환값]
 * - 계산 결과 (double)
 * 
 * [알고리즘: Shunting-Yard (변환과 계산 동시)]
 * 
 * Shunting-Yard 알고리즘:
 * - Dijkstra가 개발한 중위→후위 변환 알고리즘
 * - 두 개의 스택 사용: 출력 큐(여기선 값 스택), 연산자 스택
 * - 이 구현에서는 변환하면서 바로 계산
 * 
 * [두 스택의 역할]
 * - vals (피연산자 스택): 숫자와 중간 계산 결과 저장
 * - ops (연산자 스택): 아직 처리되지 않은 연산자 저장
 * 
 * [핵심 규칙]
 * 
 * 1. 숫자: vals 스택에 push
 * 
 * 2. 여는 괄호 '(': ops 스택에 push
 *    - 괄호 안의 연산을 먼저 처리하기 위한 경계 역할
 * 
 * 3. 닫는 괄호 ')': 
 *    - '('를 만날 때까지 ops에서 pop하며 계산
 *    - '(' 제거
 * 
 * 4. 연산자:
 *    - ops top과 우선순위 비교
 *    - top의 우선순위가 높거나 같으면: pop하여 계산
 *    - 현재 연산자를 ops에 push
 * 
 * 5. 수식 끝:
 *    - ops에 남은 모든 연산자 pop하여 계산
 * 
 * [단항 음수 처리]
 * 
 * 문제: "-3 + 5"에서 -는 단항 연산자
 * 해결: 음수가 나올 수 있는 위치 감지
 * - 수식 시작
 * - '(' 직후
 * - 연산자 직후
 * 
 * 처리 방법:
 * - 다음에 오는 숫자와 합쳐서 음수로 파싱
 * - 또는 0을 push하고 이항 연산자로 처리 (괄호 뒤의 경우)
 * 
 * [동작 과정 예시]
 * 
 * 수식: "3 + 4 * 2"
 * 
 * '3': vals=[3]
 * '+': ops=[+]
 * '4': vals=[3,4]
 * '*': ops=[+,*] (우선순위 비교: * > +, pop 안함)
 * '2': vals=[3,4,2]
 * 끝:  pop '*' → vals=[3,8]
 *      pop '+' → vals=[11]
 * 
 * 결과: 11
 */
double evaluate_infix(const string& expr) {
    stack<double> vals;      // 피연산자 스택
    stack<char> ops;         // 연산자 스택
    
    int i = 0;
    int len = expr.length();
    
    while (i < len) {
        // ===== 공백 무시 =====
        if (isspace(expr[i])) {
            i++;
            continue;
        }
        
        // ===== 숫자 토큰 파싱 =====
        // 숫자 또는 소수점으로 시작하면 숫자 전체를 파싱
        if (isdigit(expr[i]) || expr[i] == '.') {
            string num_str;
            while (i < len && (isdigit(expr[i]) || expr[i] == '.')) {
                num_str += expr[i];
                i++;
            }
            vals.push(stod(num_str));  // 문자열 → double 변환
        }
        
        // ===== 단항 음수 처리 =====
        // '-'가 음수 부호인지 뺄셈 연산자인지 판별
        else if (expr[i] == '-') {
            bool is_unary = false;
            
            // 이전 의미있는 문자 찾기 (공백 건너뜀)
            int j = i - 1;
            while (j >= 0 && isspace(expr[j])) j--;
            
            // 단항 음수인 경우:
            // 1. 수식 시작 (j < 0)
            // 2. '(' 직후
            // 3. 연산자 직후
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
                
                // 괄호 뒤의 단항 음수인 경우: -(...)
                // 0 - (...) 로 변환하여 처리
                if (expr[i] == '(') {
                    vals.push(0);  // 0을 push
                    ops.push('-'); // 이항 연산자로 처리
                    continue;
                }
                
                // 숫자 파싱 (음수 포함)
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
                // 스택 top의 연산자와 우선순위 비교
                while (!ops.empty() && ops.top() != '(' && 
                       precedence(ops.top()) >= precedence('-')) {
                    apply_op(vals, ops.top());
                    ops.pop();
                }
                ops.push('-');
                i++;
            }
        }
        
        // ===== 여는 괄호 =====
        // 무조건 스택에 push (괄호 안의 연산 경계 표시)
        else if (expr[i] == '(') {
            ops.push('(');
            i++;
        }
        
        // ===== 닫는 괄호 =====
        // 여는 괄호를 만날 때까지 연산자 처리
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
        
        // ===== 일반 연산자 (+, *, /) =====
        else if (is_operator(expr[i])) {
            char op = expr[i];
            
            // 우선순위 비교:
            // - ops top이 '('가 아니고
            // - ops top의 우선순위가 현재 연산자보다 높거나 같으면
            // - pop하여 계산
            while (!ops.empty() && ops.top() != '(' && 
                   precedence(ops.top()) >= precedence(op)) {
                apply_op(vals, ops.top());
                ops.pop();
            }
            ops.push(op);
            i++;
        }
        
        // ===== 잘못된 문자 =====
        else {
            throw runtime_error("Syntax Error: invalid character.");
        }
    }
    
    // ===== 남은 연산자 처리 =====
    while (!ops.empty()) {
        if (ops.top() == '(') {
            throw runtime_error("Syntax Error: unmatched parenthesis.");
        }
        apply_op(vals, ops.top());
        ops.pop();
    }
    
    // ===== 최종 결과 =====
    // 정상적인 수식이면 vals에 정확히 하나의 값만 있어야 함
    if (vals.size() != 1) {
        throw runtime_error("Syntax Error: malformed expression.");
    }
    
    return vals.top();
}

/**
 * main()
 * 
 * [동작]
 * 1. 한 줄의 수식 입력
 * 2. evaluate_infix 호출
 * 3. 결과 출력 (높은 정밀도)
 */
int main() {
    string expr;
    getline(cin, expr);  // 공백 포함 전체 줄 입력
    
    try {
        double result = evaluate_infix(expr);
        cout.precision(15);  // 실수 정밀도 설정
        cout << result << '\n';
    } catch (exception& e) {
        cout << e.what() << '\n';
    }
    
    return 0;
}

/**
 * [Shunting-Yard 알고리즘 시각화]
 * 
 * 수식: "3 + 4 * 2 - 1"
 * 
 * 단계  토큰  vals 스택       ops 스택    동작
 * 1     3     [3]             []         숫자 push
 * 2     +     [3]             [+]        연산자 push
 * 3     4     [3,4]           [+]        숫자 push
 * 4     *     [3,4]           [+,*]      * > +, push
 * 5     2     [3,4,2]         [+,*]      숫자 push
 * 6     -     [3,8]           [+]        * pop, 계산 (4*2=8)
 *             [11]            []         + pop, 계산 (3+8=11)
 *             [11]            [-]        - push
 * 7     1     [11,1]          [-]        숫자 push
 * 끝          [10]            []         - pop, 계산 (11-1=10)
 * 
 * 결과: 10
 * 
 * [괄호 처리 예시]
 * 
 * 수식: "(3 + 4) * 2"
 * 
 * 단계  토큰  vals 스택       ops 스택    동작
 * 1     (     []              [(]        '(' push
 * 2     3     [3]             [(]        숫자 push
 * 3     +     [3]             [(,+]      연산자 push
 * 4     4     [3,4]           [(,+]      숫자 push
 * 5     )     [7]             []         '('까지 pop, 계산
 * 6     *     [7]             [*]        연산자 push
 * 7     2     [7,2]           [*]        숫자 push
 * 끝          [14]            []         * pop, 계산 (7*2=14)
 * 
 * 결과: 14
 * 
 * [단항 음수 예시]
 * 
 * 수식: "-3 + 5"
 * - '-'가 수식 시작에 있으므로 단항
 * - "-3"을 음수 숫자로 파싱
 * - vals=[-3,5], 결과: 2
 * 
 * 수식: "-(3 + 4)"
 * - '-' 후 '('가 오는 경우
 * - 0 push, '-' push로 변환
 * - 0 - (3+4) = -7
 */
