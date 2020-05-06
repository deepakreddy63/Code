//testing the basic concepts of smart pointers namely
//unique_ptr, shared_ptr and weak_ptr in seperate sections

#include<iostream>
#include<memory>

class Sample {
  int x;
  int y;
  public:
  Sample()=default;
  Sample(int p,int q):x(p),y(q) { }
  void printxy() const {
    std::cout << x << "," << y << "\n";
  }
  ~Sample() {
    std::cout << "Sample--destr\n";
  }
};

void test_weak_ptr(std::weak_ptr<Sample>& wp) {
  std::cout << "test--wp.expired?: " << wp.expired() << std::endl;
  if( std::shared_ptr<Sample> stemp = wp.lock() ) {
    std::cout << "Test--weak pointer is alive\n";
    std::cout << "stemp.use_count(): " << stemp.use_count() << std::endl;
    stemp->printxy();
  }
  else{
    std::cout << "Test -- Weak pointer got expired\n";
    //stemp->printxy();      //run time exception
  }
};
std::weak_ptr<Sample> wp1;
void bar(std::shared_ptr<Sample>& sptr) {
    std::shared_ptr<Sample> stemp(sptr);
    test_weak_ptr(wp1);    //3
}
void foo() {
    std::shared_ptr<Sample> sp=std::make_shared<Sample>(10,20);
    test_weak_ptr(wp1);    //2
    bar(sp);
    test_weak_ptr(wp1);    //4
}  

int main(){

    //Section for unique pointers
    /*
    std::unique_ptr<Sample> p1(new Sample(10, 20));
    p1->printxy();
    //std::unique_ptr<Sample> p2(ps);  //error,copy semantics are disabled
    std::unique_ptr<Sample> p2(std::move(p1));
    
    std::unique_ptr<Sample> p3;
    p3 = std::unique_ptr<Sample>(new Sample(15, 18));     
    
    std::unique_ptr<Sample> p4;
    //p4=p3;                             //error

    //get member gives access to a raw pointer for an underlying object (if any)
    std::cout << p1.get() << "\n";     
    std::cout << p2.get() << "\n";     

    //reset can change an underlying object, i.e. release the old object and attach a new object
    std::unique_ptr<Sample> ps(new Sample(10, 20));
    ps->printxy();
    ps.reset(new Sample(11,21));    //previous object got deleted
    std::cout << ps.get() << "\n";
    ps->printxy();

    //operator==, operator!=, operator bool are available for comparison (null check of course)
    p1.reset(new Sample(10, 20));
    p2.reset();
    if(p1!=nullptr)    //if(p1) also works
        p1->printxy();
    if(p2==nullptr)    //if(!p2) also works
        std::cout << "p2 has already released memory";

    //Also, the usage of make_unique guarantees that it'll wrap to a new object only and 
    //also avoids dangerous heap problems as a resultant of wrapping raw pointers
    std::unique_ptr<Sample> p5=std::make_unique<Sample>(10,20);
    
    //Array of Objects
    
    std::unique_ptr<Sample[]> sparr(new Sample[10]);
    std::cout << sparr.get() << "\n";
    for(int i=0;i<10;i++)
        sparr[i].printxy();
    
    //TODO: ensure all the objects are released 
    //      using valgrind or dummy print in destructor

    std::unique_ptr<int[]> parr(new int[10]);
    for(int i=0;i<10;i++)
        parr[i]=10*i;
    */
    //////////////////////////////////////////////////////////////////////////////////////////////    
    /*
    //Section for shared pointer

    std::shared_ptr<Sample> p1(new Sample(10,20));
    std::cout << p1.use_count() << "\n";
    std::shared_ptr<Sample> p2(p1);
    std::cout << p1.use_count() << "\n";
    std::cout << p2.use_count() << "\n";
    std::shared_ptr<Sample> p3(p1);
    std::cout << p3.use_count() << "\n";
    std::cout << p1.use_count() << "\n";
    std::cout << p1.get() << "," << p2.get() << "," << p3.get() << "\n";
    p2.reset();  //p2=nullptr
    std::cout << p1.use_count() << "\n";
    //object will be release when p1,p2,p3,ptr goes out of scope

    //Another Example to observe reference count as per the scope of shared pointers
    std::shared_ptr<int> p4(new int());
    std::cout <<"\n" << p4.use_count() << "\n";
    {
        std::shared_ptr<int> p5(p4);
        std::cout << p4.use_count() << "\n";
        {
            std::shared_ptr<int> p6(p5);
            std::cout << p5.use_count() << "\n";
        }
        std::cout << p5.use_count() << "\n";
        p5.reset();  // p5=nullptr;
        std::cout << p4.use_count() << "\n";
    }
    std::cout << p4.use_count() << "\n";

    //As discussed during a unique pointer, wrapping raw pointers into a shared pointer also lead to dangerous situations. 
    //So always directly wrap the objects created by the new operator or usage of make_shared is highly recommended.
    std::shared_ptr<Sample> sp=std::make_shared<Sample>(10,20);

    */
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //Section for weak pointer

   //Weak pointers hold a non-owning reference to an object managed by another shared pointer
   //Weak pointers doesn't participate in reference counting
   //Weak pointers need to be converted into a shared pointer to access underlying objects.
   //Weak pointer may live beyond the life time of a managed object, but is considered as expired and can't access an underlying object

    std::shared_ptr<Sample> sp=std::make_shared<Sample>(10,20);
    std::weak_ptr<Sample> wp=sp;

    std::cout << "weak ptr use_count: " << wp.use_count() << std::endl;
    std::cout << "shared ptr use_count: " << sp.use_count() << std::endl;

    test_weak_ptr(wp);
    sp.reset();              //managed object is released
    test_weak_ptr(wp);  
  
    test_weak_ptr(wp1);     //1
    foo();
    test_weak_ptr(wp1);     //5

    return 0;
}
