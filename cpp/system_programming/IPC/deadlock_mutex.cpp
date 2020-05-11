/*
Let's consider a scenario, where we need two mutex operations to protect two
shared resources. Arbitrary mutex operations can lead to deadlock as shown in
the following example.i.e. if switching occurs in the middle of m1.lock, m2.lock
bot the threads will be infinitely blocked waiting for another mutex by locking
a mutex each

The deadlock problem in this example can be resolved with safe locking
operations as shown in the following example, these locking techniques ensures
that both the mutexes will be locked or none. If one mutex is locked but other
is not available, the locked mutex will be released and trying to lock both
again. Since the mutex shouldn't be locked independently(one at a time),
deferred lock option is specified so that constructor of unique_lock won't lock
mutex immediately and deferred for safe locking together.
*/

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex m1;
std::mutex m2;
std::chrono::duration<int, std::micro> interval(100);

void do_service1() {
  std::cout << "A--welcome\n";
  // m1.lock();     //let's assume this thread executes initially and switch a
  // here m2.lock();
  std::unique_lock<std::mutex> ulck1(m1, std::defer_lock);
  std::unique_lock<std::mutex> ulck2(m2, std::defer_lock);
  std::lock(ulck1, ulck2); // safe locking with deadlock avoidance algorithms
  for (int i = 1; i <= 10; i++) {
    std::cout << "A--" << i << "\n";
    std::this_thread::sleep_for(interval);
  }
  // m2.unlock();
  // m1.unlock();
}
void do_service2() {
  std::cout << "B--welcome\n";
  // m2.lock();    //arbitrary sequence of locking mutexes
  // m1.lock();    //may lead to dead lock
  std::unique_lock<std::mutex> ulck1(m2, std::defer_lock);
  std::unique_lock<std::mutex> ulck2(m1, std::defer_lock);
  std::lock(ulck1, ulck2); // safe locking with deadlock avoidance algorithms
  for (int i = 1; i <= 10; i++) {
    std::cout << "B--" << i << "\n";
    std::this_thread::sleep_for(interval);
  }
  // m1.lock();
  // m2.lock();
}

int main() {
  std::thread t1(do_service1);
  std::thread t2(do_service2);
  t1.join();
  t2.join();
}