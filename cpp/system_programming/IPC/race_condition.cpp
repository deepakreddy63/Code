// Simulates a race condition in common shared global variable
// This happens as the val is within the process of operation and not updated
// when other func accesses it
/*
Race conditions - Concurrent access to shared resources by two or more threads
lead to inconsistency, in other words, the final state of the resources will be
undefined. Critical Section - a piece of code accessing the shared resource
Mutual Exclusion - allowing shared resource access to only one thread at a time,
in other words only one thread can be in their critical section at a time.
OS/Library support for Mutual Exclusion

    Semaphores
    Mutex
    Spinlocks

*/
#include <iostream>
#include <thread>

int val = 100;
constexpr int max = 100000;

void do_inc() {
  for (int i = 0; i < max; i++) {
    val++;
    if (i % 10000 == 0)
      std::cout << "Inc val:" << val << "\n";
  }
}
void do_dec() {
  for (int i = 0; i < max; i++) {
    val--;
    if (i % 10000 == 0)
      std::cout << "Dec val:" << val << "\n";
  }
}
int main() {
  std::thread t1(do_inc);
  std::thread t2(do_dec);
  t1.join();
  t2.join();
  std::cout << "Final val:" << val << "\n";
}