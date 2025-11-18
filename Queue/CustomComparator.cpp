#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template <typename T>
void pop_println(string rem, T& pq) {
    cout << rem << ": ";
    for (; !pq.empty(); pq.pop()) {cout << pq.top() << ' '; }
    cout << '\n';
}

typedef bool (*func) (const string, const string);

bool string_greater(const string l, const string r) {
    return l.length() > r.length() || l.length() == r.length() && l > r;
}

int main(void) {
    vector<string> data = {"animal", "drop", "and", "for", "bold", "clude"};

    struct Compare {
        bool operator() (const string l, const string r) const {
            return l.length() > r.length() || l.length() == r.length() && l > r;
        }
    };

    // priority_queue<string, vector<string>, string_greater> custom_priority_queue(string greater); // 틀렸음 string_greater함수는 타입이 아님

    // priority_queue<string, vector<string>, bool (*)(const string, const string)> custom_priority_queue(string_greater); // 위의 맞는 예시

    // priority_queue<string, vector<string>, func> custom_priority_queue(string_greater); // function pointer를 이용한 방법 // 매개 변수로 실제 함수의 이름명을 받아야 함

    priority_queue<string, vector<string>, Compare> custom_priority_queue; // function Object를 이용한 방법 훨씬 간단

    for (auto s : data) custom_priority_queue.push(s);

    pop_println("Custom Priority Queue", custom_priority_queue);

    // Using lambda to compare elements. // anonymous function
    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); }; // 2개의 정수를 받아서  
    priority_queue<int, vector<int>, decltype(cmp)> lambda_priority_queue(cmp);
    // priority_queue는 template을 생성하고 있는 것이니 <> 안에는 타입 명이 들어가야 함 => 함수 자체가 들어가는 것이 아니라 함수의 type명이 들어가야 함
    // 해당 lambda 함수의 type명이 원래는 bool (*)(int, int)인데 decltype(변수 or 함수)를 이용하여서 type명을 자동적으로 계산해줌


    vector<int> nums = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};
    for (int n : nums) lambda_priority_queue.push(n);

    pop_println("lambda_priority_queue", lambda_priority_queue);

    return 0;
}