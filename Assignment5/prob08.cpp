#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

const int MAX = 16;
const int SQUARE = 0;
const int UNIT = 1;

struct Position {
    int x, y;
    Position() = default;
    Position(int x, int y) : x(x), y(y) {}
};

int N;
int pan[MAX][MAX];
bool visited[MAX][MAX];
Position src, des;

int offset[4][2] = {
    {-1, 0}, {0, 1},
    {1, 0}, {0, -1}
};

void read_pan() {
    ifstream chess_pan("input8.txt");
    chess_pan >> N;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            chess_pan >> pan[i][j];
        }
    }
    
    chess_pan >> src.x >> src.y;
    chess_pan >> des.x >> des.y;
    chess_pan.close();
}


bool in_range(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

// 주어진 위치 cur에서 dir 방향으로 포 규칙에 따라 이동 가능한 모든 착지 위치를 destinations 벡터에 저장
void can_moves(Position cur, int dir, vector<Position>& destinations) {
    int dx = offset[dir][0];
    int dy = offset[dir][1];
    
    int nx = cur.x + dx;
    int ny = cur.y + dy;
    
    // 첫 번째 장애물(1)을 찾을 때까지 빈 칸을 지나감 포는 반드시 하나의 말을 건너뛰어야 이동 가능
    while (in_range(nx, ny) && pan[nx][ny] == SQUARE) {
        nx += dx;
        ny += dy;
    }
    
    // 범위를 벗어났거나 장애물을 찾지 못한 경우 이동 불가
    if (!in_range(nx, ny) || pan[nx][ny] != UNIT) {
        return;
    }
    
    // 장애물을 건너뛴 후, 두 번째 장애물을 만나기 전까지의 모든 빈 칸이 착지 가능한 위치
    nx += dx;
    ny += dy;
    
    while (in_range(nx, ny) && pan[nx][ny] == SQUARE) {
        destinations.push_back(Position(nx, ny));
        nx += dx;
        ny += dy;
    }
}

bool Po() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = false;
        }
    }
    
    queue<Position> q;
    q.push(src);
    visited[src.x][src.y] = true;
    
    while (!q.empty()) {
        Position cur = q.front();
        q.pop();
        
        // 네 방향으로 포 이동 시도
        for (int dir = 0; dir < 4; dir++) {
            vector<Position> destinations;
            can_moves(cur, dir, destinations);
            
            // 해당 방향으로 착지 가능한 모든 위치 처리
            for (int i = 0; i < destinations.size(); i++) {
                Position next = destinations[i];
                
                // 목표 위치 도달 시 즉시 종료
                if (next.x == des.x && next.y == des.y) {
                    return true;
                }
                
                // 미방문 위치면 큐에 추가
                if (!visited[next.x][next.y]) {
                    visited[next.x][next.y] = true;
                    q.push(next);
                }
            }
        }
    }

    return false;
}

int main() {
    read_pan();
    
    cout << (Po() ? "Yes" : "No");
    
    return 0;
}