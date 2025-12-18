/*
 * ============================================================================
 * prob03.cpp - K개의 숫자를 제거하여 가장 큰 수 만들기
 * ============================================================================
 * 
 * [문제 개요]
 * - N자리 숫자 문자열에서 K개의 숫자를 제거
 * - 남은 숫자들의 순서를 유지하면서 가장 큰 수를 만듦
 * - 예: "1924" 에서 2개 제거 → "94" (9와 4를 남김)
 * 
 * [핵심 아이디어 - 그리디]
 * - 앞자리가 클수록 전체 수가 커짐
 * - 새 숫자가 스택 top보다 크면, top을 제거 (더 작은 수를 앞에 두면 손해)
 * - 제거 횟수가 K를 넘지 않도록 관리
 * 
 * [알고리즘]
 * - 스택을 이용한 그리디
 * - 각 숫자를 순회하며:
 *   1. 스택 top < 현재 숫자 && 아직 K개 미만 제거 → pop (제거)
 *   2. 현재 숫자를 push
 * - 최종 스택의 내용이 결과
 * 
 * [예시] N = "1924", K = 2
 * 
 * '1': stack=[], push('1'), stack=['1']
 * '9': stack=['1'], '1' < '9' → pop, removed=1
 *      stack=[], push('9'), stack=['9']
 * '2': stack=['9'], '9' > '2' → push('2'), stack=['9','2']
 * '4': stack=['9','2'], '2' < '4' → pop, removed=2
 *      stack=['9'], '9' > '4' → push('4'), stack=['9','4']
 * 
 * 결과: "94"
 * 
 * [시간 복잡도] O(N) - 각 숫자는 최대 한 번 push, 한 번 pop
 * [공간 복잡도] O(N) - 스택 및 결과 문자열
 */

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

const int MAX_SIZE = 1000000;   // 최대 입력 길이

/*
 * ============================================================================
 * Stack 클래스 - 문자를 저장하는 배열 기반 스택
 * ============================================================================
 * 
 * [용도]
 * - 결과 숫자를 구성할 문자들을 저장
 * - 그리디하게 큰 숫자가 앞에 오도록 관리
 * 
 * [특징]
 * - top_index: -1부터 시작 (비어있음 = -1)
 * - get_result(): 스택 내용을 문자열로 변환
 */
class Stack {
private:
    char arr[MAX_SIZE];         // 숫자 문자 저장 배열
    int top_index = -1;         // 스택 top의 인덱스 (-1: 비어있음)
    int max_capacity;           // 스택 최대 용량 (toKeep = N - K)
    
public:
    Stack() = default;
    
    /*
     * 생성자 - 최대 용량 지정
     * 매개변수: size - 유지할 숫자 개수 (N - K)
     */
    Stack(int size) : max_capacity(size) {}
    
    /*
     * empty() - 스택이 비어있는지 확인
     */
    bool empty() { return top_index == -1; }
    
    /*
     * full() - 스택이 가득 찼는지 확인
     * 참고: 결과의 최대 길이(toKeep)에 도달했는지 확인
     */
    bool full() { return top_index == MAX_SIZE - 1; }

    /*
     * push(x) - 숫자 문자를 스택에 추가
     */
    void push(char x) {
        if (full()) {
            throw runtime_error("Full");
        }
        arr[++top_index] = x;
    }

    /*
     * pop() - 스택에서 숫자 제거 (제거 카운트 증가와 함께 사용)
     */
    void pop() {
        if (empty()) {
            throw runtime_error("Empty");
        }
        top_index--;
    }
    
    /*
     * top() - 스택의 최상위 문자 반환
     * 반환: 현재 결과의 마지막 숫자
     */
    char top() {
        if (empty()) {
            throw runtime_error("Empty");
        }
        return arr[top_index];
    }

    /*
     * size() - 현재 스택 크기 반환
     * 반환: 현재까지 선택된 숫자의 개수
     */
    int size() {
        return top_index + 1;
    }
    
    /*
     * get_result() - 스택 내용을 문자열로 변환
     * 반환: 스택의 bottom부터 top까지를 이어붙인 문자열
     * 용도: 최종 결과 숫자 생성
     */
    string get_result() {
        string result = "";
        for (int i = 0; i <= top_index; i++) {
            result += arr[i];
        }
        return result;
    }
};

