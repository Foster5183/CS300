#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

// Class representing a Course
class Course {
public:
    string number;                // Course number
    string title;                 // Course title
    vector<string> prerequisites; // List of prerequisite course numbers

    // Constructor to initialize a Course object
    Course(string num, string t, vector<string> preq) : number(num), title(t), prerequisites(preq) {}

    // Method to return course details as a string
    string toString() const {
        string result = "Course Number: " + number + ", Title: " + title + ", Prerequisites: ";
        for (size_t i = 0; i < prerequisites.size(); ++i) {
            if (i != 0) result += ", ";
            result += prerequisites[i];
        }
        return result;
    }
};

// Function to load courses from a file into the provided unordered_map
void loadCourses(unordered_map<string, Course>& courses) {
    string fileName;
    fileName = "CS 300 ABCU_Advising_Program_Input.csv";
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    string line;
    // Read each line from the file
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, title, temp;
        vector<string> prerequisites;

        // Extract course number and title
        getline(ss, courseNumber, ',');
        getline(ss, title, ',');

        // Extract prerequisites, if any
        while (getline(ss, temp, ',')) {
            prerequisites.push_back(temp);
        }

        // Check if course number and title are present
        if (courseNumber.empty() || title.empty()) {
            cerr << "Error: Line does not have at least course number and title" << endl;
            continue;
        }

        // Create a Course object and add it to the unordered_map HashTable
        Course course(courseNumber, title, prerequisites);
        courses[courseNumber] = course;
    }

    file.close();
}

// Function to print all courses in alphanumeric order
void printAllCourses(const unordered_map<string, Course>& courses) {
    map<string, Course> sortedCourses(courses.begin(), courses.end());

    // Print each course in the sorted map
    for (const auto& pair : sortedCourses) {
        cout << pair.second.toString() << endl;
    }
}

// Function to print information for a specific course
void printCourseInfo(const unordered_map<string, Course>& courses) {
    string courseNumber;
    cout << "Enter course number: ";
    cin >> courseNumber;

    // Search for the course and print its details if found
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        cout << it->second.toString() << endl;
    }
    else {
        cerr << "Error: Course " << courseNumber << " not found" << endl;
    }
}

// Function to validate the prerequisites of all courses
void validatePrerequisites(const unordered_map<string, Course>& courses) {
    for (const auto& pair : courses) {
        const Course& course = pair.second;
        // Check if each prerequisite exists in the courses map
        for (const string& prereq : course.prerequisites) {
            if (courses.find(prereq) == courses.end()) {
                cerr << "Error: Prerequisite " << prereq << " for course " << course.number << " does not exist" << endl;
            }
        }
    }
}

int main() {
    unordered_map<string, Course> courses;
    int choice;

    // Main menu loop
    do {
        cout << "Menu:" << endl;
        cout << "1. Load the file data into the data structure" << endl;
        cout << "2. Print an alphanumeric list of all the courses" << endl;
        cout << "3. Print the course title and the prerequisites for any individual course" << endl;
        cout << "9. Exit the program" << endl;
        cout << "Enter your option: ";
        cin >> choice;

        // Perform actions based on the user's menu choice
        switch (choice) {
        case 1:
            loadCourses(courses);       // Load course data from file
            validatePrerequisites(courses); // Validate prerequisites
            break;
        case 2:
            printAllCourses(courses);   // Print all courses in alphanumeric order
            break;
        case 3:
            printCourseInfo(courses);   // Print specific course information
            break;
        case 9:
            cout << "Exiting program." << endl;
            break;
        default:
            cerr << "Invalid option. Please try again." << endl;
        }
    } while (option != 9); // Loop until the user chooses to exit

    return 0;
}
