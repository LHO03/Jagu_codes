#include <iostream>
using namespace std;

const int MAX = 1000;
int ignite[MAX];

int two_someplace(int start, int end, int K){
    if (start >= end) return 0;

    if (ignite[start] + ignite[end] == K){
        return 1 + two_someplace(start + 1, end - 1, K);   
    } 
    if (ignite[start] + ignite[end] < K){
        return two_someplace(start + 1, end, K);
    } 
    else {
        return two_someplace(start, end - 1, K);
    }
}

int main(void){
    int N, K;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> ignite[i];
    }
    cin >> K;
    cout << two_someplace(0, N - 1, K);
}