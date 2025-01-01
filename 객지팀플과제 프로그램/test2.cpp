#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <windows.h>
using namespace std;

void Draw_Ui() {                                 // 처음 화면을 그리는 UI함수
    int left = 20;
    cout << setw(left) << "ㅡ";
    for (int i = 0; i < left; i++)
        cout << "ㅡ";
    cout << endl;
    cout << setw(left - 1) << "ㅣ" << setw(42) << "ㅣ" << endl;
    cout << setw(left - 1) << "ㅣ" << setw(32) << "객체 지향 음악 플레이어" << setw(10) << "ㅣ" << endl;
    cout << setw(left - 1) << "ㅣ" << setw(42) << "ㅣ" << endl;
    cout << setw(left) << "ㅡ";
    for (int i = 0; i < left; i++)
        cout << "ㅡ";
    cout << endl;
    cout << endl;
}

class Gold {                                   // 골드 회원의 이름명단을 가지고 있는 클래스
public:
    vector <string> gold_member;               // 골드 회원 파일의 이름들을 가지고 있는 문자열 벡터
    Gold() {                                   // Gold()생성자 함수는 회원파일을 읽어 벡터에 넣는 함수
        ifstream file("gold.txt");
        string line;
        while (getline(file, line)) {
            gold_member.push_back(line);
        }
        file.close();
    }
    void Gold_update() {                      // gold_member벡터의 내용으로 새로운 골드회원의 txt파일을 만드는 함수
        ofstream writefile("temp.txt");
        for (const string& g : gold_member) {
                writefile << g << endl;
        }
        writefile.close();
        remove("gold.txt");
        rename("temp.txt", "gold.txt");
    }
};

class Silver {                                 // silver회원들의 이름명단을 갖고있는 클래스
public:
    vector <string> silver_member;             // silver회원들의 이름명단의 상황을 가지고 있고 관리하는 벡터(문자형)배열
    Silver() {                                 // silver.txt 메모장을 읽어서 벡터에다 저장하는 생성자 함수
        ifstream file("silver.txt");
        string line;
        while (getline(file, line)) {
            silver_member.push_back(line);
        }
        file.close();
    }
    void Silver_update() {                     // 새로운 silver_member내용의 벡터로 silver메모장을 수정하고 만드는 함수
        ofstream writefile("temp.txt");
        for (const string& s : silver_member) {
            writefile << s << endl;
        }
        writefile.close();
        remove("silver.txt");
        rename("temp.txt", "silver.txt");
    }
};

class Bronze {                                  // bronze회원들의 이름명단을 갖고있는 클래스
public:      
    vector <string> bronze_member;              // bronze회원들의 이름명단의 상황을 가지고 있고 관리하는 벡터(문자형)배열
    Bronze() {                                  // bronze.txt 메모장을 읽어서 벡터에다 저장하는 생성자 함수
        ifstream file("bronze.txt");
        string line;
        while (getline(file, line)) {
            bronze_member.push_back(line);
        }
        file.close();
    }
    void Bronze_update() {                    // 새로운 bronze_member내용의 벡터로 bronze메모장을 수정하고 만드는 함수
        ofstream writefile("temp.txt");
        for (const string& b : bronze_member) {
            writefile << b << endl;
        }
        writefile.close();
        remove("bronze.txt");
        rename("temp.txt", "bronze.txt");
    }
};

