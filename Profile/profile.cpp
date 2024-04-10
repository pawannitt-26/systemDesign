#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream> // for stringstream
#include <cstdlib> // for atoi

using namespace std;

class User {
protected:
    string username;
    string email;
    string firstName;
    string lastName;

public:
    User(const string& username, const string& email, const string& firstName, const string& lastName)
        : username(username), email(email), firstName(firstName), lastName(lastName) {}

    virtual void displayProfile() const = 0;
};

class Teacher : public User {
private:
    string subject;
    int experienceYears;

public:
    Teacher(const string& username, const string& email, const string& firstName, const string& lastName, const string& subject, int experienceYears)
        : User(username, email, firstName, lastName), subject(subject), experienceYears(experienceYears) {}

    void displayProfile() const override {
        cout << "Teacher Profile" << endl;
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Username: " << username << endl;
        cout << "Email: " << email << endl;
        cout << "Subject: " << subject << endl;
        cout << "Experience: " << experienceYears << " years" << endl;
    }
};

class Student : public User {
private:
    int gradeLevel;
    vector<string> enrolledCourses;

public:
    Student(const string& username, const string& email, const string& firstName, const string& lastName, int gradeLevel)
        : User(username, email, firstName, lastName), gradeLevel(gradeLevel) {
        // Default courses for the student
        enrolledCourses = {"Math", "Science", "English"};
    }

    void displayProfile() const override {
        cout << "Student Profile" << endl;
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Username: " << username << endl;
        cout << "Email: " << email << endl;
        cout << "Grade Level: " << gradeLevel << endl;
        cout << "Enrolled Courses:" << endl;
        for (const auto& course : enrolledCourses) {
            cout << "- " << course << endl;
        }
    }
};

class Webpage {
private:
    vector<unique_ptr<User>> users;

public:
    void addUser(unique_ptr<User> user) {
        users.push_back(std::move(user));
    }

    void displayAllProfiles() const {
        for (const auto& user : users) {
            user->displayProfile();
            cout << endl;
        }
    }
};

int main() {
    Webpage webpage;
    int choice;

    do {
        cout << "Menu:" << endl;
        cout << "1. Add Teacher" << endl;
        cout << "2. Add Student" << endl;
        cout << "3. Display All Profiles" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string username, email, firstName, lastName, subject, experienceStr;
                int experienceYears;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter email: ";
                cin >> email;
                cout << "Enter first name: ";
                cin >> firstName;
                cout << "Enter last name: ";
                cin >> lastName;
                cout << "Enter subject: ";
                cin >> subject;
                cout << "Enter experience years: ";
                cin >> experienceStr;

                // Convert experienceStr to integer
                stringstream ss(experienceStr);
                if (!(ss >> experienceYears)) {
                    cerr << "Error: Experience years must be a number." << endl;
                    break;
                }

                webpage.addUser(make_unique<Teacher>(username, email, firstName, lastName, subject, experienceYears));
                break;
            }
            case 2: {
                string username, email, firstName, lastName, gradeLevelStr;
                int gradeLevel;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter email: ";
                cin >> email;
                cout << "Enter first name: ";
                cin >> firstName;
                cout << "Enter last name: ";
                cin >> lastName;
                cout << "Enter grade level: ";
                cin >> gradeLevelStr;

                // Convert gradeLevelStr to integer
                stringstream ss(gradeLevelStr);
                if (!(ss >> gradeLevel)) {
                    cerr << "Error: Grade level must be a number." << endl;
                    break;
                }

                webpage.addUser(make_unique<Student>(username, email, firstName, lastName, gradeLevel));
                break;
            }
            case 3:
                webpage.displayAllProfiles();
                break;
            case 4:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
