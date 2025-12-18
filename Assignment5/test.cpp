#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// queue에서 실제로 제거하며 행운수 생성
vector<int> generateLuckyNumbers(int maxN) {
    // 1단계: 홀수만 queue에 넣기
    queue<int> q;
    for (int i = 1; i <= maxN; i += 2) {
        q.push(i);
    }
    
    // 2단계부터: step = 3, 4, 5, ... 간격으로 제거
    int step = 3;
    while (step <= (int)q.size()) {
        int size = q.size();
        int pos = 1;  // 현재 위치 (1-indexed)
        
        for (int i = 0; i < size; i++) {
            int val = q.front();
            q.pop();
            
            // pos가 step의 배수가 아니면 다시 queue에 넣음
            if (pos % step != 0) {
                q.push(val);
            }
            pos++;
        }
        step++;
    }
    
    // queue의 내용을 vector로 변환
    vector<int> result;
    while (!q.empty()) {
        result.push_back(q.front());
        q.pop();
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> lucky = generateLuckyNumbers(n);
    
    bool found = false;
    for (int x : lucky) {
        if (x == n) {
            found = true;
            break;
        }
    }
    
    if (found) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    
    return 0;
}