class Member : public Gold, public Silver, public Bronze {      // 현재 username과 password 내용을 갖고있는 Member 클래스                
    friend void input(Member& member);       
protected:
    static string username, grade;                  // 회원의 아이디, 등급
    string password;                                // 회원의 비밀번호
    int grade_cal;                                  // 회원 등급을 계산할 변수 생성

public:
    void drawMenu() {                               // menu를 그리는 함수
        cout << setw(27) << "로그인" << setw(10) << "회원가입" << setw(10) << "회원탈퇴" << setw(7) << "종료" << endl;
        cout << endl;
    }
                                            // 현 클래스에 포인터로 가져온 등급의 벡터에 등급에 맞는 사람이 있을 경우
    void checkgrade() {                     // 현 클래스의 username과 같은 이름이 있으면 등급을 할당
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

    void upgrade() {                               // 등급업을 할 조건이 할당 시 등급업을 시키는 함수
        if (grade == "bronze" && grade_cal >= 3) {
            auto it = find(bronze_member.begin(), bronze_member.end(), username);  // it에는 silver_member벡터에 username의 위치를 반환
            if (it != bronze_member.end()) {                                       // 만약에 username이 벡터에 없으면 it는 end()를 가리킴
                bronze_member.erase(it);                                           // it에 이름을 벡터에서 삭제
            }
            silver_member.push_back(username);
            Bronze_update();
            Silver_update();
            grade = "silver";
        }
        else if (grade == "silver" && grade_cal >= 5) {
            auto it = find(silver_member.begin(), silver_member.end(), username);   // it에는 silver_member벡터에 username의 위치를 반환
            if (it != silver_member.end()) {                                        // 만약에 username이 벡터에 없으면 it는 end()를 가리킴
                silver_member.erase(it);                                            // it에 이름을 벡터에서 삭제
            }
            gold_member.push_back(username);
            Silver_update();
            Gold_update();
            grade = "gold";
        }
    }

    bool login(string check = "login") {                      // login() 로그인 함수: 아이디, 비번을 CheckMember()함수를 사용해 로그인의 유무 return
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

    // 메모장에 아이디와 비번이 있는지 확인하는 함수 (로그인 확인, 회원가입 시 사용)
    bool CheckMember(const string& filename, string check) {
        string line;                                                     // 메모장의 내용을 하나씩 담을 변수 
        ifstream Rf(filename);                                           // 메모장의 내용을 ifstream 형식 (읽기형식으로 읽음)
        while (getline(Rf, line)) {
            size_t info = line.find(' ');                               // info 에 띄어쓰기가 나타나는 위치를 찾아 저장
            string Member_username = line.substr(0, info);              // Member_username = 뜨어쓰기 이전 부분
            string Member_password = line.substr(info + 1);             // Member_password = 띄어쓰기 이후 부분
            if (check == "login" && (Member_username == username && Member_password == password)) {  // 매개변수로 입력받은 username(id), password(pw)를 메모장에서 같은 것이 있는지 확인 
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

    // 입력받은 아이디와 비번을 메모장에서 삭제하는 함수(회원탈퇴 시 사용)
    void DeleteUser(const string& filename) {
        string line;
        ifstream Readfile(filename);
        ofstream Writefile("temp.txt", ios::app);                   // temp.txt라는 파일을 ofstream(읽기모드)객체의              
        while (getline(Readfile, line)) {                           // (ios::app) 파일 끝에 추가하기로 사용
            size_t info = line.find(' ');
            string Member_username = line.substr(0, info);
            string Member_password = line.substr(info + 1);

            if (Member_username != username || Member_password != password) {   // 입력받은 아이디, 비번과 다른 내용들만 임시temp.txt메모장에 저장
                Writefile << line << endl;
            }
        }
        Readfile.close();
        Writefile.close();
        remove(filename.c_str());                                                // 기존 매개변수에 있는 메모장 삭제
        rename("temp.txt", filename.c_str());                                    // 원래 이름으로 메모장 이름을 바꿈
        remove((getUsername() + "_playlist.txt").c_str());
    }
    void CreateAccount() {                                      // 회원가입 함수: 아이디, 비번을 메모장에 추가
        ofstream outputFile("login.txt", ios::app);             // 파일 끝에 추가 모드로 열기
        outputFile << username << ' ' << password << endl;      // username과 password를 메모장에 작성
        outputFile.close();
        ofstream outputGrade("bronze.txt", ios::app);             // 파일 끝에 추가 모드로 열기
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

void input(Member& member) {                      // 입력에 사용할 함수
    cout << "id 입력: ";
    cin >> member.username;
    cout << "비밀번호 입력: ";
    cin >> member.password;
}

string Member::username = "";                     // static변수들을 사용하기 위한 초기화
string Member::grade = "";

class Song {                                      // 클래스 배열로 사용할 인기도, 장르, 노래제목 클래스                                              
public:
    int popularity;
    string genre;
    string songName;
};

class Ballad : public Song {
public:
    vector<Song> ballad;                          // 각 장르의 클래스에서 벡터배열을 생성해 노래를 넣음
    Ballad() {                                    // 메모장을 읽어와 벡터 배열에 노래 제목을 넣는 함수
        ifstream file("music.txt");
        string line;
        Song temp;
        while (getline(file, line)) {
            size_t info = line.find(' ');
            string songName_ballad = line.substr(0, info);
            string genre_ballad = line.substr(info + 1);                     // 띄어쓰기 뒤에 있는게 장르
            if (genre_ballad == "발라드") {
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
            if (genre_hiphop == "힙합") {
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

bool compare(const Song& a, const Song& b) {                 // 이후 인기도에 따른 노래출력에서 sort에 사용할 compare함수
    return a.popularity > b.popularity;
}

class MusicPlayer {                                         // 전체적인 MusicPlayer의 기능들의 함수와 각 노래클래스의 객체를 생성해 사용하는 클래스
public:
    Ballad song_ballad;
    Hiphop song_hiphop;
    Kpop song_kpop;

    void drawMenu() {
        cout << setw(20) << "플레이리스트 " << setw(10) << "노래추가" << setw(10) << "노래삭제" << setw(10) << "노래보기" << "  " << "로그인돌아가기" << setw(7) << "종료" << endl;
        cout << endl;
    }
    void OutputMusic() {                                   // 반복하며 출력하면서 인기도가 높은 순서대로 노래를 순서대로 출력하는 함수
        sort(song_ballad.ballad.begin(), song_ballad.ballad.end(), compare);
        sort(song_hiphop.hiphop.begin(), song_hiphop.hiphop.end(), compare);
        sort(song_kpop.kpop.begin(), song_kpop.kpop.end(), compare);
        cout << "노래 리스트(인기도 순):" << endl;
        cout << "발라드:";
        for (const Song& song : song_ballad.ballad) {
            cout << song.songName << ", ";
        }
        cout << endl;
        cout << "힙합:";
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

    void OutputPlaylist() {                               // 내 아이디와 맡는 플레이리스트를 가져와 출력하는 함수
        wifstream playlistFile(Member::getUsername() + "_playlist.txt");
        cout << "나의 플레이리스트: " << endl;
        wstring line;
        while (getline(playlistFile, line)) {
            wcout << line << " ";
        } 
        cout << endl;
        playlistFile.close();
    }
    void MakePlaylist() {                                // 플레이리스트가 존재하지 않을 시 생성하는 함수
        string playlistFilename = Member::getUsername() + "_playlist.txt";
        ofstream playlistFile(playlistFilename, ios::app);
        playlistFile.close();
    }


    void operator+(const string& songName) {                             // 연산자 중복+를 이용하여 생성한 플레이리스트에 입력받은 노래를 추가하는 함수
        ofstream playlistFile(Member::getUsername() + "_playlist.txt", ios::app);                
        ifstream readfile(Member::getUsername() + "_playlist.txt");


        int songCount = 0;
        string line;
        while (getline(readfile, line)) {
            songCount++;
        }
        readfile.close();                    // 각 등급과 노래횟수를 songCout변수를 활용해 노래횟수를 조절하게 하는 함수
        if (Member::getGrade() == "gold" && songCount >= 10) {
            cout << "등급에 따른 플레이리스트의 노래 추가 횟수를 넘었습니다" << endl;
            cout << "등급을 올려주세요" << endl;
            return;
        }
        else if (Member::getGrade() == "silver" && songCount >= 8) {
            cout << "등급에 따른 플레이리스트의 노래 추가 횟수를 넘었습니다" << endl;
            cout << "등급을 올려주세요" << endl;
            return;
        }
        else if (Member::getGrade() == "bronze" && songCount >= 5) {
            cout << "등급에 따른 플레이리스트의 노래 추가 횟수를 넘었습니다" << endl;
            cout << "등급을 올려주세요" << endl;
            return;
        }
        if (playlistFile.is_open()) {
            playlistFile << songName << endl;
            playlistFile.close();
        }
        cout << "플레이리스트에 노래가 추가되었습니다" << endl;
    }
    void operator-(const string& songName) {       // 연산자 중복-를 이용하여 플레이리스트에 입력받은 노래를 제거하는
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
        remove((Member::getUsername() + "_playlist.txt").c_str());                         // 기존 매개변수에 있는 메모장 삭제
        rename("temp.txt", (Member::getUsername() + "_playlist.txt").c_str());             // 원래 이름으로 메모장 이름을 바꿈
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
    string menu;                                         // 입력받을 Menu 변수    
                                               // 밑에 checkgrade()를 확인을 위한 변수
    while (true) {
        Draw_Ui();
        member.drawMenu();
        cout << setw(38) << "입력: ";
        cin >> menu;
        if (menu == "로그인") {                         // Menu가 로그인이면 input()함수를 사용해 아이디 비번을 입력받고 login()함수를 사용해 유무확인
            input(member);
            if (check == 0) {
                member.checkgrade();                       // 입력받은 아이디, 비번이 Member클래스에 저장되고 checkgrade()로 등급 확인, 선언
                check = 1;
            }
            if (member.login()) {
                member.upgrade();
                cout << "로그인 성공" << endl;
                cout << "나의 등급 :" << member.getGrade() << endl;
                cout << "플레이리스트 페이지 이동" << endl;
                break;
            }
            else {
                cout << "로그인 실패 다시 입력하세요" << endl;              // member->login()가 false라면 계속해서 input()를 불러 입력받도록 반복
                do {                                                        // while로 하려다 실패해서 do-while로 해결
                    input(member);
                    if (!member.login()) {
                        cout << "없는 회원정보입니다" << endl;
                        cout << "다시 입력하세요" << endl;
                        cout << endl;
                    }
                } while (!member.login());
                cout << "로그인 성공" << endl;
                break;
            }
        }
        else if (menu == "회원가입") {                                  // menu가 회원가입이면 input()함수를 사용해 아이디 비번 입력받고 CreateAccount()실행
            do {
                input(member);
                if (member.login("create")) {
                    cout << "이미 존재하는 회원정보입니다" << endl;
                    cout << "다시 입력하세요." << endl;
                    cout << endl;
                }
            } while (member.login("create"));
            member.CreateAccount();
            cout << "회원가입 성공" << endl;
            delete &member;
            continue;
        }
        else if (menu == "회원탈퇴") {                                 // menu가 회원탈퇴면 input()함수를 사용해 아이디 비번 입력받고 QuitAccount()실행
            cout << "회원탈퇴 할 아이디와 비번을 입력해주세요" << endl;
            do {
                input(member);
                if (!member.login()) {
                    cout << "없는 회원정보입니다" << endl;
                    cout << "다시 입력하세요" << endl;
                    cout << endl;
                }
            } while (!member.login());
            member.DeleteUser("login.txt");
            cout << "회원탈퇴 성공!" << endl;
            delete &member;
            continue;
        }
        else if (menu == "종료") {
            exit(0);
        }
        else {
            cout << "올바른 메뉴를 선택하세요" << endl;
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
        cout << setw(38) << "입력: ";
        cin >> music_menu;
        if (music_menu == "플레이리스트") {
            ifstream file(member.getUsername() + "_playlist.txt");
            if (file.good()) {                      // true면 파일이 있는거 
                mp.OutputPlaylist();
                continue;
            }
            else {                                  // false면 아이디 이름으로된 파일이 없는거
                cout << "플레이리스트가 없습니다" << endl;
                cout << "플레이리스트를 새로 생성합니다" << endl;
                mp.MakePlaylist();
                continue;
            }
        }
        else if (music_menu == "노래추가") {
            cout << "노래 입력: ";
            cin >> song_new;
            if (mp.CheckSongExist(song_new, "music.txt")) {
                mp + song_new;
                continue;
            }
            else {
                cout << "다시 입력해주세요" << endl;
                do {                                                        
                    cout << "노래 입력: ";
                    cin >> song_new;
                    if (!mp.CheckSongExist(song_new, "music.txt")) {
                        cout << "없는 노래입니다" << endl;
                        cout << "다시 입력하세요" << endl;
                        cout << endl;
                    }
                } while (!mp.CheckSongExist(song_new, "music.txt"));
                mp + song_new;
                cout << "노래가 추가되었습니다" << endl;
                continue;
            }
        }
        else if (music_menu == "노래삭제") {
            cout << "노래 입력: ";
            cin >> song_new;
            if (mp.CheckSongExist(song_new, member.getUsername() + "_playlist.txt")) {
                mp - song_new;
                cout << "노래가 삭제되었습니다" << endl;
                continue;
            }
            else {
                cout << "다시 입력해주세요" << endl;
                do {                                                      
                    cout << "노래 입력: ";
                    cin >> song_new;
                    if (!mp.CheckSongExist(song_new, member.getUsername() + "_playlist.txt")) {
                        cout << "없는 노래입니다" << endl;
                        cout << "다시 입력하세요" << endl;
                        cout << endl;
                    }
                } while (!mp.CheckSongExist(song_new, member.getUsername() + "_playlist.txt"));
                mp - song_new;
                cout << "노래가 삭제되었습니다" << endl;
                continue;
            }
        }
        else if (music_menu == "노래보기") {
            mp.OutputMusic();
            continue;
        }
        else if (music_menu == "로그인돌아가기") {
            Login_Check(member, 1);
            system("cls");
        }
        else if (music_menu == "종료") {
            exit(0);
        }
        else {
            cout << "올바른 메뉴를 선택하세요" << endl;
            continue;
        }
    }
}

int main() {                                   
    Member* member = new Member();
    Login_Check(*member, 0); // 로그인 체크 함수
    MusicPlayer mp;
    Playlist_Check(*member, mp); // 플레이리스트 함수

    return 0;
}