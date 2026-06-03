/*
Creating a learning management system 

User 
  - Student
  - Teacher 
Instructor : can get the list of Courses
Student -> Enrolled -> Courses -> Modules -> Lessons


Enrollement Service : 
  - Find Courses 
  - Find students 

(Factory Pattern)
Notification Service : send msgs to Users 
  - via Email
  - via SMS 
*/
#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_set>
using namespace std ;



class User{
  private :
    int id;
    string name;
    string password;
    string email;
  public :
    virtual ~User() = default;
    int getId(){
      return id;
    }
    string getName(){
      return name;
    }
    string getEmail(){
      return email;
    }

    bool login(string email, string password){
      if(this->email == email && this->password == password){
        return true;
      }
      return false;
    }
};

class Instructor : public User{
  private:
    vector<Courses*> coursesTaught;
  public :
    vector<Courses*> getCourses(){
      return coursesTaught;
    }
};

class Student : public User{
  private:
    vector<Enrollments*> enrollments;
  public :
    vector<Enrollments*> getEnrollments(){
      return enrollments;
    }
};





class Enrollments{
  public: enum EnrollmentStatus{
      ACTIVE,
      COMPLETED,
      CANCELLED
    };
  private :
    int id;
    time_t enrollmentDate;
    EnrollmentStatus status;
    Courses* course;
    unordered_set<int> completedLessons; 
    float progressPercentage;
  public :
    Enrollments(int id){
          this->id =id;
          enrollmentDate = time(nullptr);
          status = ACTIVE;
          progressPercentage = 0.0f;
    }

    void markLessonComplete( int lessonId){
      completedLessons.insert(lessonId);
      progressPercentage = (completedLessons.size() / static_cast<float>(course->getTotalLessons())) * 100.0f;
    }
    float getProgressPercentage(){
      return progressPercentage;
    }
};


class Lesson{
private:
    int id;
    string title;
    string contentUrl;
    int durationMinutes;

public:
    Lesson(int id, string title, string contentUrl, int durationMinutes);

    pair<string,string> getLessonDetails(int id) const;
};

class Modules{
private:
    int id;
    string title;
    vector<Lesson*> lessons;

public:
    Modules(int id, string title);

    void addLesson(Lesson* lesson);

    vector<Lesson*> getLessons() const;

    int getTotalLessons() const;
};

class Courses{
private:
    int id;
    string title;
    string description;
    vector<Modules*> modules;

public:
    Courses(int id, string title, string description);

    void addModule(Modules* module);

    vector<Modules*> getModules() const;

    int getTotalLessons() const;
};