#include <iostream>
#include <string>
#include <unordered_map>

#ifdef _WIN32
#include <windows.h> // For Windows
#else
#include <cstdlib> // For Unix/Linux
#endif

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Unix/Linux
#endif
}

class User {
protected:
    string username;
    string password;

public:
    User(const string& username, const string& password) : username(username), password(password) {}

    virtual void displayType() const = 0;  // Pure virtual function

    const string& getUsername() const {
        return username;
    }

    bool isPasswordCorrect(const string& inputPassword) const {
        return password == inputPassword;
    }
};

class Tutor : public User {
private:
    string phoneNo;
    string email;
    string fluentIn;
    string degree;
    string bio;
    string whatsappNo;

public:
    Tutor(const string& username, const string& password, const string& phoneNo, const string& email, const string& fluentIn, const string& degree, const string& bio, const string& whatsappNo)
        : User(username, password), phoneNo(phoneNo), email(email), fluentIn(fluentIn), degree(degree), bio(bio), whatsappNo(whatsappNo) {}

    void displayType() const override {
        cout << "# User Type: Tutor \n";
        cout << "# Phone No: " << phoneNo << endl;
        cout << "# Email: " << email << endl;
        cout << "# Fluent In: " << fluentIn << endl;
        cout << "# Degree: " << degree << endl;
        cout << "# Bio: " << bio << endl;
        cout << "# WhatsApp No: " << whatsappNo << endl;
    }
};

class Student : public User {
private:
    string phoneNo;
    string email;
    string fluentIn;
    string learningGoals;
    string bio;
    string whatsappNo;

public:
    Student(const string& username, const string& password, const string& phoneNo, const string& email, const string& fluentIn, const string& learningGoals, const string& bio, const string& whatsappNo)
        : User(username, password), phoneNo(phoneNo), email(email), fluentIn(fluentIn), learningGoals(learningGoals), bio(bio), whatsappNo(whatsappNo) {}

    void displayType() const override {
        cout << "# User Type: Student \n";
        cout << "# Phone No: " << phoneNo << endl;
        cout << "# Email: " << email << endl;
        cout << "# Fluent In: " << fluentIn << endl;
        cout << "# Learning Goals: " << learningGoals << endl;
        cout << "# Bio: " << bio << endl;
        cout << "# WhatsApp No: " << whatsappNo << endl;
    }
};

class UserManager {
private:
    unordered_map<string, User*> users;

public:
    ~UserManager() {
        for (const auto& pair : users) {
            delete pair.second; // Free memory for each user
        }
    }

    void displayMenu() const {
        clearScreen();
        cout << "\n";
        cout << "**************************************************\n";
        cout << "****  Welcome to the Landing Page of LingQ    ****\n";
        cout << "****  Get Started...                          ****\n";
        cout << "****  1. Register as Tutor                    ****\n";
        cout << "****  2. Register as Student                  ****\n";
        cout << "****  3. Login                                ****\n";
        cout << "****  4. Exit                                 ****\n";
        cout << "**************************************************\n";
        cout << "\n";
    }

    void registerUser() {
        string username, password, phoneNo, email, fluentIn, degree, bio, whatsappNo, learningGoals;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter phone number: ";
        cin >> phoneNo;
        cout << "Enter email: ";
        cin >> email;
        cout << "Enter languages fluent in: ";
        cin.ignore();
        getline(cin, fluentIn);
        cout << "Enter degree: ";
        getline(cin, degree);
        cout << "Enter bio: ";
        getline(cin, bio);
        cout << "Enter WhatsApp number: ";
        cin >> whatsappNo;

        string userType;
        cout << "Choose user type (Tutor/Student): ";
        cin >> userType;

        if (userType == "Tutor") {
            User* newUser = new Tutor(username, password, phoneNo, email, fluentIn, degree, bio, whatsappNo);
            users[username] = newUser;
            loginUser(username, password);
            cout << "# Registration successful!\n";
        } else if (userType == "Student") {
            User* newUser = new Student(username, password, phoneNo, email, fluentIn, learningGoals, bio, whatsappNo);
            users[username] = newUser;
            loginUser(username, password);
            cout << "# Registration successful!\n";
        } else {
            cout << "Error: Invalid user type.\n";
        }
    }

    void loginUser(const string& username, const string& password) {
        auto it = users.find(username);
        if (it != users.end()) {
            if (it->second->isPasswordCorrect(password)) {
                cout<<"\n";
                cout << "# Login successful!\n";
                it->second->displayType();
                cout << "# Welcome, " << username << "!\n";
                cout << "////////////////////////////" << endl;
            } else {
                cout << "Error: Incorrect password.\n";
            }
        } else {
            cout << "Error: User not found.\n";
        }
    }
};

int main() {
    UserManager userManager;
    int choice = 0;

    while (choice != 4) {
        userManager.displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            userManager.registerUser();
            break;
        case 2:
            userManager.registerUser();
            break;
        case 3: {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            userManager.loginUser(username, password);
            break;
        }
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}
