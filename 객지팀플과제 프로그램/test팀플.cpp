#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// �޸��忡 ���̵�� ����� �ִ��� Ȯ���ϴ� �Լ� (�α��� Ȯ��, ȸ������ �� ���)
bool CheckMember(const string& filename, const string& username, const string& password) {
    string line;                                                     // �޸����� ������ �ϳ��� ���� ���� 
    ifstream Rf(filename);                                           // �޸����� ������ ifstream ���� (�б��������� ����)
    while (getline(Rf, line)) {
        size_t info = line.find(' ');                               // info �� ���Ⱑ ��Ÿ���� ��ġ�� ã�� ����
        string Member_username = line.substr(0, info);              // Member_username = �߾�� ���� �κ�
        string Member_password = line.substr(info + 1);             // Member_password = ���� ���� �κ�
        if (Member_username == username && Member_password == password) {  // �Ű������� �Է¹��� username(id), password(pw)�� �޸��忡�� ���� ���� �ִ��� Ȯ�� 
            Rf.close();
            return true;
        }
    }
    Rf.close();
    return false;
}

// �Է¹��� ���̵�� ����� �޸��忡�� �����ϴ� �Լ�(ȸ��Ż�� �� ���)
void DeleteUser(const string& filename, const string& username, const string& password) {
    string line;
    ifstream Readfile(filename);
    ofstream Writefile("temp.txt", ios::app);                   // temp.txt��� ������ ofstream(�б���)��ü��              
    while (getline(Readfile, line)) {                           // (ios::app) ���� ���� �߰��ϱ�� ���
        size_t info = line.find(' ');
        string Member_username = line.substr(0, info);
        string Member_password = line.substr(info + 1);

        if (Member_username != username || Member_password != password) {   // �Է¹��� ���̵�, ����� �ٸ� ����鸸 �ӽ�temp.txt�޸��忡 ����
            Writefile << line << endl;
        }
    }
    Readfile.close();
    Writefile.close();
    remove(filename.c_str());                                                // ���� �Ű������� �ִ� �޸��� ����
    rename("temp.txt", filename.c_str());                                    // ���� �̸����� �޸��� �̸��� �ٲ�
}

class Ui {                                // ȭ��׸��� Ui �߻� Ŭ����
protected:
    int left = 20;
public:
    Ui() {                                // ó�� ȭ���� �׸��� Ui �κ��� �����ڿ� ������ �κ�
        cout << setw(left) << "��";
        for (int i = 0; i < left; i++)
            cout << "��";
        cout << endl;
        cout << setw(left - 1) << "��" << setw(42) << "��" << endl;
        cout << setw(left - 1) << "��" << setw(32) << "��ü ���� ���� �÷��̾�" << setw(10) << "��" << endl;
        cout << setw(left - 1) << "��" << setw(42) << "��" << endl;
        cout << setw(left) << "��";
        for (int i = 0; i < left; i++)
            cout << "��";
        cout << endl;
        cout << endl;
    }
    virtual void drawMenu() = 0;         // ���� ���� �޴��� �׸��� �Լ��� �����Լ��� ����
};

class Gold {
public:
    vector <string> gold_member;                        
    Gold() {
        ifstream file("gold.txt");
        string line;
        while (getline(file, line)) {   
                gold_member.push_back(line);
        }
        file.close();
    }
    ~Gold() {
        ifstream readfile("gold.txt");
        ofstream writefile("temp.txt", ios::app);
        string line;
        for (const string& g : gold_member) {
            while (getline(readfile, line)) {
                if (g != line) {
                    writefile << line << endl;
                }
            }
        }
        readfile.close();
        writefile.close();
        remove("gold.txt");
        rename("temp.txt", "gold.txt");
    }
};

class Silver {
public:
    vector <string> silver_member;
    Silver() {
        ifstream file("silver.txt");
        string line;
        while (getline(file, line)) {
            silver_member.push_back(line);
        }
        file.close();
    }
    ~Silver() {
        ifstream readfile("silver.txt");
        ofstream writefile("temp.txt", ios::app);
        string line;
        for (const string& s : silver_member) {
            while (getline(readfile, line)) {
                if (s != line) {
                    writefile << line << endl;
                }
            }
        }
        readfile.close();
        writefile.close();
        remove("silver.txt");
        rename("temp.txt", "silver.txt");
    }
};

class Bronze {
public:
    vector <string> bronze_member;
    Bronze() {
        ifstream file("bronze.txt");
        string line;
        while (getline(file, line)) {
            bronze_member.push_back(line);
        }
        file.close();
    }
    ~Bronze() {
        ifstream readfile("bronze.txt");
        ofstream writefile("temp.txt", ios::app); 
        string line;
        for (const string& b : bronze_member) {
            while (getline(readfile, line)) {
                if (b != line) {
                    writefile << line << endl;
                }
            }
        }
        readfile.close();
        writefile.close();
        remove("bronze.txt");
        rename("temp.txt", "bronze.txt");
    }
};

