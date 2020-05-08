//extending previous example using member functions as callback
//std:: thread instances can even take member functions as callbacks by binding calling object address.
//To bind: 
/*
void MyDataSet::psum(int start,int end);

MyDataSet *ds=new MyDataSet(100);
std::thread t2(&MyDataSet::psum,ds,200,400);
//(or)
using namespace std::placeholders;
auto tentry=std::bind(&MyDataSet::psum,ds,_1,_2);
std::thread t1(tentry,0,200);
*/ 

#include<thread>
#include<iostream>
class MyDataSet {
  int *arr;
  int maxlen;
  int total=0;
  public:
  MyDataSet(int len):maxlen(len) {
    arr=new int[maxlen];
  }
  MyDataSet(const MyDataSet&)=delete;
  void fill() {
    for(int i=0;i<maxlen;i++)
      arr[i]=std::rand()%100;
  }
  void psum(int start,int end) {
    int tsum=0;
    for(int i=start;i<end;i++) 
      tsum+=arr[i];
    total+=tsum;
  }
  void printTotal() {
    std::cout << "Final sum is:" << total << "\n";
  }
  void seqSum() {
    int seqSum=0;
    for(int i=0;i<maxlen;i++)
      seqSum+=arr[i];
    std::cout << "sequential sum:" << seqSum << "\n";
  }
};
int main() {
  MyDataSet ds(1000);
  ds.fill();
  std::thread t1(&MyDataSet::psum,&ds,0,200);
  std::thread t2(&MyDataSet::psum,&ds,200,400);
  std::thread t3(&MyDataSet::psum,&ds,400,600);
  std::thread t4(&MyDataSet::psum,&ds,600,800);
  std::thread t5(&MyDataSet::psum,&ds,800,1000);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  ds.printTotal();
  ds.seqSum();
  return 0;
}