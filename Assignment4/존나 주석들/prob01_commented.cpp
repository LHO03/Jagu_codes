/**
 * 문제 1: 괄호 번호 매기기 (Parenthesis Numbering)
 * 
 * [문제 설명]
 * - 괄호가 포함된 문자열을 입력받음
 * - 각 괄호 쌍에 번호를 부여하여 출력
 * - 여는 괄호가 나올 때마다 새로운 번호 부여
 * - 닫는 괄호는 매칭되는 여는 괄호의 번호 출력
 * 
 * [예시]
 * 입력: (a+(b*c))+(d/e)
 * 출력: 1 2 2 1 3 3
 * 설명: 첫 번째 '(' → 1번
 *       두 번째 '(' → 2번
 *       첫 번째 ')' → 2번과 매칭
 *       두 번째 ')' → 1번과 매칭
 *       세 번째 '(' → 3번
 *       세 번째 ')' → 3번과 매칭
 * 
 * [알고리즘: 스택]
 * - 여는 괄호: 새 번호를 부여하고 스택에 push
 * - 닫는 괄호: 스택에서 pop하여 매칭된 번호 출력
 * 
 * [제약사항]
 * - STL stack 사용 금지, 직접 구현해야 함
 */

#include <iostream>
#include <string>
using namespace std;

const int MAX_CAPACITY = 100;  // 스택 최대 크기 (최대 중첩 깊이)

/**
 * Paren 클래스 (스택 직접 구현)
 * 
 * [역할] 정수를 저장하는 스택 자료구조
 * 
 * [멤버 변수]
 * - data[]: 정수를 저장하는 배열
 * - count: 현재 저장된 원소 개수 (= top index + 1)
 * 
 * [스택 동작 원리]
 * - LIFO (Last In First Out): 마지막에 들어간 것이 먼저 나옴
 * - push: 배열 끝에 추가, count 증가
 * - pop: count 감소 (실제 데이터는 그대로, 논리적 삭제)
 * - top: count-1 위치의 값 반환
 */
class Paren {
private:
    int data[MAX_CAPACITY];  // 괄호 번호를 저장하는 배열
    int count = 0;           // 현재 스택에 저장된 원소 개수
    
public:
    /**
     * empty()
     * [역할] 스택이 비어있는지 확인
     * [반환] true: 비어있음, false: 원소 있음
     */
    bool empty() { return count == 0; }
    
    /**
     * full()
     * [역할] 스택이 가득 찼는지 확인
     * [반환] true: 가득 참, false: 여유 있음
     */
    bool full()  { return count == MAX_CAPACITY; }

    /**
     * push(x)
     * [역할] 스택에 원소 추가
     * [매개변수] x: 추가할 정수 (괄호 번호)
     * [동작] data[count] = x 후 count 증가
     */
    void push(int x) {
        if (full()) throw runtime_error("Full");
        data[count++] = x;  // 후위 증가: 먼저 저장 후 count 증가
    }
    
    /**
     * pop()
     * [역할] 스택에서 top 원소 제거
     * [동작] count만 감소 (실제 데이터는 그대로)
     */
    void pop() {
        if (empty()) throw runtime_error("Empty");
        --count;  // count만 감소하면 논리적으로 삭제됨
    }
    
    /**
     * top()
     * [역할] 스택의 top 원소 반환 (제거하지 않음)
     * [반환] 가장 최근에 push된 원소
     */
    int top() {
        if (empty()) throw runtime_error("Empty");
        return data[count - 1];
    }
};

/**
 * paren_count(ex_input)
 * 
 * [역할] 문자열을 스캔하며 각 괄호에 번호를 부여
 * 
 * [매개변수]
 * - ex_input: 괄호가 포함된 입력 문자열
 * 
 * [반환값]
 * - 공백으로 구분된 괄호 번호들의 문자열
 * 
 * [알고리즘 상세]
 * 
 * 스택을 사용하는 이유:
 * - 중첩된 괄호에서 가장 최근의 여는 괄호와 닫는 괄호가 매칭됨
 * - LIFO 특성이 괄호 매칭에 적합
 * 
 * [동작 과정]
 * 1. 문자열을 한 글자씩 순회
 * 2. '(' 발견:
 *    - 새 번호 부여 (next_id 증가)
 *    - 번호를 스택에 push
 *    - 번호를 결과에 추가
 * 3. ')' 발견:
 *    - 스택에서 top 값 확인 (매칭되는 '('의 번호)
 *    - pop으로 제거
 *    - 해당 번호를 결과에 추가
 * 4. 다른 문자: 무시
 * 
 * [예시 실행]
 * 입력: "(a+(b*c))"
 * 
 * 문자별 처리:
 * '(' → next_id=1, push(1), 출력: "1"
 * 'a' → 무시
 * '+' → 무시
 * '(' → next_id=2, push(2), 출력: "1 2"
 * 'b' → 무시
 * '*' → 무시
 * 'c' → 무시
 * ')' → top()=2, pop(), 출력: "1 2 2"
 * ')' → top()=1, pop(), 출력: "1 2 2 1"
 */
string paren_count(string& ex_input) {
    Paren stack;       // 괄호 번호를 저장할 스택
    int next_id = 0;   // 다음에 부여할 괄호 번호
    string result;     // 결과 문자열
    bool first = true; // 첫 번째 출력인지 (공백 처리용)

    for (char ch : ex_input) {
        if (ch == '(') {
            // 여는 괄호: 새 번호 부여
            int id = ++next_id;      // 번호 증가 후 사용
            stack.push(id);          // 스택에 저장 (나중에 ')'와 매칭용)
            
            // 결과 문자열에 추가 (공백 처리)
            if (!first) result += ' ';
            result += to_string(id);
            first = false;
            
        } else if (ch == ')') {
            // 닫는 괄호: 매칭되는 여는 괄호의 번호 찾기
            if (stack.empty()) throw runtime_error("Unmatched )");
            
            int id = stack.top();    // 매칭되는 '('의 번호
            stack.pop();             // 스택에서 제거
            
            // 결과 문자열에 추가
            if (!first) result += ' ';
            result += to_string(id);
            first = false;
        }
        // 괄호가 아닌 문자는 무시
    }
    
    return result;
}

/**
 * main()
 * 
 * [동작]
 * 1. 한 줄의 문자열 입력
 * 2. paren_count 호출
 * 3. 결과 출력
 */
int main() {
    string ex_input;
    getline(cin, ex_input);  // 공백 포함 전체 줄 입력
    
    try {
        cout << paren_count(ex_input) << endl;
    } catch (runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    return 0;
}

/**
 * [스택의 괄호 매칭 시각화]
 * 
 * 입력: "((()))"
 * 
 * 문자  동작           스택 상태    출력
 * '('   push(1)       [1]         "1"
 * '('   push(2)       [1,2]       "1 2"
 * '('   push(3)       [1,2,3]     "1 2 3"
 * ')'   pop() → 3     [1,2]       "1 2 3 3"
 * ')'   pop() → 2     [1]         "1 2 3 3 2"
 * ')'   pop() → 1     []          "1 2 3 3 2 1"
 * 
 * 최종 출력: "1 2 3 3 2 1"
 */
