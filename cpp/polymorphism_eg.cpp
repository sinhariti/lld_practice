#include <iostream>

using namespace std;
// Method overriding
class Base{
    public:
        virtual void display(){
            cout<<"This is base class"<<endl;
        }
        ~Base(){
            cout<<"Deleting Base"<<endl;
        }
};
class Subclass : public Base{
    public:
        void display() override{
            cout<<"This is subclass"<<endl;
        }
        ~Subclass(){
            cout<<"Deleting Subclass"<<endl;
        }
};

//method Overloading
class Calculator{
    public:
        int mul(int a, int b){
            return a*b;
        }
        float mul(float a, float b){
            return a*b;
        }
        ~Calculator(){};
};
int main(){
    Base* b;
    Subclass s;
    b=&s;
    b->display();
    
    Calculator c = Calculator();
    cout<<c.mul(3.5f, 4.7f)<<endl;
    cout<<c.mul(2, 4)<<endl;
    

    return 0;
}