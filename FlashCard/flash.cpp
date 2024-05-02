#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Flashcard {
private:
    string question;
    string answer;

public:
    Flashcard(string question, string answer)
        : question(question), answer(answer) {}

    void displayFlashcard() const {
        cout << "Question: " << question << endl;
        cout << "Answer: " << answer << endl;
    }
};

class Lecture {
private:
    string lectureName;
    vector<Flashcard> flashcards;

public:
    Lecture(string lectureName) : lectureName(lectureName) {}

    const string& getLectureName() const {
        return lectureName;
    }

    void addFlashcard(const Flashcard& flashcard) {
        flashcards.push_back(flashcard);
    }

    void displayFlashcards() const {
        cout << "Flashcards for " << lectureName << ":" << endl;
        for (const auto& flashcard : flashcards) {
            flashcard.displayFlashcard();
            cout << endl;
        }
    }
};

class Student {
private:
    string username;
    vector<Lecture> lecturesAttended;

public:
    Student(string username) : username(username) {}

    void attendLecture(const Lecture& lecture) {
        lecturesAttended.push_back(lecture);
    }

    void createFlashcard(const string& title, const string& description) {
        Flashcard flashcard(title, description);
        lecturesAttended.back().addFlashcard(flashcard);
        cout << "Flashcard created successfully!" << endl;
    }

    void displayLectures() const {
        cout << "Subjects Available:" << endl;
        for (size_t i = 0; i < lecturesAttended.size(); ++i) {
            cout << i + 1 << ". " << lecturesAttended[i].getLectureName() << endl;
        }
    }

    void displayFlashcards() const {
        cout << "Your Flashcards:" << endl;
        for (const auto& lecture : lecturesAttended) {
            lecture.displayFlashcards();
            cout << endl;
        }
    }

    const vector<Lecture>& getLecturesAttended() const {
        return lecturesAttended;
    }
};

class FlashcardManager {
private:
    vector<Student> students;

public:
    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void showFlashcards(const Student& student) {
        student.displayFlashcards();
    }
};

int main() {
    FlashcardManager flashcardManager;
    Student student("JaneDoe");
    Lecture lecture1("Mathematics Lecture");
    Lecture lecture2("Science Lecture");

    student.attendLecture(lecture1);
    student.attendLecture(lecture2);

    flashcardManager.addStudent(student);

    int choice;
    do {
        cout << "1. Create Flashcard\n"
                "2. View Flashcards\n"
                "3. Exit\n"
                "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int lectureChoice;
                cout << "Select a Subject to Create Flashcard:" << endl;
                student.displayLectures();
                cin >> lectureChoice;
                if (lectureChoice >= 1 && lectureChoice <= student.getLecturesAttended().size()) {
                    string title, description;
                    cout << "Enter Flashcard Title: ";
                    cin.ignore();
                    getline(cin, title);
                    cout << "Enter Flashcard Description: ";
                    getline(cin, description);
                    student.createFlashcard(title, description);
                } else {
                    cout << "Invalid subject choice!" << endl;
                }
                break;
            }
            case 2:
                flashcardManager.showFlashcards(student);
                break;
            case 3:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 3);

    return 0;
}
