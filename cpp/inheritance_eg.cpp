#include <iostream>

using namespace std;
// Inheritance
class Shape{
    protected :
        string color;
    public:
        Shape(string color){
            this->color = color;
        }
        void getcolor(){
            cout<< "Color:" << color<<endl;
        }
        virtual int area()=0;
        virtual ~Shape(){
            cout<<"Deleting Shape"<<endl;
        }
};
class Square : public Shape{
    private:
        int side;
    public:
        Square(string c, int a): Shape(c){
            side =a;
        }
        int area() override{
            return side*side;
        }
        ~Square(){
            cout<<"Deleting Square"<<endl;
        }
};
int main(){
    Shape* sq = new Square("Green", 4);
    sq->getcolor();
    cout<<"Area :"<< sq->area()<< endl;
    delete sq;
    return 0;
}