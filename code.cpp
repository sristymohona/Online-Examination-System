#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

// --------------------- Classes ---------------------
class User {
protected:
    string name;                                                                                                                
    string role;
public:
    User(string n, string r) : name(n), role(r) {}
    virtual void dashboard() = 0;
    string getName() { return name; }
    string getRole() { return role; }
};

// Question Class
class Question {
public:
    string text;
    vector<string> options;
    char answer;
};

// Exam Class
class Exam {
public:
    int examID;
    string examName;
    int timeLimit;   
    vector<Question> questions;

    void addQuestion(const Question &q) {
        questions.push_back(q);
    }
};

// Global Exams Vector
vector<Exam> allExams;

//-------------------Auth--------------------------

class Auth {
private:
    string username;
    string password;
    string role;
public:
    Auth(string u, string p, string r)
        : username(u), password(p), role(r) {}

    // -------- REGISTER --------
    void registerUser() {
        ofstream fout("users.txt");
        fout << username << " " << password << " " << role << endl;
    }

    // -------- LOGIN --------
    bool loginCheck() {
        ifstream fin("users.txt");

        string fu, fp, fr;

        while(fin >> fu >> fp >> fr) {
            if(username == fu && password == fp && role == fr)
                return true;
        }
        return false;
    }
};

// --------------------- File Handling ---------------------

void saveExamsToFile() {
    ofstream fout("exams.txt");

    if (!fout) {
        cout << "Error opening file for writing!\n";
        return;
    }

    fout << allExams.size() << "\n";

    for (auto &e : allExams) {

        fout << e.examID << "\n";
        fout << e.examName << "\n";
        fout << e.questions.size() << "\n";

        for (auto &q : e.questions) {

            fout << q.text << "\n";

            for (auto &opt : q.options)
                fout << opt << "\n";

            fout << q.answer << "\n";
        }
    }

    fout.close();
}

void loadExamsFromFile() {
    ifstream fin("exams.txt");
    
    if (!fin.is_open()) {
        return;
    }

    allExams.clear();

    int examCount;
    
    if (!(fin >> examCount)) {
        fin.close();
        return;
    }
    fin.ignore();

    for (int i = 0; i < examCount; i++) {
        Exam e;
        if (!(fin >> e.examID)) break;
        fin.ignore();

        if (!getline(fin, e.examName)) break;

        int qCount;
        if (!(fin >> qCount)) break;
        fin.ignore();

        for (int j = 0; j < qCount; j++) {
            Question q;
            if (!getline(fin, q.text)) break;

            q.options.resize(4);
            for (int k = 0; k < 4; k++) {
                if (!getline(fin, q.options[k])) break;
            }

            if (!(fin >> q.answer)) break;
            fin.ignore();

            e.questions.push_back(q);
        }
        allExams.push_back(e);
    }

    fin.close();
}

// --------------------- Admin ---------------------
class Admin : public User {
public:
    Admin(string n) : User(n, "Admin") {}

    void dashboard() override {

        int choice;

        do {
            cout << "\n--- ADMIN DASHBOARD ---\n";
            cout << "1. View All Exams\n";
            cout << "2. Delete Exam\n";
            cout << "3. Edit Exam\n";
            cout << "4. Back\n";
            cout << "Enter choice: ";

            cin >> choice;
            cin.ignore();

            switch(choice) {

                // ---------------- VIEW ----------------
                case 1: {

                    if(allExams.empty()) {
                        cout << "No exams created yet.\n";
                    } 
                    else {
                        cout << "\n===== EXAM LIST =====\n\n";
                        
                        cout << left
                             << setw(10) << "Exam ID"
                             << setw(20) << "Exam Name"
                             << setw(15) << "Questions"
                             << endl;
                        
                        cout << "----------------------------------------\n";
                        
                        for(auto &e : allExams) {
                        
                            cout << left
                                 << setw(10) << e.examID
                                 << setw(20) << e.examName
                                 << setw(15) << e.questions.size()
                                 << endl;
                        }
                    }

                    break;
                }

                // ---------------- DELETE ----------------
                case 2: {

                    int id;
                    cout << "Enter Exam ID to delete: ";
                    cin >> id;
                    cin.ignore();

                    bool found = false;

                    for(int i = 0; i < allExams.size(); i++) {

                        if(allExams[i].examID == id) {

                            allExams.erase(allExams.begin() + i);
                            found = true;

                            cout << "Exam deleted successfully!\n";
                            break;
                        }
                    }

                    if(!found)
                        cout << "Exam not found!\n";

                    break;
                }

                // ---------------- EDIT ----------------
                case 3: {

                    int id;
                    cout << "Enter Exam ID to edit: ";
                    cin >> id;
                    cin.ignore();

                    bool found = false;

                    for(auto &e : allExams) {

                        if(e.examID == id) {

                            found = true;

                            cout << "Current Exam Name: " << e.examName << endl;

                            cout << "Enter new name: ";
                            getline(cin, e.examName);

                            cout << "Do you want to clear questions? (y/n): ";
                            char c;
                            cin >> c;
                            cin.ignore();

                            if(c == 'y' || c == 'Y') {
                                e.questions.clear();
                                cout << "Questions cleared!\n";
                            }

                            cout << "Exam updated successfully!\n";
                        }
                    }

                    if(!found)
                        cout << "Exam not found!\n";

                    break;
                }

                // ---------------- BACK ----------------
                case 4:
                    cout << "Returning to main menu...\n";
                    break;

                default:
                    cout << "Invalid choice!\n";
            }

        } while(choice != 4);
    }
};

