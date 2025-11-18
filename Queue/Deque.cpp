  #include <iostream>
  #include <deque>
  using namespace std;

  void showdq(deque<int> g) {
    deque<int>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) cout << '\t' << *it;
    cout << '\n';
  }

int main(void){
    deque<int> deq;
    deq.push_back(10);
    deq.push_front(20);
    deq.push_back(30);
    deq.push_front(15);
    showdq(deq);

    cout << deq.size() << endl;
    cout << deq.at(2) << endl;
    cout << deq.front() << endl;
    cout << deq.back() << endl;

    deq.pop_front();
    showdq(deq);

    deq.pop_back();
    showdq(deq);
    return 0;
}