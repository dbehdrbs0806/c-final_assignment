#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class LeadFile {
    string line;             // line: �޸����� ����, file: ������ �� ����, filename: �����̸�
    ifstream Readfile;
    ofstream Writefile;
    string filename;
public:
    LeadFile() {}
    LeadFile(const string& filename) : Readfile(filename) {
        this->filename = filename;
        if (!Readfile.is_open()) {
            cerr << "������ �����ϴ�." << filename << endl;
        }
    }
    bool CheckMember(const string& username, const string& password) {  // �α��� Ȯ�� �Լ�, ȸ������ �� ���̵� ����� ��ġ���� Ȯ�� 
        ifstream inputFile("Melon.txt");
        while (getline(Readfile, line)) {
            size_t info = line.find(' ');                               // info �� ���Ⱑ ��Ÿ���� ��ġ�� ã�� ����
            string Member_username = line.substr(0, info);              // Member_username = �߾�� ���� �κ�
            string Member_password = line.substr(info + 1);             // Member_password = ���� ���� �κ�

            if (Member_username == username && Member_password == password) {
                return true;
            }
            else {
                return false;
            }
        }
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
    }
};


int main() {
    LeadFile test("login.txt");
    string a, b;
    cout << "id�Է�: ";
    cin >> a;
    cout << "pw�Է�: ";
    cin >> b;
    bool c = test.CheckMember(a, b);
    cout << c;
    //test.DeleteUser(a, b);

}