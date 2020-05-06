//Weak ptr concept is used to avoid cyclic redundancy problem in smart_pointers_2.cpp
//Cyclic redundancy in the previous problem can be resolved through weak pointers.
//Here parent tracking is done through the strong pointer (shared pointer) and child tracking is done through weak pointers.
//Being weak pointer child tracker doesn't participate in reference counting, which eliminates cyclic redundancy.
//Also please observe the access to child widgets while traversing from origin to the last widget

#include<iostream>
#include<memory>

class MyWidget {
  std::string m_label;
  public:
  std::shared_ptr<MyWidget> m_parent;
  std::weak_ptr<MyWidget> m_child;
  MyWidget(std::string label,std::shared_ptr<MyWidget>& parent)
                                :m_parent(parent),m_label(label) { 
  }
  MyWidget(std::string label):m_label(label) {
  }
  void setChild(const std::shared_ptr<MyWidget>& ptr) { m_child=ptr; }

  std::shared_ptr<MyWidget>& getParent() { return m_parent; }
  std::weak_ptr<MyWidget>& getChild()  { return m_child; }

  void display () const {
    std::cout << "Display  for " << m_label << "\n";
    std::cout << "parent count: " << m_parent.use_count() << "\n";
    std::cout << "pchild count: " << m_child.use_count() << "\n";
  }
};

int main() {
  std::shared_ptr<MyWidget> wp1(new MyWidget("parent"));
  std::shared_ptr<MyWidget> wp2(new MyWidget("child1",wp1));
  std::shared_ptr<MyWidget> wp3(new MyWidget("child2",wp2));

  wp1->setChild(wp2);
  wp2->setChild(wp3);
  wp3->setChild(nullptr);

  wp1->display();
  wp2->display();
  wp3->display();

  std::weak_ptr<MyWidget> wptr(wp1);
  std::shared_ptr<MyWidget> sptr;
  while(true) {
    sptr=wptr.lock();
    if(!sptr) break;
    sptr->display();
    wptr=sptr->getChild();
  }

  std::shared_ptr<MyWidget> ptr=wp3;
  while(ptr!=nullptr) {
    ptr->display(); 
    ptr=ptr->getParent();
  }
  return 0;
}
