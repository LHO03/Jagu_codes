/**
 * 문제 2: 남아있는 정수 개수 세기
 * 
 * [문제 설명]
 * - N개의 정수가 하나씩 순차적으로 주어짐
 * - 각 정수가 입력될 때마다:
 *   1. 이전에 입력된 정수들 중 자신보다 작거나 같은 것들을 모두 제거
 *   2. 자신을 추가
 *   3. 남아있는 정수들의 개수를 출력
 * 
 * [예시]
 * 입력: 3, 0, 3, 4, 1
 * 
 * 과정:
 * 3 입력 → [3] → 1개
 * 0 입력 → [3, 0] → 2개 (0 < 3이므로 3은 제거 안됨)
 * 3 입력 → 3 이하 제거 → [3] → 1개 (이전 3과 0 제거, 새 3 추가)
 * 4 입력 → 4 이하 제거 → [4] → 1개 (3 제거, 4 추가)
 * 1 입력 → [4, 1] → 2개 (1 < 4이므로 4는 제거 안됨)
 * 
 * 출력: 1 2 1 1 2
 * 
 * [알고리즘: 단조 감소 스택 (Monotonic Decreasing Stack)]
 * - 스택에는 항상 위에서 아래로 감소하는 순서 유지
 * - 새 원소 입력 시 자신보다 작거나 같은 원소들을 pop
 * - 결과적으로 스택에는 "현재까지 살아남은" 원소들만 존재
 * 
 * [제약사항]
 * - STL stack 사용 금지, 직접 구현해야 함
 */

#include <iostream>
using namespace std;

const int MAX_CAPACITY = 100;

/**
 * Stack 클래스 (스택 직접 구현)
 * 
 * [역할] 정수를 저장하는 스택 자료구조
 * 
 * [단조 스택으로 사용될 때의 특징]
 * - 스택의 원소들이 항상 특정 순서(증가/감소)를 유지
 * - 이 문제에서는 단조 감소 스택으로 사용
 */
class Stack{
public:
    int nums[MAX_CAPACITY];  // 정수 저장 배열
    int count = 0;           // 현재 저장된 원소 개수

    /**
     * empty()
     * [역할] 스택이 비어있는지 확인
     */
    bool empty() { return count == 0; }
    
    /**
     * full()
     * [역할] 스택이 가득 찼는지 확인
     */
    bool full() { return count == MAX_CAPACITY; }
    
    /**
     * push(x)
     * [역할] 스택에 원소 추가
     * [동작] nums[count] = x 후 count 증가
     */
    void push(int x){
        if (full()) throw runtime_error("Full");
        nums[count++] = x;
    }
    
    /**
     * pop()
     * [역할] 스택에서 top 원소 제거
     */
    void pop(){
        if (empty()) throw runtime_error("Pop_Empty");
        count--;
    }
    
    /**
     * top()
     * [역할] 스택의 top 원소 반환 (제거하지 않음)
     */
    int top(){
        if (empty()) throw runtime_error("Top_Empty");
        return nums[count - 1];
    }
    
    /**
     * size()
     * [역할] 현재 스택에 저장된 원소 개수 반환
     */
    int size(){
        return count;
    }
};

/**
 * main()
 * 
 * [알고리즘: 단조 감소 스택]
 * 
 * 단조 스택(Monotonic Stack)이란?
 * - 스택의 원소들이 항상 특정 순서를 유지하도록 관리
 * - 단조 감소: bottom에서 top으로 갈수록 값이 감소
 * - 단조 증가: bottom에서 top으로 갈수록 값이 증가
 * 
 * 이 문제에서의 동작:
 * - 새 원소가 들어올 때, 그보다 작거나 같은 원소들은 "의미 없음"
 * - 왜? 새 원소가 더 크거나 같으므로 이후에도 제거될 것이기 때문
 * - 따라서 바로 제거해도 결과에 영향 없음
 * 
 * [동작 과정]
 * 
 * 각 정수 num에 대해:
 * 1. while 루프: 스택 top이 num 이하인 동안 pop
 *    - 자신보다 작거나 같은 원소 제거
 * 2. push(num): 현재 원소 추가
 * 3. size() 출력: 남아있는 원소 개수
 * 
 * [예시 실행]
 * 입력: 5 4 3 2 1
 * 
 * 5 입력:
 *   스택: [] → 비어있으므로 while 안 돌음
 *   push(5) → [5]
 *   출력: 1
 * 
 * 4 입력:
 *   스택: [5] → top(5) > 4 → while 안 돌음
 *   push(4) → [5, 4]
 *   출력: 2
 * 
 * 3 입력:
 *   스택: [5, 4] → top(4) > 3 → while 안 돌음
 *   push(3) → [5, 4, 3]
 *   출력: 3
 * 
 * ... 계속
 * 
 * 최종 출력: 1 2 3 4 5 (점점 증가하는 수열의 경우)
 * 
 * [시간 복잡도]
 * - 전체: O(N)
 * - 각 원소는 최대 한 번 push, 한 번 pop
 * - amortized O(1) per operation
 */
int main(void){
    int n;
    cin >> n;

    int num;
    Stack nums;  // 단조 감소 스택
    
    for (int i = 0; i < n; i++){
        cin >> num;
        
        // ===== 단조 스택 유지 =====
        // 스택 top이 현재 num 이하인 동안 제거
        // 이 루프 후 스택에는 num보다 큰 원소들만 남음
        while(!nums.empty() && nums.top() <= num) {
            nums.pop();
        }

        // ===== 현재 원소 추가 =====
        nums.push(num);
        
        // ===== 결과 출력 =====
        // 현재 스택에 남아있는 원소 개수
        cout << nums.size() << " " << endl;
    }
    
    return 0;
}

/**
 * [단조 감소 스택 시각화]
 * 
 * 입력: 3, 0, 3, 4, 1
 * 
 * 단계  입력  비교 및 pop        push    스택 상태     출력
 * 1     3     (비어있음)         3       [3]          1
 * 2     0     3>0, pop 안함      0       [3,0]        2
 * 3     3     0<=3 pop, 3<=3 pop 3       [3]          1
 * 4     4     3<=4 pop           4       [4]          1
 * 5     1     4>1, pop 안함      1       [4,1]        2
 * 
 * 출력: 1 2 1 1 2
 * 
 * [스택이 유지하는 불변량]
 * - 스택의 bottom에서 top으로 갈수록 값이 감소
 * - 스택에 있는 원소들은 "아직 살아남은" 원소들
 * - 각 원소는 자신보다 큰 원소가 나오기 전까지 살아있음
 */
