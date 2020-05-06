//To test the smart pointers functionality in C++ 14
//Creating MyWidget class to test one with no smart pointers

#include<iostream>
#include<string>

class MyWidget{
    std::string m_label;
    MyWidget* m_parent=nullptr;
    MyWidget* m_child=nullptr;
    public:
   
    MyWidget(std::string label, MyWidget* parent):m_parent(parent), m_label(label){
        if(m_parent)
            m_parent->m_child = this;
    }
    MyWidget(std::string label):m_label(label){
    }
    MyWidget* getParent(){return m_parent;}
    MyWidget* getChild(){return m_child;}
    void display() const{
        std::cout << m_label << std::endl;
    }

};

int main(){
    MyWidget w1("parent");
    MyWidget w2("child1", &w1);
    MyWidget w3("child2", &w2);
    //Traversing child to parent, towards origin
    MyWidget *ptr=&w3;
    while(ptr){
        ptr->display();
        ptr=ptr->getParent();
    }
    //Traversing child to parent, towards origin
    ptr=&w1;
    while(ptr){
        ptr->display();
        ptr=ptr->getChild();
    }
    ptr=&w3;

    return 0;
}