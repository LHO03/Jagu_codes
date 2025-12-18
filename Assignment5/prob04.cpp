#include <iostream>
using namespace std;

const int MAX = 1000;

int ignite[MAX];

int floor(int end, int K){
	if (end < 0) { return -1; }

	if (ignite[end] > K) return floor(end - 1, K);
	if (ignite[end] < K) return ignite[end];
}

int ceiling(int start, int end, int K) {
	if (start > end) { return -1; }

	if (ignite[start] < K) return ceiling(start + 1, end, K);
	if (ignite[start] >= K) return ignite[start];
}

int main(void){
	int N, K;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> ignite[i];
	}
	cin >> K;

	cout << endl << floor(N - 1, K) << endl << ceiling(0, N - 1, K);
	return 0;
}