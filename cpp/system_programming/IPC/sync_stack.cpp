// Implementation of stack data structure using parallel threads for pushing and
// popping operations of stack

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>

std::chrono::duration<int, std::micro> interval(100);
class Stack {
  int *arr;
  int maxlen;
  int top;
  std::mutex m1;
  std::condition_variable cv;

public:
  Stack(int len) : maxlen(len), top(-1) { arr = new int[maxlen]; }
  ~Stack() { delete[] arr; }
  void push(int val) {
    std::cout << "pushing:" << val << "\n";
    std::unique_lock<std::mutex> lk(m1);
    cv.wait(lk, [this] { return !isfull(); });
    arr[++top] = val;
    cv.notify_one();
  }

  int pop() {
    std::unique_lock<std::mutex> lk(m1);
    cv.wait(lk, [this] { return !isempty(); });
    int val = arr[top--];
    cv.notify_one();
    return val;
  }
  bool isempty() const { return top == -1; }
  bool isfull() const { return top == maxlen - 1; }
};

int main() {
  Stack s1(5);
  std::thread tout([&s1]() {
    for (;;) {
      std::cout << "popped val:" << s1.pop() << "\n";
      std::this_thread::sleep_for(interval);
    }
  });
  std::thread tin([&s1]() {
    for (;;) {
      s1.push(std::rand() % 100);
      std::this_thread::sleep_for(interval);
    }
  });
  tin.join();
  tout.join();

  return 0;
}
