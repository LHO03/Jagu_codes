#include <iostream>
using namespace std;

template <typename T> class ListQueue{
private:
    class Node{
    public:
        T data;
        Node* next;
        Node() = default;
        Node(T d, Node* p) : data(d), next(p) {}
    };

    Node* head = nullptr, *tail = nullptr;
    int size_queue = 0;

    void clear_list() {
        while(head != nullptr) {
            Node *p = head;
            head = head->next;
            delete p;
        }
        head = tail = nullptr;
        size_queue = 0;
    }

    void copy_from(const ListQueue<T> &que) {
        Node *p = que.head;
        while(p != nullptr) {
            push(p->data);
            p = p->next;
        }
    }

public:
    void push(T item){
        Node *p = new Node(item, nullptr);
        if(head == nullptr){
            head = tail = p;
        }
        else{
            tail->next = p;
            tail = p;
        }
        size_queue++;
    }
    void pop() {
        if (empty()) throw runtime_error("pop while queue empty!");
        Node *p = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete p;
        size_queue--;
    }
    bool empty() { return head == nullptr; }
    T front() {
        if (empty()) throw runtime_error("peek while queue empty!");
        
        return head->data;
    }
    int size() { return size_queue; }

    // void print() {
    //     Node *p = head;
    //     while(p!= nullptr){
    //         cout << p->data << " ";
    //         p = p->next;
    //     }
    //     cout << endl;
    // }

    ~ListQueue() { clear_list(); }
    ListQueue() = default;
    ListQueue(const ListQueue<T> &que) { copy_from(que); }

    ListQueue<T> &operator=(const ListQueue<T> &que) {
        clear_list();
        copy_from(que);
        return *this;
    }
};