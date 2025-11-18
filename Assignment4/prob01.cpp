#include <iostream>
#include <string>
using namespace std;

const int MAX_CAPACITY = 100;

class Paren {
private:
    int data[MAX_CAPACITY];
    int count = 0;
public:
    bool empty() { return count == 0; }
    bool full()  { return count == MAX_CAPACITY; }

    void push(int x) {
        if (full()) throw runtime_error("Full");
        data[count++] = x;
    }
    void pop() {
        if (empty()) throw runtime_error("Empty");
        --count;
    }
    int top() {
        if (empty()) throw runtime_error("Empty");
        return data[count - 1];
    }
};

// s를 스캔하며 여는 괄호엔 새로운 번호를 부여하고, 닫는 괄호는 스택 top의 번호를 사용
string paren_count(string& ex_input) {
    Paren stack;
    int next_id = 0;
    string result;
    bool first = true;

    for (char ch : ex_input) {
        if (ch == '(') {
            int id = ++next_id;
            stack.push(id);
            if (!first) result += ' ';
            result += to_string(id);
            first = false;
        } else if (ch == ')') {
            if (stack.empty()) throw runtime_error("Unmatched )");
            int id = stack.top();
            stack.pop();
            if (!first) result += ' ';
            result += to_string(id);
            first = false;
        }
    }
    return result;
}

int main() {
    string ex_input;
    getline(cin, ex_input);
    try {
        cout << paren_count(ex_input) << endl;
    } catch (runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
