/*
너비 우선 탐색으로 미로찾기
1. 하나의 큐를 만든다.
2. 위치 (0, 0)는 이미 방문한 위치임을 표시하고, 큐에 위치 (0, 0)을 넣는다.
3. 큐가 빌 때까지 다음을 반복한다.
    1. 큐에서 하나의 위치 p를 꺼낸다.
    2. p에서 한 칸 떨어진 위치들 중에서 이동 가능하면서 아직 방문하지 않은 모든 위치들을 방문된 위치임을 표시하고 큐에 넣는다.
    3. 만약 그 위치가 출구라면 종료한다.

*/
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

const int MAX_SIZE = 100;

const int PATH = 0;
const int WALL = 1;
const int VISITED = 2;
const int BACKTRACKED = 3;

int maze[MAX_SIZE][MAX_SIZE];
int n;

void read_maze() {
    ifstream mazefile("maze.txt");
    mazefile >> n;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            mazefile >> maze[i][j];
        }
    }
    mazefile.close();
}

void print_maze() {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

struct Position{
    int x, y;
    Position() = default;
    Position(int x, int y) : x(x), y(y) {}
};

int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool movable(pair<int, int> pos, int dir){
    int x = pos.first + offset[dir][0];
    int y = pos.second + offset[dir][1];
    return x >= 0 && x < n && y >= 0 && y < n && maze[x][y] == PATH;
}

pair<int, int> move_to(pair<int, int> pos, int dir){
    return pair<int, int>(pos.first + offset[dir][0], pos.second + offset[dir][1]);
}

int main(void){
    read_maze();
    queue<pair<int, int>> que;
    pair<int, int> cur(0, 0);
    maze[cur.first][cur.second] = -1; // 출발점에 방문 표시 * 추가 배열을 쓰지 않기 위하여 방문표시를 음수로 저장
    que.push(cur);

    while(!que.empty()) {
        cur = que.front();
        que.pop();
        for(int dir = 0; dir < 4; dir++) {
            if (movable(cur, dir)) {
                pair<int, int> p = move_to(cur, dir);
                maze[p.first][p.second] = maze[cur.first][cur.second] - 1; // 현재 cell의 방문 표시에 -1을 하여서 음수로 저장
                if (p.first == n - 1 && p.second == n - 1) {
                    cout << "Found the path." << endl;
                    print_maze();
                    return 0;
                }
                que.push(p);
            }
        }
    }
    cout << "No path exists." << endl;

    return 0;
}