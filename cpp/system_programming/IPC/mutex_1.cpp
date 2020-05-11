// C++11 provides std:: mutex class for mutual exclusion, let's consider an
// example to prevent race conditions in the previous example.
/*
Mutex is a system/library level data structure which ensures non-concurrent
access to shared resources, i.e. allowing only one thread to execute their
related critical sections at a time. Mutex operations - lock & unlock Lock rules

    If the mutex is in Unlocked state, lock it and allow thread execution,i.e.
this thread is the first person trying to access a shared resource If the mutex
is in Locked state, block the current thread and add to mutex queue,i.e. already
another thread is in middle of shared resource access, thus blocking the current
thread.

Unlock rules

    If the mutex queue is not empty, remove one thread from queue and resume
(unblocking from the blocked state ) If the queue is empty, change mutex state
back to Unlocked

Salient features of Mutex and differences from semaphore operations

    Mutex comes with ownership, i.e. whichever thread locks the mutex can only
unlock Unlocking before locking is not allowed with the mutex Unlocking more
than once us not allowed with a mutex (non-recursive mutex)

Thus we can say those mutex operations are purely meant for mutual exclusion,
not for synchronization,
*/
#include <iostream>
#include <mutex>
#include <thread>

int val = 100;
constexpr int max = 100000;
std::mutex m1;

void do_inc() {
  for (int i = 0; i < max; i++) {
    m1.lock();
    val++;
    m1.unlock();
  }
}
void do_dec() {
  for (int i = 0; i < max; i++) {
    m1.lock();
    val--;
    m1.unlock();
  }
}
int main() {
  std::thread t1(do_inc);
  std::thread t2(do_dec);
  t1.join();
  t2.join();
  std::cout << "Final val:" << val << "\n";
}