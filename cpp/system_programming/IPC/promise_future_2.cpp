// Futures can also pass the exceptions occurred at the thread level
// To demonstrate the use of future for exception handling between threads

/*
Optional:
A std::shared_future
    permits you to ask the promise independent of the other associated futures.
    Per default, there is a one-to-one relation between the promise and the
future. But std::shared_future supports a one-to-many relations between a
promise and many futures
*/

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

void do_something(int a, int b, std::promise<int> &&p) {
  int c;
  try {
    if (b == 0)
      throw std::runtime_error("div by zero");
    c = a / b;
    p.set_value(c);
  } catch (std::exception &e) {
    p.set_exception(std::current_exception());
  }
}

int main() {
  try {
    std::promise<int> p;
    std::future<int> f;
    f = p.get_future();
    std::thread t1(do_something, 10, 0, std::move(p));
    t1.detach(); // Test with t1.join() and what happens if gets terminated in
                 // middle
    std::cout << "Result is: " << f.get() << "\n";
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
  } catch (...) {
    std::cerr << "Generic exception\n";
  }

  return 0;
}