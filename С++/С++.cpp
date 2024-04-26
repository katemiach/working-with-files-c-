#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define MAX_NAME_LEN 50
#define MAX_LINE_LEN 200
#define MAX_STUDENTS 100

using namespace std;

// Structure for "Student"
struct Student {
    string name;
    int grade;
    string phone;
    int math, physics, russian, literature;
};

// Function to write student data to file
void writeStudent(ofstream& file, const Student& student) {
    file << student.name << "," << student.grade << "," << student.phone << ","
        << student.math << "," << student.physics << "," << student.russian << ","
        << student.literature << endl;
}

// Function to read student data from file
bool readStudent(ifstream& file, Student& student) {
    string line;
    if (getline(file, line)) {
        // Splitting the line into fields by ","
        size_t pos = 0;
        vector<string> tokens;
        while ((pos = line.find(',')) != string::npos) {
            tokens.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        tokens.push_back(line); // Extra field

        if (tokens.size() == 7) {
            // Filling the structure
            student.name = tokens[0];
            student.grade = stoi(tokens[1]);
            student.phone = tokens[2];
            student.math = stoi(tokens[3]);
            student.physics = stoi(tokens[4]);
            student.russian = stoi(tokens[5]);
            student.literature = stoi(tokens[6]);
            return true;
        }
    }
    return false;
}

int main() {
    // 1. Створення файлу та запис структурованих даних
    ofstream file("txt1.txt");
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    int numStudents;
    cout << "Enter the number of students: ";
    cin >> numStudents;

    for (int i = 0; i < numStudents; ++i) {
        Student student;
        cout << "Student " << i + 1 << ":" << endl;
        cout << "Name: ";
        cin.ignore();
        getline(cin, student.name);
        cout << "Grade: ";
        cin >> student.grade;
        cout << "Phone: ";
        cin >> student.phone;
        cout << "Math: ";
        cin >> student.math;
        cout << "Physics: ";
        cin >> student.physics;
        cout << "Russian: ";
        cin >> student.russian;
        cout << "Literature: ";
        cin >> student.literature;

        writeStudent(file, student);
    }

    file.close();

    // 2. Відображення створеного файлу на екрані
    ifstream readFile("txt1.txt");
    if (!readFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    cout << "\nOriginal file contents:" << endl;
    Student student;
    while (readStudent(readFile, student)) {
        cout << "Name: " << student.name << ", Grade: " << student.grade << ", Phone: " << student.phone << endl;
        cout << "Math: " << student.math << ", Physics: " << student.physics << ", Russian: " << student.russian << ", Literature: " << student.literature << endl;
    }

    readFile.close();

    // 3. Додавання даних до файлу
    int K;
    cout << "\nEnter the number of students to add: ";
    cin >> K;

    ofstream appendFile("txt1.txt", ios::app);
    if (!appendFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    for (int i = 0; i < K; ++i) {
        Student newStudent;
        cout << "Student " << i + 1 << ":" << endl;
        cout << "Name: ";
        cin.ignore();
        getline(cin, newStudent.name);
        cout << "Grade: ";
        cin >> newStudent.grade;
        cout << "Phone: ";
        cin >> newStudent.phone;
        cout << "Math: ";
        cin >> newStudent.math;
        cout << "Physics: ";
        cin >> newStudent.physics;
        cout << "Russian: ";
        cin >> newStudent.russian;
        cout << "Literature: ";
        cin >> newStudent.literature;

        writeStudent(appendFile, newStudent);
    }

    appendFile.close();

    // 4. Видалення даних з файлу
    ifstream inFile("txt1.txt");
    if (!inFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile.is_open()) {
        cout << "Error opening temporary file!" << endl;
        inFile.close();
        return 1;
    }

    while (readStudent(inFile, student)) {
        if (!(student.math == 2 || student.physics == 2 || student.russian == 2 || student.literature == 2)) {
            writeStudent(tempFile, student);
        }
    }

    inFile.close();
    tempFile.close();

    remove("txt1.txt");
    rename("temp.txt", "txt1.txt");

    // 5. Відображення зміненого файлу на екрані

    ifstream modifiedFile("txt1.txt");
    if (!modifiedFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    cout << "\nModified file contents:" << endl;
    while (readStudent(modifiedFile, student)) {
        cout << "Name: " << student.name << ", Grade: " << student.grade << ", Phone: " << student.phone << endl;
        cout << "Math: " << student.math << ", Physics: " << student.physics << ", Russian: " << student.russian << ", Literature: " << student.literature << endl;
    }

    modifiedFile.close();

    return 0;
}
