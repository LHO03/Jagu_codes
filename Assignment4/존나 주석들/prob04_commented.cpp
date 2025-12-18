/**
 * 문제 4: 이미지 컴포넌트 크기 계산
 * 
 * [문제 설명]
 * - N×N 흑백 이미지가 주어짐 (0: 배경, 1: 이미지 픽셀)
 * - 8방향(상하좌우 + 대각선)으로 연결된 픽셀들을 하나의 컴포넌트로 간주
 * - 각 컴포넌트의 크기(픽셀 수)를 계산하여 오름차순으로 출력
 * 
 * [예시]
 * 이미지에 5개의 컴포넌트가 있고 크기가 각각 13, 42, 9, 29, 15이면
 * 출력: 9 13 15 29 42 (오름차순)
 * 
 * [알고리즘: 스택 기반 DFS (Flood Fill)]
 * - 격자를 스캔하며 아직 방문하지 않은 1을 찾음
 * - 찾으면 새 컴포넌트 시작, DFS로 연결된 모든 1을 탐색
 * - 탐색한 픽셀 수가 컴포넌트 크기
 * 
 * [제약사항]
 * - 순환(재귀) 사용 금지, 반드시 스택으로 구현
 * - STL stack은 사용 가능 (문제에서 별도 언급 없음)
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

/**
 * 8방향 델타 배열
 * 
 * [역할] 현재 위치에서 8방향 이웃의 상대 좌표
 * 
 * [방향 순서]
 * - (dy, dx) 쌍으로 표현
 * - 상좌(-1,-1), 상(-1,0), 상우(-1,1)
 * - 좌(0,-1), 우(0,1)
 * - 하좌(1,-1), 하(1,0), 하우(1,1)
 * 
 * [4방향 vs 8방향]
 * - 4방향: 상하좌우만 연결
 * - 8방향: 대각선도 연결 (이 문제에서 사용)
 */
const int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

/**
 * component_sizes(grid)
 * 
 * [역할] 격자에서 모든 컴포넌트의 크기를 계산
 * 
 * [매개변수]
 * - grid: N×N 2D 벡터 (0: 배경, 1: 이미지)
 * 
 * [반환값]
 * - 각 컴포넌트의 크기를 담은 벡터
 * 
 * [알고리즘: 스택 기반 DFS (반복적 Flood Fill)]
 * 
 * Flood Fill이란?
 * - 연결된 영역을 "채우는" 알고리즘
 * - 그림판의 "페인트 통" 도구와 같은 원리
 * - 시작점에서 연결된 모든 같은 값의 셀을 탐색
 * 
 * 재귀 DFS vs 스택 DFS:
 * - 재귀 DFS: 함수 호출 스택 사용, 코드 간결
 * - 스택 DFS: 명시적 스택 사용, 스택 오버플로우 방지
 * - 이 문제에서는 재귀 금지이므로 스택 DFS 사용
 * 
 * [동작 과정]
 * 
 * 1. 전체 격자 스캔:
 *    - 방문하지 않은 1을 찾으면 새 컴포넌트 시작
 * 
 * 2. 컴포넌트 탐색 (스택 DFS):
 *    a. 시작 셀을 스택에 push, 방문 표시
 *    b. 스택이 빌 때까지:
 *       - pop하여 현재 셀 가져옴
 *       - 컴포넌트 크기 증가
 *       - 8방향 이웃 검사
 *       - 유효한 미방문 1이면 push, 방문 표시
 *    c. 컴포넌트 크기 저장
 * 
 * 3. 모든 컴포넌트 크기 반환
 * 
 * [스택 DFS의 핵심]
 * - 스택에 push할 때 방문 표시 (중복 방지)
 * - pop할 때 실제 처리 (크기 카운트)
 * 
 * [시간 복잡도]
 * - O(N²): 각 셀을 최대 한 번 방문
 * 
 * [공간 복잡도]
 * - O(N²): visited 배열 + 스택 (최악의 경우 모든 셀)
 */
