// logging example
// Task : Identifying race conditions and applying mutex locks

/*
Syntax used for capturing variables :
      [&] : capture all external variable by reference
      [=] : capture all external variable by value
      [a, &b] : capture a by value and b by reference
*/
#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>

constexpr int max = 100;
std::mutex m1;

void log_temperature(std::ofstream &rout) {
  std::cout << "Temperature logging thread\n";
  int tval;
  for (int i = 1; i <= max; i++) {
    tval = std::rand() % 24 + 16;
    auto tnow = std::chrono::system_clock::now();
    auto tnow_c = std::chrono::system_clock::to_time_t(tnow);
    m1.lock();
    rout << "Temperature : " << tval << " @ " << std::ctime(&tnow_c) << "\n";
    m1.unlock();
    std::this_thread::sleep_for(std::chrono::duration<int, std::micro>(100));
  }
}

void log_humidity(std::ofstream &rout) {
  std::cout << "Humidity logging thread\n";
  int hval;
  for (int i = 1; i <= max; i++) {
    hval = std::rand() % 100;
    auto tnow = std::chrono::system_clock::now();
    auto tnow_c = std::chrono::system_clock::to_time_t(tnow);
    m1.lock();
    rout << "Humidity : " << hval << " @ " << std::ctime(&tnow_c) << "\n";
    m1.unlock();
    std::this_thread::sleep_for(std::chrono::duration<int, std::micro>(100));
  }
}

int main() {
  std::ofstream fout;
  fout.open("weather.log");
  std::thread t1([&]() { log_temperature(fout); });
  std::thread t2([&]() { log_humidity(fout); });
  t1.join();
  t2.join();
  fout.close();
  return 0;
}