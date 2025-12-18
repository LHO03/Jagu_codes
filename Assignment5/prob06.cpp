#include <iostream>
#include <string>
using namespace std;

string s;
int N, K;

// pos: 현재 처리 중인 비트 위치
// flipsLeft: 앞으로 뒤집어야 할 비트 개수
void binaryDistance(int pos, int flipsLeft){
    // 뒤집을 개수가 음수면 불가능
    if (flipsLeft < 0 || (N - pos < flipsLeft)) {
        return;
    }
    
    // 모든 위치를 처리 완료
    if (pos == N) {
        if (flipsLeft == 0) {
            cout << s << '\n';
        }
        return;
    }
    
    // 1) 현재 위치를 뒤집지 않는 경우 (먼저 탐색 → 사전순 보장)
    binaryDistance(pos + 1, flipsLeft);
    
    // 2) 현재 위치를 뒤집는 경우
    // 비트 토글
    s[pos] = s[pos] == '0' ? '1' : '0';

    binaryDistance(pos + 1, flipsLeft - 1);
    
    // 백트래킹: 원상 복구
    s[pos] = s[pos] == '0' ? '1' : '0';

}

int main(){   
    cin >> s >> K;
    N = (int)s.size();
    
    binaryDistance(0, K);
    
    return 0;
}