vector<int> component_sizes(const vector<vector<int>>& grid) {
    int N = grid.size();
    
    // 방문 여부를 추적하는 2D 배열
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    
    // 각 컴포넌트의 크기를 저장할 벡터
    vector<int> comps;
    
    // ===== 전체 격자 스캔 =====
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // 아직 방문하지 않은 이미지 픽셀(1) 발견 → 새 컴포넌트
            if (grid[i][j] == 1 && !visited[i][j]) {
                int comp_size = 0;           // 현재 컴포넌트 크기
                stack<pair<int, int>> st;    // DFS용 스택
                
                // ===== 시작점 처리 =====
                st.push({i, j});
                visited[i][j] = true;  // push할 때 방문 표시 (중요!)
                
                // ===== 스택 기반 DFS =====
                while (!st.empty()) {
                    // 현재 셀 가져오기
                    pair<int, int> cur = st.top();
                    st.pop();
                    
                    int y = cur.first;
                    int x = cur.second;
                    comp_size++;  // 컴포넌트 크기 증가
                    
                    // ===== 8방향 이웃 검사 =====
                    for (int dir = 0; dir < 8; dir++) {
                        int ny = y + dy[dir];
                        int nx = x + dx[dir];
                        
                        // 조건 검사:
                        // 1. 범위 체크 (0 <= ny, nx < N)
                        // 2. 이미지 픽셀인지 (grid[ny][nx] == 1)
                        // 3. 미방문인지 (!visited[ny][nx])
                        if (ny >= 0 && ny < N && nx >= 0 && nx < N &&
                            grid[ny][nx] == 1 && !visited[ny][nx]) {
                            st.push({ny, nx});
                            visited[ny][nx] = true;  // push할 때 방문 표시!
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

/**
 * main()
 * 
 * [동작]
 * 1. 파일 또는 표준 입력에서 데이터 읽기
 * 2. 테스트 케이스 개수 T 처리
 * 3. 각 테스트 케이스에 대해:
 *    a. N×N 격자 입력
 *    b. 컴포넌트 크기 계산
 *    c. 오름차순 정렬 후 출력
 */
int main() {
    // 파일 입력 시도, 실패하면 표준 입력 사용
    ifstream fin("input.txt");
    istream& input = fin.is_open() ? fin : cin;
    
    int T;  // 테스트 케이스 개수
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

/**
 * [스택 DFS vs 재귀 DFS 비교]
 * 
 * 재귀 DFS (사용 금지):
 * void dfs(int y, int x) {
 *     visited[y][x] = true;
 *     count++;
 *     for (int dir = 0; dir < 8; dir++) {
 *         int ny = y + dy[dir];
 *         int nx = x + dx[dir];
 *         if (valid(ny, nx) && grid[ny][nx]==1 && !visited[ny][nx])
 *             dfs(ny, nx);
 *     }
 * }
 * 
 * 스택 DFS (이 문제의 해법):
 * - 위 코드를 명시적 스택으로 변환
 * - 함수 호출 → stack.push
 * - 함수 반환 → stack.pop
 * 
 * [방문 표시 시점의 중요성]
 * 
 * 잘못된 방법: pop할 때 방문 표시
 * - 같은 셀이 여러 번 push될 수 있음
 * - 중복 카운트 발생!
 * 
 * 올바른 방법: push할 때 방문 표시
 * - 각 셀이 최대 한 번만 push됨
 * - 정확한 카운트 보장
 * 
 * [8방향 연결 시각화]
 * 
 *   (-1,-1) (-1,0) (-1,1)
 *   (0,-1)  (y,x)  (0,1)
 *   (1,-1)  (1,0)  (1,1)
 * 
 * 예시 이미지:
 *   1 0 1 0
 *   0 1 0 0
 *   1 0 0 1
 *   0 0 1 1
 * 
 * 컴포넌트 1: (0,0), (1,1), (2,0) → 크기 3 (대각선으로 연결)
 * 컴포넌트 2: (0,2) → 크기 1
 * 컴포넌트 3: (2,3), (3,2), (3,3) → 크기 3
 */