// --------------------- Teacher ---------------------
class Teacher : public User {
public:
    Teacher(string n) : User(n, "Teacher") {}

    void dashboard() override {

        int choice;

        do {
            cout << "\n--- TEACHER DASHBOARD ---\n";
            cout << "1. Create New Exam\n";
            cout << "2. Add Questions\n";
            cout << "3. Back\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            switch(choice) {

                // ---------------- CREATE EXAM (UPDATED) ----------------
                case 1: {

                    string name;
                    int timeLimit;

                    cout << "Enter Exam Name: ";
                    getline(cin, name);

                    cout << "Enter Time Limit (in minutes): ";
                    cin >> timeLimit;
                    cin.ignore();

                    Exam e;

                    e.examID = allExams.size() + 1;
                    e.examName = name;

                    e.timeLimit = timeLimit;   

                    allExams.push_back(e);

                    cout << "Exam created successfully with time limit!\n";

                    break;
                }

                // ---------------- ADD QUESTIONS ----------------
                case 2: {

                    if(allExams.empty()) {
                        cout << "No exams available. Create exam first.\n";
                        break;
                    }

                    int id;

                    cout << "Enter Exam ID: ";
                    cin >> id;
                    cin.ignore();

                    bool found = false;

                    for(auto &e : allExams) {

                        if(e.examID == id) {

                            found = true;

                            int qCount;

                            cout << "How many questions to add: ";
                            cin >> qCount;
                            cin.ignore();

                            for(int i=0;i<qCount;i++) {

                                Question q;

                                cout << "Enter Question: ";
                                getline(cin, q.text);

                                q.options.resize(4);

                                for(int j=0;j<4;j++) {
                                    cout << "Option " << char('a'+j) << ": ";
                                    getline(cin, q.options[j]);
                                }

                                cout << "Correct answer (a/b/c/d): ";
                                cin >> q.answer;
                                cin.ignore();

                                e.addQuestion(q);
                            }

                            cout << "Questions added successfully!\n";
                        }
                    }

                    if(!found)
                        cout << "Exam ID not found.\n";

                    break;
                }

                // ---------------- BACK ----------------
                case 3:
                    cout << "Returning to main menu...\n";
                    break;

                default:
                    cout << "Invalid choice!\n";
            }

        } while(choice != 3);
    }
};

// ---------------- RESULT CLASS ----------------

class Result {

public:
    string studentName;
    string examName;
    int score;
};

// ---------------- GLOBAL LEADERBOARD VECTOR ----------------

vector<Result> leaderboard;

// ---------------- STUDENT CLASS ----------------
class Student : public User {

public:

    Student(string n) : User(n, "Student") {}

