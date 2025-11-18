#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

// 8방향 델타 (상좌, 상, 상우, 좌, 우, 하좌, 하, 하우)
const int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// 스택 기반 반복 DFS로 컴포넌트 크기 계산
vector<int> component_sizes(const vector<vector<int>>& grid) {
    int N = grid.size();
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    vector<int> comps;
    
    // 전체 격자 스캔
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // 아직 방문하지 않은 1을 발견 → 새 컴포넌트 시작
            if (grid[i][j] == 1 && !visited[i][j]) {
                int comp_size = 0;
                stack<pair<int, int>> st;
                
                // 시작점을 스택에 push
                st.push({i, j});
                visited[i][j] = true;
                
                // 반복 DFS
                while (!st.empty()) {
                    pair<int, int> cur = st.top();
                    st.pop();
                    
                    int y = cur.first;
                    int x = cur.second;
                    comp_size++;
                    
                    // 8방향 이웃 검사
                    for (int dir = 0; dir < 8; dir++) {
                        int ny = y + dy[dir];
                        int nx = x + dx[dir];
                        
                        // 범위 체크 && 값이 1 && 미방문
                        if (ny >= 0 && ny < N && nx >= 0 && nx < N &&
                            grid[ny][nx] == 1 && !visited[ny][nx]) {
                            st.push({ny, nx});
                            visited[ny][nx] = true;
                        }
                    }
                }
                
                // 컴포넌트 크기 저장
                comps.push_back(comp_size);
            }
        }
    }
    
    return comps;
}

int main() {
    // 파일 입력 시도, 실패하면 표준 입력 사용
    ifstream fin("input.txt");
    istream& input = fin.is_open() ? fin : cin;
    
    int T;
    input >> T;
    
    while (T--) {
        int N;
        input >> N;
        
        // 격자 입력
        vector<vector<int>> grid(N, vector<int>(N));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                input >> grid[i][j];
            }
        }
        
        // 컴포넌트 크기 계산
        vector<int> comps = component_sizes(grid);
        
        // 오름차순 정렬
        sort(comps.begin(), comps.end());
        
        // 출력: 컴포넌트가 없으면 빈 줄, 있으면 크기들을 공백으로 구분
        for (int i = 0; i < comps.size(); i++) {
            if (i > 0) cout << ' ';
            cout << comps[i];
        }
        cout << '\n';
    }
    
    if (fin.is_open()) {
        fin.close();
    }
    
    return 0;
}