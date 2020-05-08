//To use async future for higher level definition of threads
/*
    Async task is a high-level implementations for threads for simplified execution of concurrent tasks
    They allow to run a piece of code (callable elements) in the background as a separate thread and fetch the return value.
    The thread can be picked up from a thread pool or by creating a new one
    Futures wait for the completion of Async and collect the results from their execution
    This is beneficial over threads to fetch results from computations, other wise we need to manage with 
        some shred data like global variables in case of low-level threads.

*/
//To stop a thread: https://thispointer.com/c11-how-to-stop-or-terminate-a-thread/
//call_onces ensures that some code is executed only once, though it's invoked by multiple threads
#include<future>
#include<iostream>
int doSumofArray(int *arr,int max) {
  int tsum=0;
  for(int i=0;i<max;i++)
    tsum+=arr[i];
  return tsum;
}

constexpr int maxsize=1000;
int arr[maxsize];

int do_async_sum(int start,int end) {
  int tsum=0;
  for(int i=start;i<end;i++) 
    tsum+=arr[i];
  return tsum;          
}

int main() {
  int arr1[100];
  std::srand(std::time(0)); //use current time as seed for random generator
  for(int i=0;i<100;i++)
    arr1[i]=rand()%100;
  std::future<int> sum;
  sum=std::async(doSumofArray,arr1,100);
  //do some work while async task is running
  std::cout << sum.get() << "\n";

  //Rewritten Parallel sum example using async and future
  std::srand(std::time(nullptr));
  
  for(int i=0;i<maxsize;i++)
    arr[i]=std::rand()%100;
  /************************************************/
  std::future<int> f1;
  std::future<int> f2;
  std::future<int> f3;
  std::future<int> f4;
  std::future<int> f5;
  f1=std::async(do_async_sum,0,200);      //0-199
  f2=std::async(do_async_sum,200,400);    //200-399
  f3=std::async(do_async_sum,400,600);    //400-599
  f4=std::async(do_async_sum,600,800);    //600-799
  f5=std::async(do_async_sum,800,1000);   //800-999
  
  int total=f1.get()+f2.get()+f3.get()+f4.get()+f5.get();
  std::cout << "Final sum is :" << total << "\n";

  return 0;
}