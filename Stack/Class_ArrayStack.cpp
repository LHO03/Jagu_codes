#include <iostream>
using namespace std;

const int MAX_CAPACITY = 100;

class ArrayStack{
    private:
    char stack[MAX_CAPACITY];
    int top_pos = -1;

    public:
    bool full(){
        return top_pos == MAX_CAPACITY - 1;
    }
    bool empty(){
        return top_pos == -1;
    }
    void push(char c){
        if (full()){
            throw runtime_error("stack full");
        }
        stack[++top_pos] = c;
    }
    void pop(){
        if (empty()){
            throw runtime_error("stack empty");
        }
        top_pos--;
    }
    char top(){
        if (empty()){
            throw runtime_error("stack empty");
        }
        return stack[top_pos];
    }
};

int main(void){
    ArrayStack s1, s2;
    s1.push('a');
    s2.push('x');
    cout << s1.top() << ' ' << s2.top() << endl;
    if (!s1.empty()) s1.pop();

    return 0;
}