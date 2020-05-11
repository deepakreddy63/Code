// Operations on atomic variables ensure that no race condition by intrinsic
// mutual exclusion.

#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> val(100);
constexpr int max = 1000000;

void do_inc() {
  for (int i = 0; i < max; i++) {
    val++; // atomic operation
  }
}
void do_dec() {
  for (int i = 0; i < max; i++) {
    val--; // atomic operation
  }
}

int main() {
  std::thread t1(do_inc);
  std::thread t2(do_dec);
  t1.join();
  t2.join();
  std::cout << "Final val:" << val << "\n";
}