//To test the smart pointers functionality in C++ 14 two-way
//Having shared pointers in both ways, i.e. child to parent and parent to child causes cyclic redundancy.
//That means reference count of shared count never becomes zero, thus underlying objects are not released.
//This leads to memory leaks (check with Valgrind--> valgrind --leak-check=full ./a.out)

#include<iostream>
#include<string>
#include<memory>

class MyWidget{
    std::string m_label;
    std::shared_ptr<MyWidget> m_parent;
    std::shared_ptr<MyWidget> m_child;
    public:
    MyWidget(std::string label, std::shared_ptr<MyWidget>& parent):m_parent(parent), m_label(label){
    }
    MyWidget(std::string label):m_label(label){
    }
    void setChild(const std::shared_ptr<MyWidget>& ptr) {std::cout <<"\n"; m_child=ptr;}
    std::shared_ptr<MyWidget>& getParent(){return m_parent;}
    std::shared_ptr<MyWidget>& getChild(){return m_child;}
    void display() const{
        std::cout << m_label << std::endl;
        std::cout << m_parent.use_count() << "\n";
        std::cout << m_child.use_count() << "\n";
    }

};

int main(){
    std::shared_ptr<MyWidget> wp1(new MyWidget("parent"));
    std::shared_ptr<MyWidget> wp2(new MyWidget("child1",wp1));
    std::shared_ptr<MyWidget> wp3(new MyWidget("child2",wp2));

    wp1->setChild(wp2);   //TODO:better logic via constructor
    wp2->setChild(wp3);
    wp3->setChild(nullptr);

    wp1->display();
    wp2->display();
    wp3->display();

    std::shared_ptr<MyWidget> ptr(wp1);
    while(ptr){
        ptr->display();
        ptr=ptr->getChild();
    }

    ptr = wp3;
    while(ptr){
        ptr->display();
        ptr=ptr->getParent();
    }
    return 0;
}