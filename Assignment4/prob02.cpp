#include <iostream>
using namespace std;

const int MAX_CAPACITY = 100;

class Stack{
    public:
    int nums[MAX_CAPACITY];
    int count = 0;

    bool empty() {return count == 0;}
    bool full() {return count == MAX_CAPACITY;}
    void push(int x){
        if (full()) throw runtime_error("Full");
        nums[count++] = x;
    }
    void pop(){
        if (empty()) throw runtime_error("Pop_Empty");
        count--;
    }
    int top(){
        if (empty()) throw runtime_error("Top_Empty");
        return nums[count - 1];
    }
    int size(){
        return count;
    }
};

int main(void){
    int n;
    cin >> n;

    int num;
    Stack nums;
    for (int i = 0; i < n; i++){
        cin >> num;
        
        while(!nums.empty() && nums.top() <= num) nums.pop();

        nums.push(num);
        cout << nums.size() << " " << endl;
    }    
    return 0;
}