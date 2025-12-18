/**
 * 문제 3: K개의 숫자를 제거하여 최대 정수 만들기
 * 
 * [문제 설명]
 * - D자리 정수 N이 주어짐
 * - K개의 숫자(digit)를 제거하여 만들 수 있는 가장 큰 정수를 구함
 * 
 * [예시]
 * N = 442311, K = 2
 * → 4, 4, 2, 3, 1, 1 중 2개 제거
 * → 최대값: 4431 (2와 1 제거)
 * 
 * [알고리즘: 그리디 + 스택]
 * - 앞자리가 클수록 전체 값이 커짐
 * - 따라서 앞쪽에 큰 숫자가 오도록 해야 함
 * - 스택을 사용하여 단조 감소 수열을 유지하면서 최대값 생성
 * 
 * [핵심 아이디어]
 * - 현재 숫자가 스택 top보다 크면, 스택 top을 제거하는 것이 유리
 * - 제거 횟수가 K를 넘지 않는 범위에서 제거
 * 
 * [제약사항]
 * - STL stack 사용 금지, 직접 구현해야 함
 */

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

const int MAX_SIZE = 1000000;  // 최대 자릿수

/**
 * Stack 클래스 (문자용 스택 직접 구현)
 * 
 * [역할] 문자(숫자 digit)를 저장하는 스택
 * 
 * [특수 기능]
 * - get_result(): 스택의 모든 원소를 문자열로 반환
 * - full(): 결과 문자열 길이 제한용
 */
class Stack {
private:
    char arr[MAX_SIZE];      // 문자 저장 배열
    int top_index = -1;      // top 원소의 인덱스 (-1: 비어있음)
    int max_capacity;        // 최대 저장 가능 개수
    
public:
    Stack() = default;
    
    /**
     * Stack(size)
     * [역할] 최대 용량을 지정하여 스택 생성
     * [매개변수] size: 최대 저장 가능 개수 (결과 문자열 길이)
     */
    Stack(int size) : max_capacity(size) {}
    
    bool empty() { return top_index == -1; }
    bool full() { return top_index == max_capacity - 1; }

    void push(char x) {
        if (full()) {
            throw runtime_error("Full");
        }
        arr[++top_index] = x;  // 전위 증가: 먼저 증가 후 저장
    }

    void pop() {
        if (empty()) {
            throw runtime_error("Empty");
        }
        top_index--;
    }
    
    char top() {
        if (empty()) {
            throw runtime_error("Empty");
        }
        return arr[top_index];
    }

    int size() {
        return top_index + 1;
    }
    
    /**
     * get_result()
     * [역할] 스택의 모든 원소를 bottom부터 top까지 문자열로 반환
     * [반환] 스택에 저장된 숫자들을 이어붙인 문자열
     */
    string get_result() {
        string result = "";
        for (int i = 0; i <= top_index; i++) {
            result += arr[i];
        }
        return result;
    }
};

