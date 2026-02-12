#include <iostream>
#include <string>
#include <random>
#include <cstdlib> 

using namespace std;
class Notify{
    public:
        virtual void send(const string& templ, const string& to, const string& body)=0;
        virtual ~Notify(){};
};
class NotifyByEmail: public Notify{
    public:
        void send (const string& templ, const string& to, const string& body) override {
            cout << "[SMTP] template=" << templ << " to=" << to << " body=" << body << "\n";
        }
};
class OTP{
    public:
        virtual string generateOTP()=0;
        virtual void sendOTP(const string& phone)=0;
        virtual ~OTP(){};
};
class TwilioClient : public OTP {
public:
    string generateOTP() override{
        int code = rand() % 900000 + 100000; 
        return to_string(code);
    }
    void sendOTP(const string& phone) override{
        string code = generateOTP();
        cout << "[Twilio] OTP " << code << " -> " << phone << "\n";
    }
};
class User{
    private:
        string email;
        string phone;
    public:
        void setEmail(const string& e) {
            email = e;
        }
        void setPhone(const string& p){
            phone =p;
            
        }
        string getEmail() const{
            return email;
        }
        string getPhone() const{
            return phone;
        }
};
class SaveDB{
    public:
        virtual void save(const User& u)=0;
        virtual ~SaveDB(){};
};
class MongoDB: public SaveDB{
    public:
        void save(const User& u) override{
            cout << "[MongoDB] user saved: " << u.getEmail() << "\n";
        }
};
class SignUpService{
    private:
        Notify& notifier;
        OTP& otpService;
        SaveDB& dbmsSave;
    public:
        SignUpService(Notify& mailer, OTP& sms, SaveDB& dbmsSave): notifier(mailer), otpService(sms), dbmsSave(dbmsSave){}
        bool signUp(const User& u){
            if (u.getEmail().empty()) return false;
            dbmsSave.save(u);

            notifier.send("welcome", u.getEmail(), "Welcome!");

            otpService.sendOTP(u.getPhone());
            return true;
        }
};



int main(){

    User u;
    u.setEmail("user@example.com");
    u.setPhone("+15550001111");
    NotifyByEmail mailer;
    TwilioClient sms;
    MongoDB dbmsSave;
    SignUpService svc(mailer, sms, dbmsSave);
    svc.signUp(u);
    return 0;
}
