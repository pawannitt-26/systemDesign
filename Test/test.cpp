#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <algorithm>
#include <random>

using namespace std ;

struct Question {
    string questionText;
    vector<string> options;
    int correctOptionIndex;
};

class Quiz {
private:
    vector<Question> questions;
    int score;

public:
    Quiz() : score(0) {}

    void addQuestion(const Question& question) {
        questions.push_back(question);
    }

    void generateRandomQuiz(int numQuestions) {
        shuffle(questions.begin(), questions.end(), default_random_engine(random_device()()));
        questions.resize(numQuestions); // Limit to numQuestions
    }

    void displayQuiz() const {
        for (const auto& question : questions) {
            cout << question.questionText << "\n";
            for (size_t i = 0; i < question.options.size(); ++i) {
                cout << i + 1 << ". " << question.options[i] << "\n";
            }
        }
    }

    void gradeQuiz(const vector<int>& userAnswers) {
        if (userAnswers.size() != questions.size()) {
            cerr << "Error: Number of user answers does not match number of questions.\n";
            return;
        }

        score = 0;
        for (size_t i = 0; i < questions.size(); ++i) {
            if (userAnswers[i] == questions[i].correctOptionIndex + 1) {
                ++score;
            }
        }
    }

    int getScore() const {
        return score;
    }
};

int main() {
    sqlite3* db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc) {
        cerr << "Error opening SQLite database: " << sqlite3_errmsg(db) << "\n";
        return 1;
    }

    // Create a users table
    rc = sqlite3_exec(db,
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password TEXT NOT NULL"
        ");",
        0, 0, 0);

    if (rc != SQLITE_OK) {
        cerr << "Error creating users table: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return 1;
    }

    // Mock user registration (in a real application, passwords should be hashed)
    rc = sqlite3_exec(db,
        "INSERT INTO users (username, password) VALUES ('user1', 'password123');",
        0, 0, 0);

    if (rc != SQLITE_OK) {
        cerr << "Error inserting user data: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return 1;
    }

    // Mock quiz questions
    Question q1 {"What is the capital of France?", {"Paris", "London", "Berlin", "Madrid"}, 0};
    Question q2 {"What is 2 + 2?", {"3", "4", "5", "6"}, 1};
    Question q3 {"Is oswald gay ?" , {"Yes","No" , "Idk" , "NOTA"} , 0} ;

    Quiz quiz;
    quiz.addQuestion(q1);
    quiz.addQuestion(q2);
    quiz.addQuestion(q3);
    quiz.generateRandomQuiz(2);

    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    // Validate user credentials
    rc = sqlite3_exec(db,
        ("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "';").c_str(),
        0, 0, 0);

    if (rc != SQLITE_OK) {
        cerr << "Error querying user data: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return 1;
    }

    int numQuestions = 2;
    vector<int> userAnswers(numQuestions);
    quiz.displayQuiz();

    cout << "Enter your answers (1-" << numQuestions << "): ";
    for (int i = 0; i < numQuestions; ++i) {
        cin >> userAnswers[i];
    }

    quiz.gradeQuiz(userAnswers);
    cout << "Your score: " << quiz.getScore() << "/" << numQuestions << "\n";

    sqlite3_close(db);
    return 0;
}
