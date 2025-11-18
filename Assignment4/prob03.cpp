#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

const int MAX_SIZE = 1000000;

class Stack {
private:
    char arr[MAX_SIZE];
    int top_index = -1;
    int max_capacity;
    
public:
    Stack() = default;
    Stack(int size) : max_capacity(size) {}
    
    bool empty() {return top_index == -1;}
    bool full() {return top_index == MAX_SIZE - 1;}

    void push(char x) {
        if (full()) {
            throw runtime_error("Full");
        }
        arr[++top_index] = x;
    }

    void pop() {
        if (empty()) {
            throw runtime_error("Empty");
        }
        top_index--;
    }
    
    char top() {
        if (empty()) {
            throw runtime_error("Empty");
        }
        return arr[top_index];
    }

    int size() {
        return top_index + 1;
    }
    
    string get_result() {
        string result = "";
        for (int i = 0; i <= top_index; i++) {
            result += arr[i];
        }
        return result;
    }
};

string find_max_number(string N, int K) {
    int n = N.length();
    int toKeep = n - K;
    
    if (K >= n) {
        throw runtime_error("Cannot remove");
    }
    if (K < 0) {
        throw runtime_error("K negative");
    }
    
    Stack stack(toKeep);
    int removed = 0;
    
    for (int i = 0; i < n; i++) {
        char current = N[i];
        
        while (!stack.empty() && stack.top() < current && removed < K && 
        stack.size() + (n - i) > toKeep) {
            stack.pop();
            removed++;
        }
        
        if (!stack.full()) {
            stack.push(current);
        } else {
            removed++;
        }
    }
    
    return stack.get_result();
}

int main() {
    try {
        string N;
        int K;
        
        cin >> N >> K;
        
        if (N.empty()) {
            throw runtime_error("N empty");
        }

        string result = find_max_number(N, K);
        cout << result << endl;
        
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}