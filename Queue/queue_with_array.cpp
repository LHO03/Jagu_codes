#include <iostream>
#include <vector>
using namespace std;

template <typename T> class ArrayQueue {
private:
    T *array = nullptr;
    int init_capacity = 4;
    int capacity;
    int size_queue = 0, head = 0, tail = -1;

    void clear_queue() {
        delete [] array;
        size_queue = 0;
        head = 0;
        tail = -1;
    }

    void copy_from(const ArrayQueue<T> &que) {
        int j = que.head;
        for (int i = 0; i < que.size(); i++) {
            push(que.array[j]);
            j = (j + 1) % que.capacity;
        }
    }
    void init(int cap) {
        array = new T [cap];
        capacity = cap;
    }

    bool full() { return size_queue == capacity; }

    void reallocate(int cap) {
        T *tmp = new T [cap];
        int j = head;
        for (int i = 0; i < size_queue; i++) {
            tmp[i] = array[j];
            j = (j + 1) % capacity;
        }
        delete [] array;
        head = 0;
        tail = size_queue - 1;
        array = tmp;
        capacity = cap;
    }

public:
    ArrayQueue() { init(init_capacity); }
    ~ArrayQueue() { clear_queue(); }
    ArrayQueue(const ArrayQueue<T> &que) {
        init(que.capacity);
        copy_from(que);
    }
    ArrayQueue<T> &operator=(const ArrayQueue<T> &que) {
        head = 0, tail = -1, size_queue = 0;
        copy_from(que);
        return *this;
    }
    void push(T item) {
        if (full()) reallocate(capacity * 2);
        tail = (tail + 1) % capacity;
        array[tail] = item;
        size_queue++;
    }
    void pop() {
        if (empty()) throw runtime_error("pop while queue empty");
        head = (head + 1) % capacity; // 실제로 삭제할 필요 없이 head => tail까지만 데이터가 있는 것이니 그저 head만 1 증가시켜주면 된다.
        size_queue--;
    }
    T front() {
        if (empty()) throw runtime_error("fron while queue empty.");
        return array[head];
    }
    bool empty() { return size_queue == 0; }
    int size() const { return size_queue; } // const의 의미: size()라는 member 함수가 해당 객체의 data member의 값을 수정하지 않는다.
                                            // const선언을 안 하면 compile error? => copy constructor => copy_from가 매개변수를 const로 받기 때문에 
                                            // + 안에서 que.size()를 호출하기 때문 
};

int main(void){
    vector<int> v { 1, 2, 3, 4, 5};
    ArrayQueue<int> que;
    for (int d : v) que.push(d);
    ArrayQueue<int> que2(que);
    ArrayQueue<int> que3;
    que3 = que2;

    while(!que.empty()) { cout << que.front() << ' '; que.pop(); }
    cout << endl;

    while(!que2.empty()) { cout << que2.front() << ' '; que2.pop(); }
    cout << endl;
    
    while(!que3.empty()) { cout << que3.front() << ' '; que3.pop(); }
    cout << endl;

    return 0;
}