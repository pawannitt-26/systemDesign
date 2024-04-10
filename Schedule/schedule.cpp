#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ClassSchedule {
private:
    string className;
    string dayOfWeek;
    string startTime;
    string endTime;

public:
    ClassSchedule(string className, string dayOfWeek, string startTime, string endTime)
        : className(className), dayOfWeek(dayOfWeek), startTime(startTime), endTime(endTime) {}

    void displaySchedule() const {
        cout << "Class: " << className << endl;
        cout << "Day: " << dayOfWeek << endl;
        cout << "Time: " << startTime << " - " << endTime << endl;
    }
};

class Teacher {
private:
    string username;
    vector<ClassSchedule> schedules;

public:
    Teacher(string username) : username(username) {}

    void addSchedule(const ClassSchedule& schedule) {
        schedules.push_back(schedule);
    }

    void displaySchedule() const {
        cout << "Your Schedule:" << endl;
        for (const auto& schedule : schedules) {
            schedule.displaySchedule();
            cout << endl;
        }
    }
};

int main() {
    Teacher teacher("JohnDoe");

    // Adding sample schedules
    ClassSchedule schedule1("Mathematics", "Monday", "09:00 AM", "10:30 AM");
    ClassSchedule schedule2("Physics", "Wednesday", "11:00 AM", "12:30 PM");

    teacher.addSchedule(schedule1);
    teacher.addSchedule(schedule2);

    int choice;
    do {
        cout << "1. View Schedule\n"
                "2. Exit\n"
                "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                teacher.displaySchedule();
                break;
            case 2:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 2);

    return 0;
}
