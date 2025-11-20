/*
* Recursive Thinking
현재 위치에서 이미 가본 곳을 다시 지나지 않고 출구까지 가는 경로가 있으려면
    1) 현재 위치가 출구이거나 혹은
    2) 이웃한 셀들 중 하나에서 이미 가본 곳(현재 위치도 포함)을 다시 지나지 않고 출구까지 가는 경로가 있거나
*/

// 수도 코드 2가지

/*
boolean findPath(x, y)
    if (x, y) is the exit { return true; }

    else{
        mark(x, y) as visited;
        for each neighbouring cell (x', y') of (x, y) do
            if (x', y') is a pathway cell and not visited
                if findPath(x', y') { return true; }
        return false;    
    }
*/
/*
boolean findPath(x, y){
    if (x, y) is either on the wall or a visited cell { return false; }
    else if (x, y) is the exit { return true; }
    else{
        mark (x, y) as a visited cell;
        for each neightbouring cell (x', y') of (x, y) do
            if findPath(x', y') { return true; }
        return false;    
    }    
}
*/

#include <stdio.h>
#include <stdbool.h>

int N = 8;
int maze[][8] = {
    {0, 0, 0, 0, 0, 0, 0, 1}, 
    {0, 1, 1, 0, 1, 1, 0, 1}, 
    {0, 0, 0, 1, 0, 0, 0, 1},
    {0, 1, 0, 0, 1, 1, 0, 0},
    {0, 1, 1, 1, 0, 0, 1, 1},
    {0, 1, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0, 1, 0, 0}
};

#define PATHWAY_COLOUR 0 
#define WALL_COLOUR 1
#define BLOCKED_COLOUR 2 // 이미 방문했으면서 출구까지의 경로상에 있지 않음이 밝혀진 cell
#define PATH_COLOUR 3 // 이미 방문했으면서 출구로 가는 경로가 될 가능성이 있는 cell

bool findMazePath(int x, int y){
    if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] != PATHWAY_COLOUR) { return false; }

    else if (x == N - 1 && y == N - 1){
        maze[x][y] = PATH_COLOUR;
        return true;
    }
    else{
        maze[x][y] = PATH_COLOUR;
        if (findMazePath(x - 1, y) || findMazePath(x, y + 1) || findMazePath(x + 1, y) || findMazePath(x, y - 1)) {
            return true;
        }
        maze[x][y] = BLOCKED_COLOUR;
        return false;
    }
}

void printMaze(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d\t", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int offset[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

// void printPath(int x, int y){
//     printf("(%d, %d)\n", x, y);
//     if (x == N - 1 && y == N - 1) { return; }

//     for (int dir = 0; dir < 4; dir++){
//         int nx = x + offset[dir][0];
//         int ny = y + offset[dir][1];
//         if (nx >= 0 && nx < N && ny >= 0 && ny < N && maze[nx][ny] == PATH_COLOUR){
//             printPath(nx, ny);
//             return;
//         }
//     }
//     printf("No Path");
// }

bool printPath(int x, int y, int px, int py){
    if (x < 0 || y < 0 || x >= N || y >= N) return false;
    if (maze[x][y] != PATH_COLOUR) return false;

    printf("(%d, %d)\n", x, y);
    if (x == N - 1 && y == N - 1) return true;

    for (int dir = 0; dir < 4; dir++){
        int nx = x + offset[dir][0];
        int ny = y + offset[dir][1];
        if (nx == px && ny == py) continue; // 바로 온 칸으로는 돌아가지 않음
        if (nx >= 0 && nx < N && ny >= 0 && ny < N && maze[nx][ny] == PATH_COLOUR){
            if (printPath(nx, ny, x, y)) return true;
        }
    }
    return false;
}

int main(void){
    printMaze();
    bool ok = findMazePath(0, 0);
    printf("Path found? %s\n\n", ok ? "Yes" : "No");
    printMaze();

    if (!printPath(0, 0, -1, -1)){
        printf("No Path\n");
    }

    return 0;
}