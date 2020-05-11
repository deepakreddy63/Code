/*
Code Analysis:-

    In this example, you can observe that only one thread can enter the for loop
(Let's consider this as dummy critical section, stdout as a shared resource) at
a time Second thread can enter for loop only when the first thread releases the
mutex after completion of for loop.

*/
// std::unique_lock/std::lock_guard ensures that underlying mutex will be
// unlocked when the lock instance goes out of the scope.
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex m1;
std::chrono::duration<int, std::micro> interval(100);

void do_service1() {
  std::cout << "A--welcome\n";
  std::unique_lock<std::mutex> ulck(m1);
  // std::lock_guard<std::mutex> glck(m1);
  // m1.lock();
  for (int i = 1; i <= 10; i++) {
    std::cout << "A--" << i << "\n";
    std::this_thread::sleep_for(interval);
  }
  // m1.unlock();
}
void do_service2() {
  std::cout << "B--welcome\n";
  m1.lock();
  for (int i = 1; i <= 10; i++) {
    std::cout << "B--" << i << "\n";
    std::this_thread::sleep_for(interval);
  }
  m1.unlock();
}

int main() {
  std::thread t1(do_service1);
  std::thread t2(do_service2);
  t1.join();
  t2.join();
  return 0;
}