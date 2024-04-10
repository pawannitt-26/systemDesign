#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class Question {
private:
    string questionText;
    vector<string> options;
    char correctOption;

public:
    // Default constructor added
    Question() {}

    Question(const string& text, const vector<string>& opts, char correct)
        : questionText(text), options(opts), correctOption(correct) {}

    string getQuestionText() const { return questionText; }

    vector<string> getOptions() const { return options; }

    char getCorrectOption() const { return correctOption; }
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
        for (size_t i = 0; i < questions.size(); ++i) {
            cout << i + 1 << ". " << questions[i].getQuestionText() << "\n";
            vector<string> options = questions[i].getOptions();
            for (size_t j = 0; j < options.size(); ++j) {
                cout << "   " << static_cast<char>('A' + j) << ") " << options[j] << "\n";
            }
        }
    }

    void gradeQuiz(const vector<char>& userAnswers) {
        if (userAnswers.size() != questions.size()) {
            cerr << "Error: Number of user answers does not match number of questions.\n";
            return;
        }

        score = 0;
        for (size_t i = 0; i < questions.size(); ++i) {
            if (toupper(userAnswers[i]) == questions[i].getCorrectOption()) {
                ++score;
            }
        }
    }

    int getScore() const {
        return score;
    }

    vector<Question> getQuestions() const {
        return questions;
    }
};

int main() {
    char userType;
    cout << "Are you a (T)eacher or a (S)tudent? Enter T or S: ";
    cin >> userType;

    if (toupper(userType) == 'T') {
        int numQuestions;
        cout << "Enter the number of questions for the quiz: ";
        cin >> numQuestions;
        cin.ignore(); // Clear the newline from the input buffer

        Quiz teacherQuiz;
        for (int i = 0; i < numQuestions; ++i) {
            string questionText;
            vector<string> options;
            char correctOption;

            cout << "Enter question " << i + 1 << " text: ";
            getline(cin, questionText);

            for (char optionLetter = 'A'; optionLetter < 'A' + 4; ++optionLetter) {
                string optionText;
                cout << "Enter option " << optionLetter << ": ";
                getline(cin, optionText);
                options.push_back(optionText);
            }

            cout << "Enter correct option (A/B/C/D): ";
            cin >> correctOption;
            cin.ignore(); // Clear the newline from the input buffer

            teacherQuiz.addQuestion(Question(questionText, options, toupper(correctOption)));
        }

        teacherQuiz.generateRandomQuiz(numQuestions);
        cout << "Quiz created successfully!\n";
    } else if (toupper(userType) == 'S') {
        Quiz studentQuiz;
        // Language-related quiz questions for the student
        Question q1 {"What is the official language of Brazil?", {"Portuguese", "Spanish", "English", "French"}, 'A'};
        Question q2 {"Who is known as the father of modern computer science?", {"Alan Turing", "Charles Babbage", "Ada Lovelace", "John von Neumann"}, 'A'};
        Question q3 {"Which programming language is used for web development?", {"Python", "Java", "HTML/CSS", "C++"}, 'C'};
        Question q4 {"What is the capital of Spain?", {"Madrid", "Barcelona", "Seville", "Valencia"}, 'A'};
        Question q5 {"Who wrote 'The Great Gatsby'?", {"F. Scott Fitzgerald", "Ernest Hemingway", "Mark Twain", "William Faulkner"}, 'A'};
        Question q6 {"Which country is known for producing Bollywood films?", {"India", "China", "Japan", "USA"}, 'A'};
        Question q7 {"What is the most widely spoken language in the world?", {"English", "Mandarin Chinese", "Spanish", "Hindi"}, 'B'};
        Question q8 {"Who wrote the play 'Hamlet'?", {"William Shakespeare", "George Bernard Shaw", "Anton Chekhov", "Tennessee Williams"}, 'A'};
        Question q9 {"Which language uses curly braces to define code blocks?", {"Python", "Java", "C++", "Ruby"}, 'C'};
        Question q10 {"What is the national language of Japan?", {"Japanese", "Mandarin", "Korean", "Cantonese"}, 'A'};

        studentQuiz.addQuestion(q1);
        studentQuiz.addQuestion(q2);
        studentQuiz.addQuestion(q3);
        studentQuiz.addQuestion(q4);
        studentQuiz.addQuestion(q5);
        studentQuiz.addQuestion(q6);
        studentQuiz.addQuestion(q7);
        studentQuiz.addQuestion(q8);
        studentQuiz.addQuestion(q9);
        studentQuiz.addQuestion(q10);

        studentQuiz.generateRandomQuiz(10);

        int numQuestions = 5;
        vector<char> userAnswers(numQuestions);
        studentQuiz.displayQuiz();

        cout << "Enter your answers (A/B/C/D) for each question:\n";
        for (int i = 0; i < numQuestions; ++i) {
            cout << "Question " << i + 1 << ": ";
            cin >> userAnswers[i];
            userAnswers[i] = toupper(userAnswers[i]);
        }

        studentQuiz.gradeQuiz(userAnswers);
        cout << "Your score: " << studentQuiz.getScore() << "/" << numQuestions << "\n";
    } else {
        cerr << "Invalid input. Please enter T or S.\n";
        return 1;
    }

    return 0;
}
