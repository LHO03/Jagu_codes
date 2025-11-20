/*
* Recursive Thinking
현재 픽셀이 이 속한 blob의 크기를 카운트하려면
    현재 픽셀이 image color가 아니라면
        0을 반환한다
    현재 픽셀이 image color라면
        먼저 현재 픽셀을 카운트한다 (count = 1)
        현재 픽셀이 중복 카운트되는 것을 방지하기 위해 다른 색으로 칠한다.
        현재 픽셀이 이웃한 모든 픽셀들에 대해서
           그 픽셀이 속한 blob의 크기를 카운트하여 카운터에 더해준다.
        카운터를 반환한다.

* Counting cells in a Blob
Algorithm for countCells(x, y)
if the pixel (x, y) is outside the grid
    the result is 0;
else if pixel (x, y) is not an image pixel or already counted
    the result is 0;
else
    set the colour of the pixel (x, y) to a red colour;
    the result is 11 plus the number of cells in each piece of 
      the blob that includes a nearest neighbour;
*/
#define BACKGROUND_COLOR 0
#define IMAGE_COLOR 1
#define ALREADY_COUNTED 2
#include <stdio.h>

int N = 8;
int grid[][8] = {
    {1, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 1, 0, 0, 1, 0, 0},
    {1, 1, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 1},
    {0, 1, 1, 0, 0, 1, 1, 1}
};

int countCells(int x, int y){
    if (x < 0 || x >= N || y < 0 || y >= N || grid[x][y] != IMAGE_COLOR) return 0;

    grid[x][y] = ALREADY_COUNTED;
    return 1 + countCells(x - 1, y + 1) + countCells(x, y + 1) +
    countCells(x + 1, y + 1) + countCells(x - 1, y) + 
    countCells(x + 1, y) + countCells(x - 1, y - 1) + 
    countCells(x, y - 1) + countCells(x + 1, y - 1);
}


// int countCells(int x, int y){
//     if (x < 0 || x >= N || y < 0 || y >= N || grid[x][y] != IMAGE_COLOR) return 0;
    
//     else if (grid[x][y] != IMAGE_COLOR) return 0; 
//     // 0이거나 이미 count된 color이거나
    
//     else{
//         grid[x][y] = ALREADY_COUNTED;
//         return 1 + countCells(x - 1, y + 1) + countCells(x, y + 1) +
//         countCells(x + 1, y + 1) + countCells(x - 1, y) + 
//         countCells(x + 1, y) + countCells(x - 1, y - 1) + 
//         countCells(x, y - 1) + countCells(x + 1, y - 1);
//     }
// }

void print_grid(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d\t", grid[i][j]);
        }
        printf("\n\n");
    }
}

int main(void){
    print_grid();
    printf("\n");
    int totalCount = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (grid[i][j] == IMAGE_COLOR){
                totalCount += countCells(i, j);
            }
        }
    }
    printf("%d", totalCount);
    return 0;
}