/**
 * find_max_number(N, K)
 * 
 * [역할] 문자열 N에서 K개의 숫자를 제거하여 최대값 생성
 * 
 * [매개변수]
 * - N: 원본 숫자 문자열
 * - K: 제거할 숫자 개수
 * 
 * [반환값]
 * - 최대값 문자열
 * 
 * [알고리즘: 그리디 + 단조 스택]
 * 
 * 그리디 전략:
 * - 가능한 한 앞자리에 큰 숫자를 배치
 * - 현재 숫자가 이전 숫자보다 크면, 이전 숫자를 제거하는 것이 유리
 * 
 * 단조 감소 스택 아이디어:
 * - 스택에는 가능한 한 큰 숫자들이 앞에 오도록 유지
 * - 하지만 제거 횟수(K)와 남길 개수(toKeep) 제한이 있음
 * 
 * [핵심 조건]
 * 스택 top을 pop할 조건:
 * 1. 스택이 비어있지 않음
 * 2. 스택 top < 현재 숫자 (현재 숫자가 더 큼)
 * 3. 아직 K개를 다 제거하지 않음 (removed < K)
 * 4. 스택 크기 + 남은 숫자 > toKeep (pop해도 toKeep개를 채울 수 있음)
 * 
 * [동작 과정]
 * 
 * 1. toKeep = n - K (최종적으로 남길 숫자 개수)
 * 
 * 2. 각 숫자 current에 대해:
 *    a. while 조건 만족하면 스택 pop (작은 숫자 제거)
 *    b. 스택이 가득 차지 않았으면 push
 *    c. 스택이 가득 찼으면 현재 숫자 버림 (removed 증가)
 * 
 * 3. 스택에 남은 숫자들을 문자열로 반환
 * 
 * [예시 실행]
 * N = "442311", K = 2, toKeep = 4
 * 
 * '4': 스택 비어있음, push → ['4']
 * '4': top('4') >= '4', push 안하고 → ['4','4']
 * '2': top('4') >= '2', push → ['4','4','2']
 * '3': top('2') < '3', pop, removed=1 → ['4','4']
 *      top('4') >= '3', push → ['4','4','3']
 * '1': top('3') >= '1', push → ['4','4','3','1'] (full!)
 * '1': 스택 full, removed=2 → 버림
 * 
 * 결과: "4431"
 * 
 * [시간 복잡도] O(N) - 각 숫자는 최대 한 번 push, 한 번 pop
 */
string find_max_number(string N, int K) {
    int n = N.length();
    int toKeep = n - K;  // 최종적으로 남길 숫자 개수
    
    // 예외 처리
    if (K >= n) {
        throw runtime_error("Cannot remove");
    }
    if (K < 0) {
        throw runtime_error("K negative");
    }
    
    Stack stack(toKeep);  // 최대 toKeep개만 저장 가능
    int removed = 0;      // 현재까지 제거한 숫자 개수
    
    for (int i = 0; i < n; i++) {
        char current = N[i];
        
        // ===== 그리디 제거: 스택 top이 현재보다 작으면 제거 =====
        // 조건 4번 설명: stack.size() + (n - i) > toKeep
        // - 현재 스택 크기 + 앞으로 올 숫자 개수 > 남길 개수
        // - 즉, pop해도 toKeep개를 채울 수 있다는 의미
        while (!stack.empty() && stack.top() < current && removed < K && stack.size() + (n - i) > toKeep) {
            stack.pop();
            removed++;
        }
        
        // ===== 현재 숫자 처리 =====
        if (!stack.full()) {
            // 스택에 여유가 있으면 push
            stack.push(current);
        } else {
            // 스택이 가득 찼으면 현재 숫자 버림
            removed++;
        }
    }
    
    return stack.get_result();
}

/**
 * main()
 * 
 * [동작]
 * 1. 숫자 문자열 N과 제거 개수 K 입력
 * 2. find_max_number 호출
 * 3. 결과 출력
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

/**
 * [알고리즘 정당성]
 * 
 * 왜 이 그리디가 최적인가?
 * 
 * 1. 앞자리의 중요성:
 *    - 9XXX > 8999 (앞자리가 크면 뒷자리와 무관하게 큼)
 *    - 따라서 가능한 한 앞자리에 큰 숫자를 배치해야 함
 * 
 * 2. 스택 pop 조건의 의미:
 *    - stack.top() < current: 현재 숫자가 더 큼
 *    - 이전 숫자를 제거하고 현재 숫자를 앞에 두는 것이 유리
 * 
 * 3. 제한 조건:
 *    - removed < K: 아직 제거 가능
 *    - stack.size() + (n-i) > toKeep: pop해도 충분한 숫자가 있음
 * 
 * [또 다른 예시]
 * N = "1234567890", K = 3, toKeep = 7
 * 
 * 과정:
 * '1' → [1]
 * '2' → 1<2, pop, removed=1 → [2]
 * '3' → 2<3, pop, removed=2 → [3]
 * '4' → 3<4, pop, removed=3 → [4]
 * '5' → 4<5, removed>=K, can't pop → [4,5]
 *       wait, removed=3=K 이므로 더 이상 pop 불가
 * '5' → [4,5]? 다시 계산...
 * 
 * 실제: 1→2→3→4 에서 1,2,3 제거 (K=3)
 * 결과: "4567890"
 */