/*
 * ============================================================================
 * find_max_number() - K개 숫자를 제거하여 최대 수 생성
 * ============================================================================
 * 
 * [매개변수]
 * - N: 숫자 문자열
 * - K: 제거할 숫자의 개수
 * 
 * [반환값]
 * - K개를 제거한 후 가장 큰 수 (문자열)
 * 
 * [알고리즘 상세]
 * 
 * 1. 유효성 검사:
 *    - K >= n: 모든 숫자를 제거하면 결과가 없음
 *    - K < 0: 잘못된 입력
 * 
 * 2. 핵심 변수:
 *    - toKeep = n - K: 최종 결과의 자릿수
 *    - removed: 지금까지 제거한 숫자 개수
 * 
 * 3. 각 숫자(current)를 순회하며:
 *    
 *    a. while 조건으로 제거 여부 결정:
 *       - !stack.empty(): 스택에 숫자가 있어야 비교 가능
 *       - stack.top() < current: top이 현재보다 작으면 제거 대상
 *       - removed < K: 아직 K개를 다 제거하지 않음
 *       - stack.size() + (n - i) > toKeep: 
 *         현재 스택 + 남은 숫자 > 필요한 개수
 *         → 제거해도 toKeep개를 채울 수 있음
 *    
 *    b. 조건 만족 시 pop() 후 removed++
 *    
 *    c. 스택이 가득 차지 않았으면 push(current)
 *       - 이미 가득 찼으면 현재 숫자 버림 (removed++)
 * 
 * [예시 트레이스] N = "4177252841", K = 4, toKeep = 6
 * 
 * i=0, '4': stack=[], push, stack=['4']
 * i=1, '1': '4' > '1', push, stack=['4','1']
 * i=2, '7': '1' < '7', pop(removed=1), '4' < '7', pop(removed=2)
 *           push, stack=['7']
 * i=3, '7': '7' == '7', push, stack=['7','7']
 * i=4, '2': '7' > '2', push, stack=['7','7','2']
 * i=5, '5': '2' < '5', pop(removed=3), '7' > '5', push, stack=['7','7','5']
 * i=6, '2': '5' > '2', push, stack=['7','7','5','2']
 * i=7, '8': '2' < '8', pop(removed=4), '5' < '8', size+remain=4+2=6 == toKeep
 *           더 이상 제거 불가, push, stack=['7','7','5','8']
 * i=8, '4': push, stack=['7','7','5','8','4']
 * i=9, '1': push, stack=['7','7','5','8','4','1'], size=6=toKeep
 * 
 * 결과: "775841"
 * 
 * [그리디 정당성]
 * - 앞자리가 클수록 전체 수가 큼
 * - 작은 숫자를 앞에 두는 것은 항상 손해
 * - 따라서 뒤에 더 큰 숫자가 오면 앞의 작은 숫자를 제거하는 것이 최적
 */
string find_max_number(string N, int K) {
    int n = N.length();
    int toKeep = n - K;         // 유지해야 할 숫자 개수
    
    // 유효성 검사
    if (K >= n) {
        throw runtime_error("Cannot remove");
    }
    if (K < 0) {
        throw runtime_error("K negative");
    }
    
    Stack stack(toKeep);
    int removed = 0;            // 제거한 숫자 개수
    
    for (int i = 0; i < n; i++) {
        char current = N[i];
        
        // ================================================================
        // 그리디 제거 로직
        // ================================================================
        // 스택 top이 현재 숫자보다 작고,
        // 아직 K개 미만으로 제거했고,
        // 제거해도 toKeep개를 채울 수 있으면 → 제거
        while (!stack.empty() && stack.top() < current && removed < K && 
               stack.size() + (n - i) > toKeep) {
            stack.pop();
            removed++;
        }
        
        // ================================================================
        // 현재 숫자 추가 또는 버림
        // ================================================================
        if (!stack.full()) {
            // 스택에 공간이 있으면 추가
            stack.push(current);
        } else {
            // 스택이 가득 찼으면 현재 숫자 버림
            // (이 경우도 제거로 카운트)
            removed++;
        }
    }
    
    return stack.get_result();
}

/*
 * ============================================================================
 * main() - 프로그램 진입점
 * ============================================================================
 * 
 * [입력]
 * - N: 숫자 문자열
 * - K: 제거할 숫자 개수
 * 
 * [출력]
 * - 최대 수
 */
int main() {
    try {
        string N;
        int K;
        
        cin >> N >> K;
        
        if (N.empty()) {
            throw runtime_error("N empty");
        }

        string result = find_max_number(N, K);
        cout << result << endl;
        
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