class Member : public Ui, public Gold, public Silver, public Bronze {                   // �α����Ҷ� ȸ���� ���̵�, ���, ȸ����� �׸��� �̿��� �Լ����� Ŭ����
    friend void input(Member& member);       // input()�Լ��� ����� ���̵�� ����� �Է¹��� �� class Member�� �����ϱ� ����
protected:
    static string username, grade;
    string password;                                // ȸ���� ���̵�, ���, ���
    int grade_cal = 0;                           // ȸ�� ����� ����� ���� ����

    Gold* gd;
    Silver* sr;
    Bronze* be;
public:
    Member() : Ui() {                        // �θ� Ŭ������ Ui�� �����ڰ� ���� �����
        drawMenu();                          // �ؿ��� �������� drawMenu()�� �����ڿ��� ���
    }
    void drawMenu() {                        // drawMenu() ������
        cout << setw(27) << "�α���" << setw(10) << "ȸ������" << setw(10) << "ȸ��Ż��" << setw(7) << "����" << endl;
        cout << endl;
    }

    void checkgrade() {
        for (const string& b : be->bronze_member)
            if (b == username || grade_cal < 3) {
                grade = "bronze";
                grade_cal = 0;
            }
        for (const string& g : gd->gold_member)
            if (g == username) {
                grade = "gold";
                grade_cal = 5;
            }
        for (const string& s : sr->silver_member)
            if (s == username) {
                grade = "silver";
                grade_cal = 3;
            }
    }

    void upgrade() {
        if (grade == "bronze" && grade_cal >= 3) {
            auto it = find(be->bronze_member.begin(), be->bronze_member.end(), username);
            if (it != be->bronze_member.end()) {
                be->bronze_member.erase(it);
            }
            sr->silver_member.push_back(username);
        }
        else if (grade == "silver" && grade_cal >= 5) {
            auto it = find(sr->silver_member.begin(), sr->silver_member.end(), username);
            if (it != sr->silver_member.end()) {
                sr->silver_member.erase(it);
            }
            gd->gold_member.push_back(username);
        }
    }

    bool login() {                           // login() �α��� �Լ�: ���̵�, ����� CheckMember()�Լ��� ����� �α����� ���� return
        bool log = CheckMember("login.txt", username, password);
        if (log == true) {
            grade_cal++;
            upgrade();
            return true;
        }
        else {
            return false;
        }
    }

    void CreateAccount() {                                  // ȸ������ �Լ�: ���̵�, ����� �޸��忡 �߰�
        ofstream outputFile("login.txt", ios::app);         // ���� ���� �߰� ���� ����
        outputFile << username << ' ' << password << "\n";  // username�� password�� �޸��忡 �ۼ�
        outputFile.close();
    }
    void QuitAccount() {                                         // ȸ��Ż�� �Լ�: ���̵�, ����� �޸��忡�� ����
        DeleteUser("login.txt", this->username, this->password); // DeleteUser �Լ��� ����� ���̵�, ����� ����
    }
    static string getUsername() {
        return username;
    }
    static string getGrade() {
        return grade;
    }
};

string Member::username = "";
string Member::grade= "";


void input(Member& member) {
    cout << "id �Է�: ";
    cin >> member.username;
    cout << "��й�ȣ �Է�: ";
    cin >> member.password;
}

class Song {                                                               // �α⵵:popularity�� �뷡�̸�: songName�� ���� Ŭ���� Song
public:
    int popularity;
    string genre;
    string songName;
};

