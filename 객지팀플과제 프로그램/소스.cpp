#include<iostream>
#include<fstream>
#include<string>

using namespace std;


class Login { //로그인 추상클래스
protected:
    string id;
    string password;
public:
    Login() : id(id), password(password) {}
    virtual void signUp() {} // 회원가입 가상함수
    virtual void login() {} // 로그인 가상함수
};

class Id : public Login {
private:
    string id, password;
    string song;
    string degree; // 등급
public:
    Id() : Login(), id(id), password(password), song(song), degree(degree) {
        cout << "아이디를 입력하세요: " << endl;
        cin >> id;
        cout << "비밀번호를 입력하세요: " << endl;
        cin >> password;
        degree = "브론즈";
    }
    void signUp() {
        ofstream writeFile;
        writeFile.open("login.txt");
        writeFile.write(id.c_str(), id.size());
        writeFile.write(password.c_str(), password.size());
        writeFile.close();





    }
    void login() {
        string login_id, login_password;
        cout << "ID를 입력하세요: ";
        cin >> id;
        cout << "비밀번호를 입력하세요: ";
        cin >> password;
        ifstream readFile(id + ".txt");
        bool found = false;
        while (getline(readFile, login_id) && getline(readFile, login_password)) {
            if (id == login_id && password == login_password)
            {
                found = true;
                break;
            }
            if (found)
                cout << "로그인 성공!" << endl;
            else
                cout << "ID 또는 비밀번호가 일치하지 않습니다." << endl;
            readFile.close();
        }
        void addSong() {
            ofstream writeFile;
            writeFile.open(id + ".txt");
            cout << "원하는 노래를 입력하세요: " << endl;
            cin.ignore();
            getline(cin, song);
            writeFile.write(song.c_str(), song.size());
            writeFile.close();
        }
    };


    int main(void)
    {
        Id a;
        a.login();
        a.login();
    }