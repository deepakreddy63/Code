//Usage of threads for large parallel sum of array

#include<thread>
#include<iostream>
#include<cstdlib>

constexpr int maxsize=10000000;
int mul = maxsize/1000;
int arr[maxsize];
int parallelSum=0;

void do_sum(int start,int end) {
  int tsum=0;
  for(int i=start;i<end;i++) 
    tsum+=arr[i];
  parallelSum+=tsum;                 //???
}

int main() {
  std::srand(std::time(nullptr));
  for(int i=0;i<maxsize;i++)
    arr[i]=std::rand()%100;
  int seqSum=0;
  auto tstart=std::chrono::system_clock::now(); 
  for(int i=0;i<maxsize;i++)
    seqSum+=arr[i];
  auto tend=std::chrono::system_clock::now();
  std::chrono::duration<double,std::micro> elapsed=tend-tstart;
  //auto elapsed=tend-tstart;
  std::cout << "sequential sum :" << seqSum << " completed in us " << elapsed.count() << "\n";
  /************************************************/
  tstart=std::chrono::system_clock::now(); 
  std::thread t1(do_sum,0*mul,200*mul);        //0-200*mul-1
  std::thread t2(do_sum,200*mul,400*mul);    //200-399
  std::thread t3(do_sum,400*mul,600*mul);    //400-599
  std::thread t4(do_sum,600*mul,800*mul);    //600-799
  std::thread t5(do_sum,800*mul,1000*mul);    //800-999
  
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  tend=std::chrono::system_clock::now();
  elapsed=tend-tstart;
  std::cout << "Parallel sum is :" << parallelSum << " completed in us " << elapsed.count() << "\n";

  //Another approach with variable threads
  int n=10;
  parallelSum = 0;
  std::thread *tarr[n];
  int range=maxsize/n;
  int start = 0;
  tstart=std::chrono::system_clock::now();
  for(int i=0;i<n;i++) {
    tarr[i]=new std::thread(do_sum,start,start+range);
    start+=range;
   }
  for(int i=0;i<n;i++) {
    tarr[i]->join();
    delete tarr[i];
  }
  tend=std::chrono::system_clock::now();
  elapsed=tend-tstart;
  std::cout << "Parallel sum with thread array is :" << parallelSum << " completed in us " << elapsed.count() << "\n";
  
  //Another test I ran was to store threads as objects instead of pointers which compares stack vs heap memory access 
  //Stack storage runs little faster but stack has fixed size in RAM memory where as heap is flexible, but heap can cause fragmentation issue
  
  return 0;
}