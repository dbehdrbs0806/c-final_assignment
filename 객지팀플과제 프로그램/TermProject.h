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
            cout << "�α��� ����!" << endl;
        }
    }
};

class ReadFile {
    string line;             // line: �޸����� ����, file: ������ �� ����, filename: �����̸�
    ifstream Readfile;
    ofstream Writefile;
    string filename;
public:
    ReadFile(const string& filename) : Readfile(filename) {
        this->filename = filename;
        if (!Readfile.is_open()) {
            cerr << "������ �����ϴ�." << filename << endl;
        }
    }

    bool CheckMember(const string& username, const string& password) {  // �α��� Ȯ�� �Լ�, ȸ������ �� ���̵� ����� ��ġ���� Ȯ�� 
        while (getline(Readfile, line)) {
            size_t info = line.find(' ');                               // info �� ���Ⱑ ��Ÿ���� ��ġ�� ã�� ����
            string Member_username = line.substr(0, info);              // Member_username = �߾�� ���� �κ�
            string Member_password = line.substr(info + 1);             // Member_password = ���� ���� �κ�

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