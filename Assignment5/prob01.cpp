#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

const int GRASS = -1;
const int BLOCK = 1;
const int LAND  = 0;

int N;
int MAX_YEAR;
vector<vector<int>> ground;

int offset[4][2] = {
    {-1, 0}, {0, 1},
    {1, 0}, {0, -1}
};

void read_ground() {
    ifstream groundmap("input1.txt");

    groundmap >> N;
    ground.assign(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            groundmap >> ground[i][j];
        }
    }

    groundmap >> MAX_YEAR;
    groundmap.close();
}

void result(int x, int y) {
    ground[x][y] = 0;   // 초기 위치를 0으로 지정하기 위해서
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << ground[i][j] << '\t';
        }
        cout << endl << endl;
    }
}

bool can_grow(pair<int,int> &pos, int dir, int year) {
    if (year >= MAX_YEAR) return false;

    int x = pos.first  + offset[dir][0];
    int y = pos.second + offset[dir][1];

    return (x >= 0 && y >= 0 && x < N && y < N && ground[x][y] == LAND);
}

pair<int,int> grow_to(pair<int,int> &pos, int dir) {
    return pair<int,int>(pos.first + offset[dir][0], pos.second + offset[dir][1]);
}

struct Status{
    int x;
    int y;
    int year;
};

int countGrass(int x, int y) {
    queue<Status> grass;
    grass.push({x, y, 0});
    ground[x][y] = GRASS;
    int total_grass = 1;

    while (!grass.empty()) {
        Status cur = grass.front();
        grass.pop();

        pair<int,int> cur_pos(cur.x, cur.y);
        for (int dir = 0; dir < 4; dir++) {
            if (can_grow(cur_pos, dir, cur.year)) {
                pair<int,int> nx = grow_to(cur_pos, dir);
                ground[nx.first][nx.second] = cur.year + 1;
                grass.push({nx.first, nx.second, cur.year + 1});
                total_grass++;
            }
        }
    }

    return total_grass;
}

int main(void) {
    read_ground();

    int x, y;
    cin >> x >> y;

    cout << countGrass(x, y) << endl;
    result(x, y);

    return 0;
}
