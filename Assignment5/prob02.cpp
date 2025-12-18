#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
using namespace std;

const int PATH = 0;
const int WALL = 1;
const int VISITED = 2;
const int BACKTRACKED = 3;

int N;
vector<vector<int>> maze;

void read_maze(){
    ifstream maze_map("input2.txt");

    maze_map >> N;
    maze.assign(N, vector<int>(N));

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            maze_map >> maze[i][j];
        }
    }
    maze_map.close();
}

void print_maze(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cout << maze[i][j] << '\t';
        }
        cout << endl << endl;
    }
}

class Status{
public:
    int x, y, count, dir;
    bool is_backtrack;  // 백트래킹 표시용
    Status() = default;
    Status(int x, int y, int c, int d, bool bt = false) : x(x), y(y), count(c), dir(d), is_backtrack(bt) {}
};

int offset[4][2] = {
    {-1, 0}, {0, 1},
    {1, 0}, {0, -1}
};

bool can_go(int x, int y){
    return (x >= 0 && y >= 0 && x < N && y < N && maze[x][y] == PATH);
}

int count_branch(){
    int min_branch = INT_MAX;    
    stack<Status> branch;

    maze[0][0] = VISITED;    
    for (int dir = 0; dir < 4; dir++){
        int nx = offset[dir][0];
        int ny = offset[dir][1];
        if (can_go(nx, ny)) { branch.push(Status(nx, ny, 0, dir, false)); }
    }
    
    while(!branch.empty()){
        Status cur = branch.top();
        branch.pop();
        
        // 백트래킹 처리
        if (cur.is_backtrack){
            maze[cur.x][cur.y] = PATH;
            continue;
        }
        
        // 가지치기: 이미 더 좋은 경로를 찾았으면 스킵
        if (cur.count >= min_branch) continue;
        
        // 방문 표시
        maze[cur.x][cur.y] = VISITED;
        
        // 목적지 도착
        if (cur.x == N - 1 && cur.y == N - 1){
            min_branch = min(min_branch, cur.count);
            maze[cur.x][cur.y] = PATH;  // 다른 경로를 위해 복원
            continue;
        }
        
        // 백트래킹을 위한 표시 추가
        branch.push(Status(cur.x, cur.y, cur.count, cur.dir, true));
        
        // 4방향 탐색
        for (int next_dir = 0; next_dir < 4; next_dir++){
            int nx = cur.x + offset[next_dir][0];
            int ny = cur.y + offset[next_dir][1];
            
            if (!can_go(nx, ny)) continue;
            
            // 꺾임 계산
            int new_count = cur.count + (cur.dir != next_dir ? 1 : 0);
            
            // 가지치기
            if (new_count < min_branch) { branch.push(Status(nx, ny, new_count, next_dir, false)); }
        }
    }

    if (min_branch == INT_MAX){
        cout << "No path exists";
        return 0;
    } else {
        cout << min_branch << '\n';
        return min_branch;
    }
}

int main(){
    read_maze();
    count_branch();
    return 0;
}