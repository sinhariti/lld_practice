#include <iostream>

using namespace std;

class Employee{
    private:
        string name;
        double salary;
    public:
        void setname(string n){
            name = n;
        }
        void setsalary(double s){
            salary = s;
        }
        void getsalary(){
            cout<<this->salary<<endl;
        }
        void getname(){
            cout<<this->name<<endl;
        }
        ~Employee(){
            cout<<"Deleting employee"<<endl;
        }
};

int main(){
    Employee* e1 = new Employee();
    e1->setname("John");
    e1->setsalary(3000.0);
    e1->getname();
    delete e1;
    return 0;
}