    void dashboard() override {

        int choice;

        do {

            cout << "\n--- STUDENT DASHBOARD ---\n";

            cout << "1. View Available Exams\n";
            cout << "2. Take Exam\n";
            cout << "3. View Leaderboard\n";
            cout << "4. Back\n";

            cout << "Enter choice: ";

            cin >> choice;
            cin.ignore();

            switch(choice) {

                // -------- VIEW EXAMS --------

                case 1: {

                    if(allExams.empty()) {

                        cout << "No exams available.\n";
                    }

                    else {

                         cout << "\n===== AVAILABLE EXAMS =====\n\n";

                         cout << left
                              << setw(10) << "Exam ID"
                              << setw(15) << "Exam Name"
                              << setw(15) << "Questions"
                              << setw(10) << "Time"
                              << endl;

                         cout << "--------------------------------------------------\n";

                         for(auto &e : allExams) {

                             cout << left
                                  << setw(10) << e.examID
                                  << setw(15) << e.examName
                                  << setw(15) << e.questions.size()
                                  << setw(10) << (to_string(e.timeLimit) + " min")
                                  << endl;
                         }
                     }

                    break;
                }

                // -------- TAKE EXAM --------

                case 2: {
                
                    int id;
                
                    cout << "Enter Exam ID: ";
                    cin >> id;
                    cin.ignore();
                
                    bool found = false;
                
                    for(auto &e : allExams) {
                
                        if(e.examID == id) {
                
                            found = true;
                
                            int score = 0;
                
                            cout << "\nStarting Exam: " << e.examName << endl;
                            cout << "Time Limit: " << e.timeLimit << " minutes\n";
                            cout << "Press Enter to start...";
                            cin.get();
                
                            for(auto &q : e.questions) {
                
                                cout << "\n" << q.text << endl;
                
                                for(int i = 0; i < q.options.size(); i++) {
                
                                    cout << char('a' + i)
                                         << ") "
                                         << q.options[i]
                                         << endl;
                                }
                
                                char ans;
                                cout << "Your answer: ";
                                cin >> ans;
                
                                if(ans == q.answer)
                                    score++;
                            }
                
                            cout << "\nScore: "
                                 << score
                                 << "/"
                                 << e.questions.size()
                                 << endl;
                
                            double passMark = e.questions.size() * 0.4;
                
                            if(score >= passMark)
                                cout << "Congratulations! You Passed\n";
                            else
                                cout << "You Failed\n";
                
                            Result r;
                            r.studentName = name;
                            r.examName = e.examName;
                            r.score = score;
                
                            leaderboard.push_back(r);
                        }
                    }
                
                    if(!found)
                        cout << "Exam not found.\n";
                
                    break;
                }

                // -------- LEADERBOARD --------

                case 3: {

                    if(leaderboard.empty()) {

                        cout << "No leaderboard data.\n";
                        break;
                    }

                    sort(leaderboard.begin(),
                         leaderboard.end(),

                        [](Result a, Result b) {

                            return a.score > b.score;
                        }
                    );

                    cout << "\n===== LEADERBOARD =====\n\n";

                    cout << left
                         << setw(8)  << "Rank"
                         << setw(12) << "Name"
                         << setw(12) << "Exam"
                         << setw(8)  << "Score"
                         << endl;

                    cout << "----------------------------------------\n";

                    for(int i = 0;
                        i < leaderboard.size();
                        i++) {

                        cout << left
                             << setw(8)  << i + 1
                             << setw(12) << leaderboard[i].studentName
                             << setw(12) << leaderboard[i].examName
                             << setw(8)  << leaderboard[i].score
                             << endl;
                    }

                    break;
                }

                // -------- BACK --------

                case 4:

                    cout << "Returning...\n";
                    break;

                default:

                    cout << "Invalid choice!\n";
            }

        } while(choice != 4);
    }
};
         
// --------------------- Main ---------------------

int main() {

    loadExamsFromFile(); 

    int choice;

    do {

        cout << "\n===== SMART ONLINE EXAM SYSTEM =====\n";
        cout << "1. Admin Login\n";
        cout << "2. Teacher Login\n";
        cout << "3. Student Login\n";
        cout << "4. Register\n";
        cout << "5. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        string username, password, role;

        switch(choice) {

            // ---------------- ADMIN LOGIN ----------------
            case 1: {

                cout << "Username: ";
                getline(cin, username);

                cout << "Password: ";
                getline(cin, password);

                role = "Admin";

                Auth auth(username, password, role);

                if(auth.loginCheck()) {

                    Admin admin(username);
                    admin.dashboard();

                } else {
                    cout << "Login Failed!\n";
                }

                break;
            }

            // ---------------- TEACHER LOGIN ----------------
            case 2: {

                cout << "Username: ";
                getline(cin, username);

                cout << "Password: ";
                getline(cin, password);

                role = "Teacher";

                Auth auth(username, password, role);

                if(auth.loginCheck()) {

                    Teacher teacher(username);
                    teacher.dashboard();

                } else {
                    cout << "Login Failed!\n";
                }

                break;
            }

            // ---------------- STUDENT LOGIN ----------------
            case 3: {

                cout << "Username: ";
                getline(cin, username);

                cout << "Password: ";
                getline(cin, password);

                role = "Student";

                Auth auth(username, password, role);

                if(auth.loginCheck()) {

                    Student student(username);
                    student.dashboard();

                } else {
                    cout << "Login Failed!\n";
                }

                break;
            }

            // ---------------- REGISTER ----------------
            case 4: {

                cout << "Enter Username: ";
                getline(cin, username);

                cout << "Enter Password: ";
                getline(cin, password);

                cout << "Enter Role (Admin/Teacher/Student): ";
                getline(cin, role);

                Auth auth(username, password, role);
                auth.registerUser();

                cout << "Registration Successful!\n";

                break;
            }

            // ---------------- EXIT ----------------
            case 5:
                saveExamsToFile();
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 5);

    return 0;
}
