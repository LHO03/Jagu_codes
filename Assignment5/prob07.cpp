#include <iostream>
using namespace std;

// pos: 현재 단계에서 n의 위치
// step: 현재 단계의 제거 간격
bool is_luckyNum(int pos, int step){
    if (step > pos) {
        return true;
    }
    
    if (pos % step == 0) {
        return false;
    }
    
    // 다음 단계의 새 index
    // 현재 index - 앞에서 제거된 원소 개수
    int newPos = pos - (pos / step);
    
    return is_luckyNum(newPos, step + 1);
}

bool is_lucky(int n){
    // 짝수는 행운수 X => 사전차단
    if (n % 2 == 0) {
        return false;
    }
    
    // n의 초기 index (홀수만 남은 수열에서의 위치)
    int pos = (n + 1) / 2;
    
    // 3의 배수부터 시작
    return is_luckyNum(pos, 3);
}

int main(){
    int n;
    cin >> n;
    
    cout << is_lucky(n) ? "yes" : "no";
    
    return 0;
}