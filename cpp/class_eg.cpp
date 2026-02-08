// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;
class Dog{
    private:
        string name;
        string color;
        string breed;
    public:
        Dog(){
            name = "";
            color ="";
            breed ="";
        }
        Dog(string n, string c, string b){
            name = n;
            color =c;
            breed =b;
        }
        void details(){
            cout<<"Name :" << name<< endl;
            cout<<"Color :" << color<< endl;
            cout<<"Breed :" << breed<< endl;
        }
};
int main() {
    // Write C++ code here
    // creating an object 
    Dog tommy = Dog("Tommy", "Golden", "Labrador");
    tommy.details();
    return 0;
}