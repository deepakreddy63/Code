// Implementation of producer consumer problem synchronisation
// Condition Variable is a kind of Event used for signaling between two or more
// threads. One or more thread can wait on it to get signaled, while an another
// thread can signal this. A mutex is required along with condition variable.

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>

std::mutex m1;
std::condition_variable cv;
std::atomic<int> k(0);

void do_service1() {
  std::cout << "A--welcome\n";
  for (int i = 1; i <= 100; i++) {
    std::unique_lock<std::mutex> lk(m1);
    cv.wait(lk, []() { return k < 5; });
    std::cout << "A--" << i << "\n";
    k++;
    if (k == 4) {
      lk.unlock();
      cv.notify_one();
    }
  }
}
void do_service2() {
  std::cout << "B--welcome\n";

  for (int i = 1; i <= 100; i++) {
    std::unique_lock<std::mutex> lk(m1);
    cv.wait(lk, []() { return k > 0; });
    k--;
    std::cout << "B--" << i << "\n";
    if (k == 0) {
      lk.unlock();
      cv.notify_one();
    }
  }
}
int main() {
  std::thread t1(do_service1);
  std::thread t2(do_service2);
  t1.join();
  t2.join();
  return 0;
}