/*
이미 방문한 위치에는 표시를 해서 무한루프를 방지한다.
현재 위치에서 일정한 규칙으로 다음 위치로 이동한다.
-북, 동, 남, 서의 순서로 검사하여, 그 방향으로 갈 수 있으면, 즉 아직 안 가본 위치면서 벽이 아니면 그 방향으로 간다.
아무 방향으로도 갈 수 없으면 그 위치에 오기 직전 위치로 되돌아 간다. 
*/
#include <iostream>
#include <fstream>
#include <stack>
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

bool movable(Position pos, int dir){
    int x = pos.x + offset[dir][0];
    int y = pos.y + offset[dir][1];
    return x >= 0 && x < n && y >= 0 && y < n && maze[x][y] == PATH;
}

Position move_to(Position pos, int dir){
    return Position(pos.x + offset[dir][0], pos.y + offset[dir][1]);
}

int main(void){
    read_maze();
    stack<Position> s;      // 위치를 저장할 스택
    Position cur(0, 0);     // 현재 위치를 표현
    while(true){
        maze[cur.x][cur.y] = VISITED;   // 현재 위치를 방문했다고 표시
        if (cur.x == n - 1 && cur.y == n - 1){  // 현재 위치가 출구라면
            cout << "Found the path." << endl;
            break;
        }
        bool forwarded = false;
        for (int dir = 0; dir < 4; dir++){
            if (movable(cur, dir)){
                s.push(cur);
                cur = move_to(cur, dir);
                forwarded = true;
                break;
            }
        }
        if(!forwarded){
            maze[cur.x][cur.y] = BACKTRACKED;
            if (s.empty()){
                cout << "No path exists." << endl;
                break;
            }
            cur = s.top(), s.pop();
        }
    }
    print_maze();
}