class Ballad : public Song {
public:
    vector<Song> ballad;
    Ballad() {
        readFile();
        RandomPopularity();
    }
    void readFile() {
        ifstream file("music.txt");
        string line;
        Song temp;
        while (getline(file, line)) {
            size_t info = line.find(' ');
            string songName_ballad = line.substr(0, info);
            string genre_ballad = line.substr(info + 1);
            if (genre_ballad == "Ballad") {
                temp.songName = songName_ballad;
                temp.genre = genre_ballad;
                ballad.push_back(temp);
            }
        }
        file.close();
    }
    void RandomPopularity() {
        srand(time(NULL));
        for (size_t i = 0; i < ballad.size(); i++) {
            int randomPopularity = rand() % 5 + 1;
            ballad[i].popularity = randomPopularity;
        }
    }
};
class Hiphop : public Song {
public:
    vector<Song> hiphop;
    Hiphop() {
        readFile();
        RandomPopularity();
    }
    void readFile() {
        ifstream file("music.txt");
        string line;
        Song temp;
        while (getline(file, line)) {
            size_t info = line.find(' ');
            string songName_hiphop = line.substr(0, info);
            string genre_hiphop = line.substr(info + 1);
            if (genre_hiphop == "Hiphop") {
                temp.songName = songName_hiphop;
                temp.genre = genre_hiphop;
                hiphop.push_back(temp);
            }
        }
        file.close();
    }
    void RandomPopularity() {
        srand(time(0));
        for (size_t i = 0; i < hiphop.size(); i++) {
            int randomPopularity = rand() % 5 + 1;
            hiphop[i].popularity = randomPopularity;
        }
    }
};
class Kpop : public Song {
public:
    vector<Song> kpop;
    Kpop() {
        readFile();
        RandomPopularity();
    }
    void readFile() {
        ifstream file("music.txt");
        string line;
        Song temp;
        while (getline(file, line)) {
            size_t info = line.find(' ');
            string songName_kpop = line.substr(0, info);
            string genre_kpop = line.substr(info + 1);
            if (genre_kpop == "kpop") {
                temp.songName = songName_kpop;
                temp.genre = genre_kpop;
                kpop.push_back(temp);
            }
        }
        file.close();
    }
    void RandomPopularity() {
        srand(time(0));
        for (size_t i = 0; i < kpop.size(); i++) {
            int randomPopularity = rand() % 5 + 1;
            kpop[i].popularity = randomPopularity;
        }
    }
};

bool compare(const Song& a, const Song& b) {
    return a.popularity > b.popularity;
}

class MusicPlayer : public Ui {
public:
    Ballad song_ballad;
    Hiphop song_hiphop;
    Kpop song_kpop;

    MusicPlayer() {
        void drawMenu();
    }
    void drawMenu() {
        cout << setw(27) << "�� �÷��̸���Ʈ ����(���� �Է�)" << setw(10) << "�÷��̸���Ʈ�� �뷡 �߰�����(�뷡�߰�, �뷡���� �Է�)" << setw(10) << "�뷡����" << setw(7) << "����" << endl;
        cout << setw(31) << "(���� �Է�)" << setw(13) << "(�뷡�߰�, �뷡���� �Է�)" << endl;
        cout << endl;
    }

    void OutputMusic() {                                                  // songList�� �ݺ��ϸ� ����ϸ鼭 �α⵵�� ���� ������� �뷡�� ������� ����ϴ� �Լ�
        sort(song_ballad.ballad.begin(), song_ballad.ballad.end(), compare);
        sort(song_hiphop.hiphop.begin(), song_hiphop.hiphop.end(), compare);
        sort(song_kpop.kpop.begin(), song_kpop.kpop.end(), compare);
        cout << "�뷡 ����Ʈ(�α⵵ ��):" << endl;
        cout << "�߶��:" << endl;
        for (const Song& song : song_ballad.ballad) {
            cout << song.songName << ", " << endl;
        }
        cout << "\n����:" << endl;
        for (const Song& song : song_hiphop.hiphop) {
            cout << song.songName << ", " << endl;
        }
        cout << "\nKpop:" << endl;
        for (const Song& song : song_kpop.kpop) {
            cout << song.songName << ", " << endl;
        }
    }
    void OutputPlaylist() {
        ifstream playlistFile(Member::getUsername() + "_playlist.txt");
        cout << "���� �÷��̸���Ʈ: " << endl;
        string line;
        while (getline(playlistFile, line)) {
            cout << line << " ";
        }
        playlistFile.close();
    }
    void MakePlaylist() {
        string playlistFilename = Member::getUsername() + "_playlist.txt";
        ofstream playlistFile(playlistFilename, ios::app);
        playlistFile.close();
    }
    void operator+(const string& songName) {                             // ������ �ߺ�+�� �̿��Ͽ� ������ �÷��̸���Ʈ�� �Է¹��� �뷡�� �߰��ϴ� �Լ�
        ofstream playlistFile(Member::getUsername() + "_playlist.txt", ios::app);                 // �뷡 �߰� �� ȸ���� ��޿� ���� �߰� ���� Ƚ�� �κ��� �Լ��� �־����
        
        ifstream readfile(Member::getUsername() + "_playlist.txt");
        int songCount = 0;
        string line;
        while (getline(readfile, line)) {
            songCount++;
        }
        readfile.close();

        if (Member::getGrade() == "���" && songCount > 10) {
            cout << "��޿� ���� �÷��̸���Ʈ�� �뷡 �߰� Ƚ���� �Ѿ����ϴ�" << endl;
            cout << "����� �÷��ּ���" << endl;
            return;
        }

        else if (Member::getGrade() == "�ǹ�" && songCount > 8) {
            cout << "��޿� ���� �÷��̸���Ʈ�� �뷡 �߰� Ƚ���� �Ѿ����ϴ�" << endl;
            cout << "����� �÷��ּ���" << endl;
            return;
        }

        else if (Member::getGrade() == "�����" && songCount > 5) {
            cout << "��޿� ���� �÷��̸���Ʈ�� �뷡 �߰� Ƚ���� �Ѿ����ϴ�" << endl;
            cout << "����� �÷��ּ���" << endl;
            return;
        }

        if (playlistFile.is_open()) {
            playlistFile << songName << endl;
            playlistFile.close();
            cout << "�÷��̸���Ʈ�� �뷡�� �߰��Ǿ����ϴ�." << endl;
        }
    }
    void operator-(const string& songName) {       // ������ �ߺ�-�� �̿��Ͽ� �÷��̸���Ʈ�� �Է¹��� �뷡�� �����ϴ�
        string line;
        ifstream Readfile(Member::getUsername() + "_playlist.txt");
        ofstream Writefile("temp.txt", ios::app);                   
     
        while (getline(Readfile, line)) {                           
            if (line != songName) {         
                Writefile << line << endl;
            }
        }
        Readfile.close();
        Writefile.close();
        remove((Member::getUsername() + "_playlist.txt").c_str());                                                // ���� �Ű������� �ִ� �޸��� ����
        rename("temp.txt", (Member::getUsername() + "_playlist.txt").c_str());                                    // ���� �̸����� �޸��� �̸��� �ٲ�
    }
};

