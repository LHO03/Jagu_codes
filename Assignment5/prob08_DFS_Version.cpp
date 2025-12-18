#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// ============ 전역 상수 ============
const int MAX = 16;
const int EMPTY = 0;      // 빈 칸
const int OCCUPIED = 1;   // 다른 말이 있는 칸 (장애물)

// ============ 위치 구조체 ============
struct Position {
    int x, y;
    Position() = default;
    Position(int x, int y) : x(x), y(y) {}
};

// ============ 전역 변수 ============
int N;                          // 보드 크기
int board[MAX][MAX];            // 장기판
bool visited[MAX][MAX];         // 방문 여부
Position start_pos, goal_pos;   // 시작/목표 위치

// 방향 배열 (북, 동, 남, 서)
int offset[4][2] = {
    {-1, 0},  // 북 (위)
    {0, 1},   // 동 (오른쪽)
    {1, 0},   // 남 (아래)
    {0, -1}   // 서 (왼쪽)
};

// ============ 파일 입력 함수 ============
void read_board() {
    ifstream fin("input8.txt");
    fin >> N;
    
    // 보드 N×N 읽기
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> board[i][j];
        }
    }
    
    // 시작 좌표, 도착 좌표 읽기
    fin >> start_pos.x >> start_pos.y;
    fin >> goal_pos.x >> goal_pos.y;
    fin.close();
}

// ============ 범위 체크 함수 ============
bool in_range(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

// ============ 포 이동 가능 위치 계산 함수 ============
// 주어진 위치 cur에서 dir 방향으로 포 규칙에 따라
// 이동 가능한 모든 착지 위치를 destinations 벡터에 저장
void get_cannon_moves(Position cur, int dir, vector<Position>& destinations) {
    int dx = offset[dir][0];
    int dy = offset[dir][1];
    
    int nx = cur.x + dx;
    int ny = cur.y + dy;
    
    // [1단계] 첫 번째 장애물(1)을 찾을 때까지 빈 칸을 지나감
    // 포는 반드시 하나의 말을 건너뛰어야 이동 가능
    while (in_range(nx, ny) && board[nx][ny] == EMPTY) {
        nx += dx;
        ny += dy;
    }
    
    // 범위를 벗어났거나 장애물을 찾지 못한 경우 이동 불가
    if (!in_range(nx, ny) || board[nx][ny] != OCCUPIED) {
        return;
    }
    
    // [2단계] 장애물을 건너뛴 후, 두 번째 장애물을 만나기 전까지의
    // 모든 빈 칸이 착지 가능한 위치
    nx += dx;
    ny += dy;
    
    while (in_range(nx, ny) && board[nx][ny] == EMPTY) {
        destinations.push_back(Position(nx, ny));
        nx += dx;
        ny += dy;
    }
}

// ============ 방문 배열 초기화 함수 ============
void init_visited() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = false;
        }
    }
}

// ============ 재귀 DFS 탐색 함수 ============
bool dfs_recursive(Position cur) {
    // 목표 위치 도달 시 성공
    if (cur.x == goal_pos.x && cur.y == goal_pos.y) {
        return true;
    }
    
    // 네 방향으로 포 이동 시도
    for (int dir = 0; dir < 4; dir++) {
        vector<Position> destinations;
        get_cannon_moves(cur, dir, destinations);
        
        // 해당 방향으로 착지 가능한 모든 위치 탐색
        for (int i = 0; i < destinations.size(); i++) {
            Position next = destinations[i];
            
            // 미방문 위치면 재귀 호출
            if (!visited[next.x][next.y]) {
                visited[next.x][next.y] = true;
                
                // 재귀 호출로 목표 도달 성공 시 즉시 반환
                if (dfs_recursive(next)) {
                    return true;
                }
            }
        }
    }
    
    // 이 경로로는 목표 도달 불가
    return false;
}

// ============ 메인 함수 ============
int main() {
    // 파일에서 보드 읽기
    read_board();
    
    // 방문 배열 초기화 및 시작 위치 방문 처리
    init_visited();
    visited[start_pos.x][start_pos.y] = true;
    
    // 재귀 DFS로 경로 탐색 후 결과 출력
    if (dfs_recursive(start_pos)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    
    return 0;
}