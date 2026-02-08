// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;
// Abstraction - Interface 
class Vehicle{
    public:
        virtual ~Vehicle() {
            cout<<"Deleting Vehicle"<<endl;
        }
        virtual void brake()=0;
        virtual void accelerate()=0;
};
class Car: public Vehicle{
    public:
        void brake() override{
            cout<<"Applying car brakes"<<endl;
        }
        void accelerate() override{
            cout<<"Car speeding up"<<endl;
        }
         ~Car() {
            cout<<"Deleting Car"<<endl;
        }
};
class Scooter: public Vehicle{
    public:
        void brake() override{
            cout<<"Applying Scooter brakes"<<endl;
        }
        void accelerate() override{
            cout<<"Scooter speeding up"<<endl;
        }
        ~Scooter() {
            cout<<"Deleting Scooter"<<endl;
        }
};
// abstract class
class Shape{
    protected:
        string color;
    public:
        Shape(string color){
            this->color= color;
        }
        virtual void area()=0;
        void getcolor(){
            cout<<"Color:"<< color<<endl;
        }
        virtual ~Shape(){
            cout<<"Deleting Shape"<< endl;
        }
};
class Square: public Shape{
    private:
        double width;
        double length;
    public :
        Square(string c, double w, double l): Shape(c){
            width = w;
            length=l;
        }
        void area(){
            cout<<"Area:"<<length*width<< endl;
        }
        ~Square(){
            cout<< "Deleting Square"<< endl;
        }
};

int main() {
    // Write C++ code here
    // creating an object
    Vehicle* car = new Car();
    Vehicle* scooty = new Scooter();
    
    Shape* sq = new Square("Green", 5, 4);
    car->brake();
    scooty->accelerate();
    
    sq->getcolor();
    sq->area();
    
    // delete scooty;
    // delete sq;
    delete car;
    return 0;
}