/*if (menu == "�뷡����") {
    player->RandomPopularity();

    do {
        player->getMusic();
        player->OutputMusic();
        cout << setw(38) << "�帣�� ����(�߶��, ����, K - pop):";

        player->genre_sort();

    } while (menu == "�ڷ�");
}
if (menu == "�÷��̸���") {
    player->MakePlaylist();
    while (menu == "����") {
        if (menu == "�߰�") {
            if (menu != song->songName)
                cout << "���� �뷡�Դϴ�" << endl;
            else if (menu == playlist->)
                cout << "�̹� �÷��̸���Ʈ�� �����ϴ� �뷡�Դϴ�." << endl;
            else
                playlist + song->songName;
        }
        else if (menu == "����") {
            if (menu != playlist->song)
                playlist - song->songName;
        }
    }*/

int main() {
    string menu;                                         // �Է¹��� Menu ���� 
    Member* member = nullptr;                            // �ʱ⿡ ȸ�� ��ü�� ���� ó�� (nullptr�� �� Ȱ���غ���)

    while (true) {
        member = new Member();
        cout << setw(38) << "�Է�: ";
        cin >> menu;
        if (menu == "�α���") {                         // Menu�� �α����̸� input()�Լ��� ����� ���̵� ����� �Է¹ް� login()�Լ��� ����� ����Ȯ��
            input(*member);
            if (member->login()) {
                cout << "�α��� ����" << endl;
                // �α��� ���� �� �÷��̸���Ʈ ���κ�, ��޵� ���ķ� �ؾ���

            }
            else {
                cout << "�α��� ���� �ٽ� �Է��ϼ���" << endl;              // member->login()�� false��� ����ؼ� input()�� �ҷ� �Է¹޵��� �ݺ�
                do {                                                        // while�� �Ϸ��� �����ؼ� do-while�� �ذ�
                    input(*member);
                    if (!member->login()) {
                        cout << "���� ȸ�������Դϴ�" << endl;
                        cout << "�ٽ� �Է��ϼ���" << endl;
                        cout << endl;
                    }
                } while (!member->login());
                cout << "�α��� ����" << endl;
                delete member;
                continue;
            }
        }
        else if (menu == "ȸ������") {                                  // menu�� ȸ�������̸� input()�Լ��� ����� ���̵� ��� �Է¹ް� CreateAccount()����
            do {
                input(*member);
                if (member->login()) {
                    cout << "�̹� �����ϴ� ȸ�������Դϴ�" << endl;
                    cout << "�ٽ� �Է��ϼ���." << endl;
                    cout << endl;
                }
            } while (member->login());
            member->CreateAccount();
            cout << "ȸ������ ����" << endl;
            delete member;
            continue;
        }
        else if (menu == "ȸ��Ż��") {                                 // menu�� ȸ��Ż��� input()�Լ��� ����� ���̵� ��� �Է¹ް� QuitAccount()����
            cout << "ȸ��Ż�� �� ���̵�� ����� �Է����ּ���" << endl;
            do {
                input(*member);
                if (!member->login()) {
                    cout << "���� ȸ�������Դϴ�" << endl;
                    cout << "�ٽ� �Է��ϼ���" << endl;
                    cout << endl;
                }
            } while (!member->login());
            member->QuitAccount();
            cout << "ȸ��Ż�� ����!" << endl;
            delete member;
            continue;
        }
        else if (menu == "����") {
            return 0;
        }
        else {
            cout << "�ùٸ� �޴��� �����ϼ���" << endl;
            continue;
        }
    }
    return 0;
}