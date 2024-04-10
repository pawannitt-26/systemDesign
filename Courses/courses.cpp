#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Course
{
private:
    string courseName;
    string courseCode;
    float price;
    string timeSlot;
    int duration;

public:
    Course(string courseName, string courseCode, float price, string timeSlot, int duration)
        : courseName(courseName), courseCode(courseCode), price(price), timeSlot(timeSlot), duration(duration) {}

    const string &getCourseName() const
    {
        return courseName;
    }

    const string &getCourseCode() const
    {
        return courseCode;
    }

    float getPrice() const
    {
        return price;
    }

    void setPrice(float newPrice)
    {
        price = newPrice;
    }

    const string &getTimeSlot() const
    {
        return timeSlot;
    }

    int getDuration() const
    {
        return duration;
    }
};

class User
{
protected:
    string username;
    string email;
    string firstName;
    string lastName;
    int gradeLevel;

public:
    User(string username, string email, string firstName, string lastName, int gradeLevel)
        : username(username), email(email), firstName(firstName), lastName(lastName), gradeLevel(gradeLevel) {}

    const string &getUsername() const
    {
        return username;
    }

    const string &getFirstName() const
    {
        return firstName;
    }

    const string &getLastName() const
    {
        return lastName;
    }

    int getGradeLevel() const
    {
        return gradeLevel;
    }

    virtual void displayProfile() const = 0;
};

class Teacher : public User
{
private:
    vector<Course> allCourses;

public:
    Teacher(string username, string email, string firstName, string lastName)
        : User(username, email, firstName, lastName, 0) {}

    void createCourse(const string &courseName, const string &courseCode, float price, const string &timeSlot, int duration)
    {
        allCourses.emplace_back(courseName, courseCode, price, timeSlot, duration);
        cout << "Course '" << courseName << "' created successfully!" << endl;
    }

    void displayProfile() const override
    {
        cout << "Teacher Profile" << endl;
        cout << "Name: " << getFirstName() << " " << getLastName() << endl;
        cout << "Username: " << getUsername() << endl;
        cout << "Email: " << email << endl;
        cout << "Courses Created:" << endl;
        for (const auto &course : allCourses)
        {
            cout << "- " << course.getCourseName() << " (" << course.getPrice() << ")" << endl;
        }
    }
};

class Student : public User
{
private:
    vector<Course> coursesTaken;
    float creditBalance; // New attribute to store credits

public:
    Student(string username, string email, string firstName, string lastName, int gradeLevel)
        : User(username, email, firstName, lastName, gradeLevel), creditBalance(0) {}

    float getCreditBalance() const
    {
        return creditBalance;
    }

    void addCredits(float credits)
    {
        creditBalance += credits;
        cout << "Credits added successfully! Current balance: " << creditBalance << endl;
    }

    void buyCourse(const Course &course)
    {
        if (creditBalance >= course.getPrice()) {
            creditBalance -= course.getPrice();
            coursesTaken.push_back(course);
            cout << "Course '" << course.getCourseName() << "' purchased successfully!" << endl;
        } else {
            cout << "Insufficient credits to buy this course!" << endl;
        }
    }

    void browseCourses(const vector<Course> &availableCourses) const
    {
        cout << "Available Courses:" << endl;
        for (size_t i = 0; i < availableCourses.size(); ++i)
        {
            cout << i + 1 << ". " << availableCourses[i].getCourseName()
                 << " (" << availableCourses[i].getPrice() << ")" << endl;
        }
    }

    void displayProfile() const override
    {
        cout << "Student Profile" << endl;
        cout << "Name: " << getFirstName() << " " << getLastName() << endl;
        cout << "Username: " << getUsername() << endl;
        cout << "Email: " << email << endl;
        cout << "Grade Level: " << getGradeLevel() << endl;
        cout << "Courses Taken:" << endl;
        for (const auto &course : coursesTaken)
        {
            cout << "- " << course.getCourseName() << endl;
        }
    }
};

class Webpage
{
private:
    vector<User *> users;
    vector<Course> allCourses;

public:
    void addUser(User *user)
    {
        users.push_back(user);
    }

    void addCourse(const Course &course)
    {
        allCourses.push_back(course);
    }

    void displayAllProfiles() const
    {
        for (const auto &user : users)
        {
            user->displayProfile();
            cout << endl;
        }
    }

    vector<Course> &getAllCourses() // Changed return type to vector<Course>
    {
        return allCourses;
    }
};

void clear_screen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main()
{
    Webpage webpage;
    Teacher teacher("JohnDoe", "johndoe@email.com", "John", "Doe");
    Student student("JaneDoe", "janedoe@email.com", "Jane", "Doe", 10);

    webpage.addUser(&teacher);
    webpage.addUser(&student);

    int choice;
    do
    {
        clear_screen();
        cout << "*******************************************" << endl;
        cout << "*** 1. Teacher: Create Course           ***" << endl;
        cout << "*** 2. Student: Buy Course              ***" << endl;
        cout << "*** 3. Student: Browse Courses          ***" << endl;
        cout << "*** 4. Student: Show Courses Taken      ***" << endl;
        cout << "*** 5. Student: Add Credits             ***" << endl;
        cout << "*** 6. Student: Show Remaining Credits  ***" << endl;
        cout << "*** 7. Exit                             ***" << endl;
        cout << "*******************************************" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string courseName, courseCode, timeSlot;
            float price;
            int duration;
            cout << "Enter Course Name: ";
            cin.ignore(); // Ignore newline from previous input
            getline(cin, courseName);
            cout << "Enter Course Code: ";
            getline(cin, courseCode);
            cout << "Enter Price: ";
            cin >> price;
            cin.ignore(); // Ignore newline from previous input
            cout << "Enter Time Slot: ";
            getline(cin, timeSlot);
            cout << "Enter Duration (in weeks): ";
            cin >> duration;
            teacher.createCourse(courseName, courseCode, price, timeSlot, duration);
            webpage.addCourse(Course(courseName, courseCode, price, timeSlot, duration)); // Provide all 5 arguments
            break;
        }
        case 2:
        {
            student.browseCourses(webpage.getAllCourses());
            int courseChoice;
            cout << "Enter Course Number to Buy: ";
            cin >> courseChoice;
            if (courseChoice >= 1 && courseChoice <= webpage.getAllCourses().size())
            {
                student.buyCourse(webpage.getAllCourses()[courseChoice - 1]);
            }
            else
            {
                cout << "Invalid course choice!" << endl;
            }
            break;
        }
        case 3:
            student.browseCourses(webpage.getAllCourses());
            break;
        case 4:
            student.displayProfile();
            break;
        case 5:
            float credits;
            cout << "Enter credits to add: ";
            cin >> credits;
            student.addCredits(credits);
            break;
        case 6:
            cout << "Remaining Credits: " << student.getCreditBalance() << endl;
            break;
        case 7:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    } while (choice != 7);

    return 0;
}
