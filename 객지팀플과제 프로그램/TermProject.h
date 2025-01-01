#ifndef TermProject_h
#define TermProject_h


#include <iostream>
#include <fstream>
#include <string>
using namespace std;



class Login : public ReadFile {
public:
    //Login() : Ui() {}

    //void drawMenu() override {}
    void login() {
        int a = CheckMember();
        if (a == true) {
            cout << "로그인 성공!" << endl;
        }
    }
};

class ReadFile {
    string line;             // line: 메모장의 내용, file: 파일을 연 내용, filename: 파일이름
    ifstream Readfile;
    ofstream Writefile;
    string filename;
public:
    ReadFile(const string& filename) : Readfile(filename) {
        this->filename = filename;
        if (!Readfile.is_open()) {
            cerr << "파일이 없습니다." << filename << endl;
        }
    }

    bool CheckMember(const string& username, const string& password) {  // 로그인 확인 함수, 회원가입 시 아이디 비번이 겹치는지 확인 
        while (getline(Readfile, line)) {
            size_t info = line.find(' ');                               // info 에 띄어쓰기가 나타나는 위치를 찾아 저장
            string Member_username = line.substr(0, info);              // Member_username = 뜨어쓰기 이전 부분
            string Member_password = line.substr(info + 1);             // Member_password = 띄어쓰기 이후 부분

            if (Member_username == username && Member_password == password) {
                return true;
            }
        }
            Readfile.close(); 
            return false;
    }
    void DeleteUser(const string& username, const string& password) {
        ofstream Writefile("temp.txt", ios::app);  // Open a temporary file for appending

        while (getline(Readfile, line)) {
            size_t info = line.find(' ');
            string Member_username = line.substr(0, info);
            string Member_password = line.substr(info + 1);

            if (Member_username != username || Member_password != password) {
                Writefile << line << endl;  // Write lines for non-deleted users to the temporary file
            }
        }

        Readfile.close();
        Writefile.close();

        remove(filename.c_str());  // Remove the original file
        rename("temp.txt", filename.c_str());  // Rename the temporary file to the original filename

    };
#endif