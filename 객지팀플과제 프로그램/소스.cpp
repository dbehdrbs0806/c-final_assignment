#include<iostream>
#include<fstream>
#include<string>

using namespace std;


class Login { //�α��� �߻�Ŭ����
protected:
    string id;
    string password;
public:
    Login() : id(id), password(password) {}
    virtual void signUp() {} // ȸ������ �����Լ�
    virtual void login() {} // �α��� �����Լ�
};

class Id : public Login {
private:
    string id, password;
    string song;
    string degree; // ���
public:
    Id() : Login(), id(id), password(password), song(song), degree(degree) {
        cout << "���̵� �Է��ϼ���: " << endl;
        cin >> id;
        cout << "��й�ȣ�� �Է��ϼ���: " << endl;
        cin >> password;
        degree = "�����";
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
        cout << "ID�� �Է��ϼ���: ";
        cin >> id;
        cout << "��й�ȣ�� �Է��ϼ���: ";
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
                cout << "�α��� ����!" << endl;
            else
                cout << "ID �Ǵ� ��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
            readFile.close();
        }
        void addSong() {
            ofstream writeFile;
            writeFile.open(id + ".txt");
            cout << "���ϴ� �뷡�� �Է��ϼ���: " << endl;
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