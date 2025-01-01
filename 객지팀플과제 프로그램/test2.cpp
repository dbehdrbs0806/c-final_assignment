#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <windows.h>
using namespace std;

void Draw_Ui() {                                 // ó�� ȭ���� �׸��� UI�Լ�
    int left = 20;
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

class Gold {                                   // ��� ȸ���� �̸������ ������ �ִ� Ŭ����
public:
    vector <string> gold_member;               // ��� ȸ�� ������ �̸����� ������ �ִ� ���ڿ� ����
    Gold() {                                   // Gold()������ �Լ��� ȸ�������� �о� ���Ϳ� �ִ� �Լ�
        ifstream file("gold.txt");
        string line;
        while (getline(file, line)) {
            gold_member.push_back(line);
        }
        file.close();
    }
    void Gold_update() {                      // gold_member������ �������� ���ο� ���ȸ���� txt������ ����� �Լ�
        ofstream writefile("temp.txt");
        for (const string& g : gold_member) {
                writefile << g << endl;
        }
        writefile.close();
        remove("gold.txt");
        rename("temp.txt", "gold.txt");
    }
};

class Silver {                                 // silverȸ������ �̸������ �����ִ� Ŭ����
public:
    vector <string> silver_member;             // silverȸ������ �̸������ ��Ȳ�� ������ �ְ� �����ϴ� ����(������)�迭
    Silver() {                                 // silver.txt �޸����� �о ���Ϳ��� �����ϴ� ������ �Լ�
        ifstream file("silver.txt");
        string line;
        while (getline(file, line)) {
            silver_member.push_back(line);
        }
        file.close();
    }
    void Silver_update() {                     // ���ο� silver_member������ ���ͷ� silver�޸����� �����ϰ� ����� �Լ�
        ofstream writefile("temp.txt");
        for (const string& s : silver_member) {
            writefile << s << endl;
        }
        writefile.close();
        remove("silver.txt");
        rename("temp.txt", "silver.txt");
    }
};

class Bronze {                                  // bronzeȸ������ �̸������ �����ִ� Ŭ����
public:      
    vector <string> bronze_member;              // bronzeȸ������ �̸������ ��Ȳ�� ������ �ְ� �����ϴ� ����(������)�迭
    Bronze() {                                  // bronze.txt �޸����� �о ���Ϳ��� �����ϴ� ������ �Լ�
        ifstream file("bronze.txt");
        string line;
        while (getline(file, line)) {
            bronze_member.push_back(line);
        }
        file.close();
    }
    void Bronze_update() {                    // ���ο� bronze_member������ ���ͷ� bronze�޸����� �����ϰ� ����� �Լ�
        ofstream writefile("temp.txt");
        for (const string& b : bronze_member) {
            writefile << b << endl;
        }
        writefile.close();
        remove("bronze.txt");
        rename("temp.txt", "bronze.txt");
    }
};

class Member : public Gold, public Silver, public Bronze {      // ���� username�� password ������ �����ִ� Member Ŭ����                
    friend void input(Member& member);       
protected:
    static string username, grade;                  // ȸ���� ���̵�, ���
    string password;                                // ȸ���� ��й�ȣ
    int grade_cal;                                  // ȸ�� ����� ����� ���� ����

public:
    void drawMenu() {                               // menu�� �׸��� �Լ�
        cout << setw(27) << "�α���" << setw(10) << "ȸ������" << setw(10) << "ȸ��Ż��" << setw(7) << "����" << endl;
        cout << endl;
    }
                                            // �� Ŭ������ �����ͷ� ������ ����� ���Ϳ� ��޿� �´� ����� ���� ���
    void checkgrade() {                     // �� Ŭ������ username�� ���� �̸��� ������ ����� �Ҵ�
        for (const string& b : bronze_member)
            if (b == username) {
                grade = "bronze";
                grade_cal = 0;
            }
        for (const string& g : gold_member)
            if (g == username) {
                grade = "gold";
                grade_cal = 5;
            }
        for (const string& s : silver_member)
            if (s == username) {
                grade = "silver";
                grade_cal = 3;
            }
    }

    void upgrade() {                               // ��޾��� �� ������ �Ҵ� �� ��޾��� ��Ű�� �Լ�
        if (grade == "bronze" && grade_cal >= 3) {
            auto it = find(bronze_member.begin(), bronze_member.end(), username);  // it���� silver_member���Ϳ� username�� ��ġ�� ��ȯ
            if (it != bronze_member.end()) {                                       // ���࿡ username�� ���Ϳ� ������ it�� end()�� ����Ŵ
                bronze_member.erase(it);                                           // it�� �̸��� ���Ϳ��� ����
            }
            silver_member.push_back(username);
            Bronze_update();
            Silver_update();
            grade = "silver";
        }
        else if (grade == "silver" && grade_cal >= 5) {
            auto it = find(silver_member.begin(), silver_member.end(), username);   // it���� silver_member���Ϳ� username�� ��ġ�� ��ȯ
            if (it != silver_member.end()) {                                        // ���࿡ username�� ���Ϳ� ������ it�� end()�� ����Ŵ
                silver_member.erase(it);                                            // it�� �̸��� ���Ϳ��� ����
            }
            gold_member.push_back(username);
            Silver_update();
            Gold_update();
            grade = "gold";
        }
    }

    bool login(string check = "login") {                      // login() �α��� �Լ�: ���̵�, ����� CheckMember()�Լ��� ����� �α����� ���� return
        bool log = CheckMember("login.txt", check);
        if ((check == "login") && (log == true)) {
            grade_cal += 1;
            return true;
        }
        else if ((check == "create") && (log == true)) {
            return true;
        }
        else {
            return false;
        }
    }

    // �޸��忡 ���̵�� ����� �ִ��� Ȯ���ϴ� �Լ� (�α��� Ȯ��, ȸ������ �� ���)
    bool CheckMember(const string& filename, string check) {
        string line;                                                     // �޸����� ������ �ϳ��� ���� ���� 
        ifstream Rf(filename);                                           // �޸����� ������ ifstream ���� (�б��������� ����)
        while (getline(Rf, line)) {
            size_t info = line.find(' ');                               // info �� ���Ⱑ ��Ÿ���� ��ġ�� ã�� ����
            string Member_username = line.substr(0, info);              // Member_username = �߾�� ���� �κ�
            string Member_password = line.substr(info + 1);             // Member_password = ���� ���� �κ�
            if (check == "login" && (Member_username == username && Member_password == password)) {  // �Ű������� �Է¹��� username(id), password(pw)�� �޸��忡�� ���� ���� �ִ��� Ȯ�� 
                Rf.close();
                return true;
            }
            else if ((check == "create") && (Member_username == username || Member_password == password)) {
                Rf.close();
                return true;
            }
        }
        Rf.close();
        return false;
    }

    // �Է¹��� ���̵�� ����� �޸��忡�� �����ϴ� �Լ�(ȸ��Ż�� �� ���)
    void DeleteUser(const string& filename) {
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
        remove((getUsername() + "_playlist.txt").c_str());
    }
    void CreateAccount() {                                      // ȸ������ �Լ�: ���̵�, ����� �޸��忡 �߰�
        ofstream outputFile("login.txt", ios::app);             // ���� ���� �߰� ���� ����
        outputFile << username << ' ' << password << endl;      // username�� password�� �޸��忡 �ۼ�
        outputFile.close();
        ofstream outputGrade("bronze.txt", ios::app);             // ���� ���� �߰� ���� ����
        outputGrade << username << endl;
        outputGrade.close();
    }
    static string getUsername() {
        return username;
    }
    static string getGrade() {
        return grade;
    }
};

void input(Member& member) {                      // �Է¿� ����� �Լ�
    cout << "id �Է�: ";
    cin >> member.username;
    cout << "��й�ȣ �Է�: ";
    cin >> member.password;
}

string Member::username = "";                     // static�������� ����ϱ� ���� �ʱ�ȭ
string Member::grade = "";

class Song {                                      // Ŭ���� �迭�� ����� �α⵵, �帣, �뷡���� Ŭ����                                              
public:
    int popularity;
    string genre;
    string songName;
};

class Ballad : public Song {
public:
    vector<Song> ballad;                          // �� �帣�� Ŭ�������� ���͹迭�� ������ �뷡�� ����
    Ballad() {                                    // �޸����� �о�� ���� �迭�� �뷡 ������ �ִ� �Լ�
        ifstream file("music.txt");
        string line;
        Song temp;
        while (getline(file, line)) {
            size_t info = line.find(' ');
            string songName_ballad = line.substr(0, info);
            string genre_ballad = line.substr(info + 1);                     // ���� �ڿ� �ִ°� �帣
            if (genre_ballad == "�߶��") {
                temp.songName = songName_ballad;
                temp.genre = genre_ballad;
                ballad.push_back(temp);
            }
        }
        file.close();
        RandomPopularity();
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
        ifstream file("music.txt");
        string line;
        Song temp;
        while (getline(file, line)) {
            size_t info = line.find(' ');
            string songName_hiphop = line.substr(0, info);
            string genre_hiphop = line.substr(info + 1);
            if (genre_hiphop == "����") {
                temp.songName = songName_hiphop;
                temp.genre = genre_hiphop;
                hiphop.push_back(temp);
            }
        }
        file.close();
        RandomPopularity();
    }
    void RandomPopularity() {
        srand(time(NULL));
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
        RandomPopularity();
    }
    void RandomPopularity() {
        srand(time(NULL));
        for (size_t i = 0; i < kpop.size(); i++) {
            int randomPopularity = rand() % 5 + 1;
            kpop[i].popularity = randomPopularity;
        }
    }
};

bool compare(const Song& a, const Song& b) {                 // ���� �α⵵�� ���� �뷡��¿��� sort�� ����� compare�Լ�
    return a.popularity > b.popularity;
}

class MusicPlayer {                                         // ��ü���� MusicPlayer�� ��ɵ��� �Լ��� �� �뷡Ŭ������ ��ü�� ������ ����ϴ� Ŭ����
public:
    Ballad song_ballad;
    Hiphop song_hiphop;
    Kpop song_kpop;

    void drawMenu() {
        cout << setw(20) << "�÷��̸���Ʈ " << setw(10) << "�뷡�߰�" << setw(10) << "�뷡����" << setw(10) << "�뷡����" << "  " << "�α��ε��ư���" << setw(7) << "����" << endl;
        cout << endl;
    }
    void OutputMusic() {                                   // �ݺ��ϸ� ����ϸ鼭 �α⵵�� ���� ������� �뷡�� ������� ����ϴ� �Լ�
        sort(song_ballad.ballad.begin(), song_ballad.ballad.end(), compare);
        sort(song_hiphop.hiphop.begin(), song_hiphop.hiphop.end(), compare);
        sort(song_kpop.kpop.begin(), song_kpop.kpop.end(), compare);
        cout << "�뷡 ����Ʈ(�α⵵ ��):" << endl;
        cout << "�߶��:";
        for (const Song& song : song_ballad.ballad) {
            cout << song.songName << ", ";
        }
        cout << endl;
        cout << "����:";
        for (const Song& song : song_hiphop.hiphop) {
            cout << song.songName << ", ";
        }
        cout << endl;
        cout << "Kpop:";
        for (const Song& song : song_kpop.kpop) {
            cout << song.songName << ", ";
        }
        cout << endl;
    }

    void OutputPlaylist() {                               // �� ���̵�� �ô� �÷��̸���Ʈ�� ������ ����ϴ� �Լ�
        wifstream playlistFile(Member::getUsername() + "_playlist.txt");
        cout << "���� �÷��̸���Ʈ: " << endl;
        wstring line;
        while (getline(playlistFile, line)) {
            wcout << line << " ";
        } 
        cout << endl;
        playlistFile.close();
    }
    void MakePlaylist() {                                // �÷��̸���Ʈ�� �������� ���� �� �����ϴ� �Լ�
        string playlistFilename = Member::getUsername() + "_playlist.txt";
        ofstream playlistFile(playlistFilename, ios::app);
        playlistFile.close();
    }


    void operator+(const string& songName) {                             // ������ �ߺ�+�� �̿��Ͽ� ������ �÷��̸���Ʈ�� �Է¹��� �뷡�� �߰��ϴ� �Լ�
        ofstream playlistFile(Member::getUsername() + "_playlist.txt", ios::app);                
        ifstream readfile(Member::getUsername() + "_playlist.txt");


        int songCount = 0;
        string line;
        while (getline(readfile, line)) {
            songCount++;
        }
        readfile.close();                    // �� ��ް� �뷡Ƚ���� songCout������ Ȱ���� �뷡Ƚ���� �����ϰ� �ϴ� �Լ�
        if (Member::getGrade() == "gold" && songCount >= 10) {
            cout << "��޿� ���� �÷��̸���Ʈ�� �뷡 �߰� Ƚ���� �Ѿ����ϴ�" << endl;
            cout << "����� �÷��ּ���" << endl;
            return;
        }
        else if (Member::getGrade() == "silver" && songCount >= 8) {
            cout << "��޿� ���� �÷��̸���Ʈ�� �뷡 �߰� Ƚ���� �Ѿ����ϴ�" << endl;
            cout << "����� �÷��ּ���" << endl;
            return;
        }
        else if (Member::getGrade() == "bronze" && songCount >= 5) {
            cout << "��޿� ���� �÷��̸���Ʈ�� �뷡 �߰� Ƚ���� �Ѿ����ϴ�" << endl;
            cout << "����� �÷��ּ���" << endl;
            return;
        }
        if (playlistFile.is_open()) {
            playlistFile << songName << endl;
            playlistFile.close();
        }
        cout << "�÷��̸���Ʈ�� �뷡�� �߰��Ǿ����ϴ�" << endl;
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
        remove((Member::getUsername() + "_playlist.txt").c_str());                         // ���� �Ű������� �ִ� �޸��� ����
        rename("temp.txt", (Member::getUsername() + "_playlist.txt").c_str());             // ���� �̸����� �޸��� �̸��� �ٲ�
    }
    bool CheckSongExist(const string& songName, string filename) {
        ifstream musicFile(filename);
        string line;
        while (getline(musicFile, line)) {
            size_t info = line.find(' ');
            string songNameFromFile = line.substr(0, info);
            if (songNameFromFile == songName) {
                musicFile.close();
                return true;
            }
        }
        musicFile.close();
        return false;
    }
};

void Login_Check(Member& member, int check) {
    string menu;                                         // �Է¹��� Menu ����    
                                               // �ؿ� checkgrade()�� Ȯ���� ���� ����
    while (true) {
        Draw_Ui();
        member.drawMenu();
        cout << setw(38) << "�Է�: ";
        cin >> menu;
        if (menu == "�α���") {                         // Menu�� �α����̸� input()�Լ��� ����� ���̵� ����� �Է¹ް� login()�Լ��� ����� ����Ȯ��
            input(member);
            if (check == 0) {
                member.checkgrade();                       // �Է¹��� ���̵�, ����� MemberŬ������ ����ǰ� checkgrade()�� ��� Ȯ��, ����
                check = 1;
            }
            if (member.login()) {
                member.upgrade();
                cout << "�α��� ����" << endl;
                cout << "���� ��� :" << member.getGrade() << endl;
                cout << "�÷��̸���Ʈ ������ �̵�" << endl;
                break;
            }
            else {
                cout << "�α��� ���� �ٽ� �Է��ϼ���" << endl;              // member->login()�� false��� ����ؼ� input()�� �ҷ� �Է¹޵��� �ݺ�
                do {                                                        // while�� �Ϸ��� �����ؼ� do-while�� �ذ�
                    input(member);
                    if (!member.login()) {
                        cout << "���� ȸ�������Դϴ�" << endl;
                        cout << "�ٽ� �Է��ϼ���" << endl;
                        cout << endl;
                    }
                } while (!member.login());
                cout << "�α��� ����" << endl;
                break;
            }
        }
        else if (menu == "ȸ������") {                                  // menu�� ȸ�������̸� input()�Լ��� ����� ���̵� ��� �Է¹ް� CreateAccount()����
            do {
                input(member);
                if (member.login("create")) {
                    cout << "�̹� �����ϴ� ȸ�������Դϴ�" << endl;
                    cout << "�ٽ� �Է��ϼ���." << endl;
                    cout << endl;
                }
            } while (member.login("create"));
            member.CreateAccount();
            cout << "ȸ������ ����" << endl;
            delete &member;
            continue;
        }
        else if (menu == "ȸ��Ż��") {                                 // menu�� ȸ��Ż��� input()�Լ��� ����� ���̵� ��� �Է¹ް� QuitAccount()����
            cout << "ȸ��Ż�� �� ���̵�� ����� �Է����ּ���" << endl;
            do {
                input(member);
                if (!member.login()) {
                    cout << "���� ȸ�������Դϴ�" << endl;
                    cout << "�ٽ� �Է��ϼ���" << endl;
                    cout << endl;
                }
            } while (!member.login());
            member.DeleteUser("login.txt");
            cout << "ȸ��Ż�� ����!" << endl;
            delete &member;
            continue;
        }
        else if (menu == "����") {
            exit(0);
        }
        else {
            cout << "�ùٸ� �޴��� �����ϼ���" << endl;
            continue;
        }
    }
}

void Playlist_Check(Member& member, MusicPlayer& mp) {
    string music_menu;
    string song_new;
    while (true) {
        Draw_Ui();
        mp.drawMenu();
        cout << setw(38) << "�Է�: ";
        cin >> music_menu;
        if (music_menu == "�÷��̸���Ʈ") {
            ifstream file(member.getUsername() + "_playlist.txt");
            if (file.good()) {                      // true�� ������ �ִ°� 
                mp.OutputPlaylist();
                continue;
            }
            else {                                  // false�� ���̵� �̸����ε� ������ ���°�
                cout << "�÷��̸���Ʈ�� �����ϴ�" << endl;
                cout << "�÷��̸���Ʈ�� ���� �����մϴ�" << endl;
                mp.MakePlaylist();
                continue;
            }
        }
        else if (music_menu == "�뷡�߰�") {
            cout << "�뷡 �Է�: ";
            cin >> song_new;
            if (mp.CheckSongExist(song_new, "music.txt")) {
                mp + song_new;
                continue;
            }
            else {
                cout << "�ٽ� �Է����ּ���" << endl;
                do {                                                        
                    cout << "�뷡 �Է�: ";
                    cin >> song_new;
                    if (!mp.CheckSongExist(song_new, "music.txt")) {
                        cout << "���� �뷡�Դϴ�" << endl;
                        cout << "�ٽ� �Է��ϼ���" << endl;
                        cout << endl;
                    }
                } while (!mp.CheckSongExist(song_new, "music.txt"));
                mp + song_new;
                cout << "�뷡�� �߰��Ǿ����ϴ�" << endl;
                continue;
            }
        }
        else if (music_menu == "�뷡����") {
            cout << "�뷡 �Է�: ";
            cin >> song_new;
            if (mp.CheckSongExist(song_new, member.getUsername() + "_playlist.txt")) {
                mp - song_new;
                cout << "�뷡�� �����Ǿ����ϴ�" << endl;
                continue;
            }
            else {
                cout << "�ٽ� �Է����ּ���" << endl;
                do {                                                      
                    cout << "�뷡 �Է�: ";
                    cin >> song_new;
                    if (!mp.CheckSongExist(song_new, member.getUsername() + "_playlist.txt")) {
                        cout << "���� �뷡�Դϴ�" << endl;
                        cout << "�ٽ� �Է��ϼ���" << endl;
                        cout << endl;
                    }
                } while (!mp.CheckSongExist(song_new, member.getUsername() + "_playlist.txt"));
                mp - song_new;
                cout << "�뷡�� �����Ǿ����ϴ�" << endl;
                continue;
            }
        }
        else if (music_menu == "�뷡����") {
            mp.OutputMusic();
            continue;
        }
        else if (music_menu == "�α��ε��ư���") {
            Login_Check(member, 1);
            system("cls");
        }
        else if (music_menu == "����") {
            exit(0);
        }
        else {
            cout << "�ùٸ� �޴��� �����ϼ���" << endl;
            continue;
        }
    }
}

int main() {                                   
    Member* member = new Member();
    Login_Check(*member, 0); // �α��� üũ �Լ�
    MusicPlayer mp;
    Playlist_Check(*member, mp); // �÷��̸���Ʈ �Լ�

    return 0;
}