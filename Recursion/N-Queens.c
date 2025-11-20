/*
*Desifn Recursion 
return-type queens(arguments){  // 매개변수는 내가 현재 트리의 어떤 노드에 있는 지를 지정해야 한다.
    if non-promising(infeasible 실행 불가능한)
        report failure and return;
    else if success
        report answer and return;
    else
        visit children recursively;
}
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define N 4

int cols[N + 1];

bool promising(int level){
    for (int i = 1; i < level; i++){
        if (cols[i] == cols[level]) return false; // 같은 열에 있는 경우

        else if (level - i == abs(cols[level] - cols[i])) return false; // 같은 대각선에 놓인 경우
    }
    return true;
}

bool queens( int level ){
    if (!promising(level)) return false;

    else if (level == N){
        for (int i =  1; i <= N; i++){
            printf("(%d, %d)\n", i, cols[i]);
        }
        return true;
    } 

    for (int i = 1; i <= N; i++){
        cols[level + 1] = i;
        if (queens(level + 1)) return true;
    }
    return false;
}

int main(void){
    queens(0);
    return 0;
}