// void futures for event signalling
// An empty promise & future can be used to synchronize between threads
// (one-shot event signalling)

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

void do_work(std::promise<void> barrier) {
  std::cout << "do some work\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  barrier.set_value();
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  std::cout << "some more work\n";
}

int main() {
  std::promise<void> barrier;
  std::future<void> barrier_future = barrier.get_future();
  std::thread t1(do_work, std::move(barrier));
  barrier_future.wait(); //???
  std::cout << "barrier crossed\n";
  t1.join();
  std::cout << "Thread got completed\n";
  return 0;
}