//To test the smart shared pointers functionality in C++ 14 one-way
//One way, i.e. only child tracks the parent but not vice versa

#include<iostream>
#include<string>
#include<memory>

class MyWidget{
    std::string m_label;
    std::shared_ptr<MyWidget> m_parent;
    public:
    MyWidget(std::string label, std::shared_ptr<MyWidget>& parent):m_parent(parent), m_label(label){
    }
    MyWidget(std::string label):m_label(label){
    }
    std::shared_ptr<MyWidget>& getParent(){return m_parent;}
    void display() const{
        std::cout << m_label << std::endl;
        std::cout << m_parent.use_count() << "\n";
    }

};

int main(){
    std::shared_ptr<MyWidget> wp1 = std::make_shared<MyWidget>("parent");
    std::shared_ptr<MyWidget> wp2 = std::make_shared<MyWidget>("child1", wp1);
    std::shared_ptr<MyWidget> wp3 = std::make_shared<MyWidget>("child2", wp2);

    wp1->display();
    wp2->display();
    wp3->display();

    std::shared_ptr<MyWidget> ptr(wp3);
    while(ptr){
        ptr->display();
        ptr=ptr->getParent();
    }
    return 0;
}