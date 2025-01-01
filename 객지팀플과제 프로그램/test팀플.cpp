#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 메모장에 아이디와 비번이 있는지 확인하는 함수 (로그인 확인, 회원가입 시 사용)
bool CheckMember(const string& filename, const string& username, const string& password) {
    string line;                                                     // 메모장의 내용을 하나씩 담을 변수 
    ifstream Rf(filename);                                           // 메모장의 내용을 ifstream 형식 (읽기형식으로 읽음)
    while (getline(Rf, line)) {
        size_t info = line.find(' ');                               // info 에 띄어쓰기가 나타나는 위치를 찾아 저장
        string Member_username = line.substr(0, info);              // Member_username = 뜨어쓰기 이전 부분
        string Member_password = line.substr(info + 1);             // Member_password = 띄어쓰기 이후 부분
        if (Member_username == username && Member_password == password) {  // 매개변수로 입력받은 username(id), password(pw)를 메모장에서 같은 것이 있는지 확인 
            Rf.close();
            return true;
        }
    }
    Rf.close();
    return false;
}

// 입력받은 아이디와 비번을 메모장에서 삭제하는 함수(회원탈퇴 시 사용)
void DeleteUser(const string& filename, const string& username, const string& password) {
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
}

class Ui {                                // 화면그리는 Ui 추상 클래스
protected:
    int left = 20;
public:
    Ui() {                                // 처음 화면을 그리는 Ui 부분을 생성자에 대입한 부분
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
    virtual void drawMenu() = 0;         // 이후 밑의 메뉴를 그리는 함수를 가상함수로 생성
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

class Member : public Ui, public Gold, public Silver, public Bronze {                   // 로그인할때 회원의 아이디, 비번, 회원등급 그리고 이외의 함수들의 클래스
    friend void input(Member& member);       // input()함수를 사용해 아이디와 비번을 입력받을 때 class Member에 접근하기 위해
protected:
    static string username, grade;
    string password;                                // 회원의 아이디, 비번, 등급
    int grade_cal = 0;                           // 회원 등급을 계산할 변수 생성

    Gold* gd;
    Silver* sr;
    Bronze* be;
public:
    Member() : Ui() {                        // 부모 클래스인 Ui의 생성자가 먼저 실행됨
        drawMenu();                          // 밑에서 재정의한 drawMenu()를 생성자에서 사용
    }
    void drawMenu() {                        // drawMenu() 재정의
        cout << setw(27) << "로그인" << setw(10) << "회원가입" << setw(10) << "회원탈퇴" << setw(7) << "종료" << endl;
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

    bool login() {                           // login() 로그인 함수: 아이디, 비번을 CheckMember()함수를 사용해 로그인의 유무 return
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

    void CreateAccount() {                                  // 회원가입 함수: 아이디, 비번을 메모장에 추가
        ofstream outputFile("login.txt", ios::app);         // 파일 끝에 추가 모드로 열기
        outputFile << username << ' ' << password << "\n";  // username과 password를 메모장에 작성
        outputFile.close();
    }
    void QuitAccount() {                                         // 회원탈퇴 함수: 아이디, 비번을 메모장에서 삭제
        DeleteUser("login.txt", this->username, this->password); // DeleteUser 함수를 사용해 아이디, 비번을 삭제
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
    cout << "id 입력: ";
    cin >> member.username;
    cout << "비밀번호 입력: ";
    cin >> member.password;
}

class Song {                                                               // 인기도:popularity와 노래이름: songName이 들어가는 클래스 Song
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
        cout << setw(27) << "내 플레이리스트 보기(보기 입력)" << setw(10) << "플레이리스트에 노래 추가삭제(노래추가, 노래삭제 입력)" << setw(10) << "노래보기" << setw(7) << "종료" << endl;
        cout << setw(31) << "(보기 입력)" << setw(13) << "(노래추가, 노래삭제 입력)" << endl;
        cout << endl;
    }

    void OutputMusic() {                                                  // songList를 반복하며 출력하면서 인기도가 높은 순서대로 노래를 순서대로 출력하는 함수
        sort(song_ballad.ballad.begin(), song_ballad.ballad.end(), compare);
        sort(song_hiphop.hiphop.begin(), song_hiphop.hiphop.end(), compare);
        sort(song_kpop.kpop.begin(), song_kpop.kpop.end(), compare);
        cout << "노래 리스트(인기도 순):" << endl;
        cout << "발라드:" << endl;
        for (const Song& song : song_ballad.ballad) {
            cout << song.songName << ", " << endl;
        }
        cout << "\n힙합:" << endl;
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
        cout << "나의 플레이리스트: " << endl;
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
    void operator+(const string& songName) {                             // 연산자 중복+를 이용하여 생성한 플레이리스트에 입력받은 노래를 추가하는 함수
        ofstream playlistFile(Member::getUsername() + "_playlist.txt", ios::app);                 // 노래 추가 시 회원의 등급에 따른 추가 가능 횟수 부분을 함수에 넣어야함
        
        ifstream readfile(Member::getUsername() + "_playlist.txt");
        int songCount = 0;
        string line;
        while (getline(readfile, line)) {
            songCount++;
        }
        readfile.close();

        if (Member::getGrade() == "골드" && songCount > 10) {
            cout << "등급에 따른 플레이리스트의 노래 추가 횟수를 넘었습니다" << endl;
            cout << "등급을 올려주세요" << endl;
            return;
        }

        else if (Member::getGrade() == "실버" && songCount > 8) {
            cout << "등급에 따른 플레이리스트의 노래 추가 횟수를 넘었습니다" << endl;
            cout << "등급을 올려주세요" << endl;
            return;
        }

        else if (Member::getGrade() == "브론즈" && songCount > 5) {
            cout << "등급에 따른 플레이리스트의 노래 추가 횟수를 넘었습니다" << endl;
            cout << "등급을 올려주세요" << endl;
            return;
        }

        if (playlistFile.is_open()) {
            playlistFile << songName << endl;
            playlistFile.close();
            cout << "플레이리스트에 노래가 추가되었습니다." << endl;
        }
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
        remove((Member::getUsername() + "_playlist.txt").c_str());                                                // 기존 매개변수에 있는 메모장 삭제
        rename("temp.txt", (Member::getUsername() + "_playlist.txt").c_str());                                    // 원래 이름으로 메모장 이름을 바꿈
    }
};

/*if (menu == "노래보기") {
    player->RandomPopularity();

    do {
        player->getMusic();
        player->OutputMusic();
        cout << setw(38) << "장르별 보기(발라드, 힙합, K - pop):";

        player->genre_sort();

    } while (menu == "뒤로");
}
if (menu == "플레이리스") {
    player->MakePlaylist();
    while (menu == "종료") {
        if (menu == "추가") {
            if (menu != song->songName)
                cout << "없는 노래입니다" << endl;
            else if (menu == playlist->)
                cout << "이미 플레이리스트에 존재하는 노래입니다." << endl;
            else
                playlist + song->songName;
        }
        else if (menu == "삭제") {
            if (menu != playlist->song)
                playlist - song->songName;
        }
    }*/

int main() {
    string menu;                                         // 입력받을 Menu 변수 
    Member* member = nullptr;                            // 초기에 회원 객체가 없음 처리 (nullptr을 잘 활용해보자)

    while (true) {
        member = new Member();
        cout << setw(38) << "입력: ";
        cin >> menu;
        if (menu == "로그인") {                         // Menu가 로그인이면 input()함수를 사용해 아이디 비번을 입력받고 login()함수를 사용해 유무확인
            input(*member);
            if (member->login()) {
                cout << "로그인 성공" << endl;
                // 로그인 성공 후 플레이리스트 사용부분, 등급도 이후로 해야함

            }
            else {
                cout << "로그인 실패 다시 입력하세요" << endl;              // member->login()가 false라면 계속해서 input()를 불러 입력받도록 반복
                do {                                                        // while로 하려다 실패해서 do-while로 해결
                    input(*member);
                    if (!member->login()) {
                        cout << "없는 회원정보입니다" << endl;
                        cout << "다시 입력하세요" << endl;
                        cout << endl;
                    }
                } while (!member->login());
                cout << "로그인 성공" << endl;
                delete member;
                continue;
            }
        }
        else if (menu == "회원가입") {                                  // menu가 회원가입이면 input()함수를 사용해 아이디 비번 입력받고 CreateAccount()실행
            do {
                input(*member);
                if (member->login()) {
                    cout << "이미 존재하는 회원정보입니다" << endl;
                    cout << "다시 입력하세요." << endl;
                    cout << endl;
                }
            } while (member->login());
            member->CreateAccount();
            cout << "회원가입 성공" << endl;
            delete member;
            continue;
        }
        else if (menu == "회원탈퇴") {                                 // menu가 회원탈퇴면 input()함수를 사용해 아이디 비번 입력받고 QuitAccount()실행
            cout << "회원탈퇴 할 아이디와 비번을 입력해주세요" << endl;
            do {
                input(*member);
                if (!member->login()) {
                    cout << "없는 회원정보입니다" << endl;
                    cout << "다시 입력하세요" << endl;
                    cout << endl;
                }
            } while (!member->login());
            member->QuitAccount();
            cout << "회원탈퇴 성공!" << endl;
            delete member;
            continue;
        }
        else if (menu == "종료") {
            return 0;
        }
        else {
            cout << "올바른 메뉴를 선택하세요" << endl;
            continue;
        }
    }
    return 0;
}