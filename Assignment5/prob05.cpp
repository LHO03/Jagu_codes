#include <iostream>
#include <fstream>
using namespace std;

const int MAX_N = 100;
const int PATH = 0;
const int WALL = 1;

int n;
int maze[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

void read_maze(){
    ifstream maze_file("maze.txt");
    
    maze_file >> n;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            maze_file >> maze[i][j];
        }
    }

    maze_file.close();
}

int offset[4][2] = {
    {-1, 0}, {0, 1},
    {1, 0}, {0, -1}
};

int dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n || maze[x][y] == WALL || visited[x][y]) {
        return 0;
    }

    if (x == n - 1 && y == n - 1) {
        return 1;
    }
    
    visited[x][y] = true;
    
    // 네 방향으로 탐색하며 경로 수 합산
    int count = 0;
    for (int dir = 0; dir < 4; dir++) {
        int nx = x + offset[dir][0];
        int ny = y + offset[dir][1];
        count += dfs(nx, ny);
    }
    
    // 백트래킹: 다른 경로 탐색을 위해 방문 표시 해제
    visited[x][y] = false;
    
    return count;
}

int main() {
    read_maze();

    int answer = dfs(0, 0);
    cout << answer << '\n';
    
    return 0;
}