
//Parallel sum using container

#include<thread>
#include<iostream>

constexpr int maxsize=10000;
std::array<int,maxsize> arr;
int total(0);
//template<typename T>
using myiter_t=std::array<int,maxsize>::iterator;
void psum(myiter_t pstart, myiter_t pend) {
  int tsum=0;
  for(auto iter=pstart;iter!=pend;++iter)
    tsum += *iter;
  total+=tsum;
}

int main() {
  int lsum=0,i;
  //for(auto iter=arr.begin();iter!=arr.end();++iter) 
  //  *iter=std::rand()%100;
  for(auto& x:arr)
    x=std::rand()%100;
  for(auto x:arr)
    lsum+=x;
  std::cout << "Linear sum is " << lsum << "\n";
  int n=10;
  std::thread *tarr[n];
  int range=maxsize/n;
  std::array<int,maxsize>::iterator tstart=arr.begin();
  for(i=0;i<n;i++) {
    tarr[i]=new std::thread(psum,tstart,tstart+range);
    tstart+=range; 
  }
  for(i=0;i<n;i++) {
    tarr[i]->join();
    delete tarr[i];
  }
  std::cout << "Final sum is " << total << "\n";
  return 0;
}