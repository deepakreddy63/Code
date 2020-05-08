//Basics of thread
//In absence of joining main thread won't wait for the completion of running thread(t1), 
//as a resultant all running threads terminate abnormally when main thread hits return statement. 

/*
A thread can execute independently in the detachable state like client connection etc.
To detach a thread
void doSomething() {
   //heavy/busy code or infinite loop
}
std::thread t1(doSomething);
t1.detach();
*/
//To stop a thread: https://thispointer.com/c11-how-to-stop-or-terminate-a-thread/
//Compile: g++ -pthread thread_1.cpp

#include<thread>
#include<iostream>
using namespace std::chrono_literals;

constexpr int max=10;

void do_service1() {
  std::cout << "A--welcome\n";
  for(int i=1;i<=max;i++) {
    std::cout << "A--" << i << "\n";
    std::this_thread::sleep_for(1s);  
  }
}

void do_service2() {
  std::cout << "B--welcome\n";
  for(int i=1;i<=max;i++) {
    std::cout << "B--" << i << "\n";
    std::this_thread::sleep_for(1s);
  }
}

void do_service(std::string label) {
  std::cout << "Started thread with id : " << std::this_thread::get_id() << "\n";
  std::cout << label << "--welcome\n";
  for(int i=1;i<=20;i++) {
    std::cout << label << "--" << i << "\n";
    std::this_thread::sleep_for(100us);
  }
}

class DoService {
  std::string m_label;
  public:
  DoService(std::string label):m_label(label) { }
  DoService(){ }
  //The first () is the name of the operator - it's the operator that is invoked when you use () on the object. 
  //The second () is for the parameters, of which there are none.
  void operator()() {
    std::cout << m_label << "--welcome\n";
    for(int i=1;i<=20;i++) {
      std::cout << m_label << "--" << i << "\n";
      std::this_thread::sleep_for(std::chrono::duration<int,std::micro>(100));
    }
  }

  void operator()(std::string label) {
    std::cout << label << "--welcome\n";
    for(int i=1;i<=20;i++) {
      std::cout << label << "--" << i << "\n";
      std::this_thread::sleep_for(std::chrono::duration<int,std::micro>(100));
    }
  }
};

int main() {
   /*                 
  //Task driven parallelism
  std::thread t1(do_service1);
  std::thread t2(do_service2);
  t1.join();
  t2.join();
  */
  /*
  //Data driven parallelelism
  std::thread t1(do_service,"A1");
  std::thread t2(do_service,"B2");
  t1.join();
  t2.join();
  std::cout << "main--thank you\n";
  //sleep_until blocks the thread till a future timepoint, this is helpful for absolute delays where as sleep_for is helpful for relative delays
  */

  /*
  //Using lambdas as callbacks:-
  int max=10;
  std::thread t1( [=] () {
    std::cout << "Welcome\n";
    for(int i=1;i<=max;i++){
        std::cout << ("Hello--%d\n",i);
        std::this_thread::sleep_for(100us);
    }
  });
  std::thread t2( []() {
    do_service("C3");
  });
  auto do_compute = [](std::string label) {
    do_service(label);
  };
  std::thread t3(do_compute,"D4"); 
  t1.join();
  t2.join();
  t3.join();
*/
  
  //Using function objects as callbacks:-
  std::thread t1(DoService("A1"));
  DoService s2("B2");
  std::thread t2(s2);
  t1.join();
  t2.join();

  std::thread t3(DoService(),"C1");
  DoService s3;
  std::thread t4(s3,"D2");
  t3.join();
  t4.join();
  
  return 0;


}