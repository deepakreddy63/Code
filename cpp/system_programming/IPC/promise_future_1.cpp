// future & promise
/*
    std:: promise instances are used to pass arguments or handle exceptions
   across the threads A thread will create std:: promise object and get the
   future of it (get_future member). So it's a promise to update the object
   state in future. Promise object can be passed to another thread, who is
   supposed to update the state. First thread can wait for the update on promise
   object state via set_value Once the object is updated first thread can
   retrieve the updated state via getting the member So this can be considered
   as a high-level implementation of condition variables and mutex when object
   state to be reflected across the threads. An empty void future/promise can be
   used to signalling between the threads (one-shot event communication)
*/

#include <chrono>
#include <future>
#include <iostream>

void doSomething(int a, int b, std::promise<int> p) {
  int res;
  res = a / b;
  // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  p.set_value(res);
}
int main() {
  std::promise<int> p;
  std::future<int> f = p.get_future();
  std::thread t1(doSomething, 10, 2, std::move(p));
  t1.detach();
  // Here f.get blocks till the completion of p.set_value, you can check this by
  // uncommenting sleep statement This even works on detached threads
  // intentionally introduced for some delay
  std::cout << "result is " << f.get() << "\n";
  // t1.join();     //required if not detached
  return 0;
}