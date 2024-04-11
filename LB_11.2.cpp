#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

enum Specialty {
    ComputerScience,
    Informatics,
    MathAndEconomics,
    PhysicsAndInformatics,
    LaborEducation
};

struct Student {
    std::string surname;
    int course;
    Specialty specialty;
    int physicsGrade;
    int mathGrade;
    union {
        int programmingGrade;
        int numericalMethodsGrade;
        int pedagogyGrade;
    };
};

int countExcellentStudents(const std::vector<Student>& students) {
    int count = 0;
    for (const auto& student : students) {
        if (student.physicsGrade == 5 && student.mathGrade == 5 &&
            ((student.specialty == ComputerScience && student.programmingGrade == 5) ||
                (student.specialty == Informatics && student.numericalMethodsGrade == 5) ||
                (student.specialty != ComputerScience && student.specialty != Informatics && student.pedagogyGrade == 5))) {
            ++count;
        }
    }
    return count;
}

double calculatePhysics5Percentage(const std::vector<Student>& students) {
    int count = 0;
    for (const auto& student : students) {
        if (student.physicsGrade == 5) {
            ++count;
        }
    }
    return 100.0 * count / students.size();
}

std::vector<Student> createStudents() {
    int studentCount;
    std::cout << "Enter the number of students: ";
    std::cin >> studentCount;

    std::vector<Student> students(studentCount);
    for (int i = 0; i < studentCount; ++i) {
        std::cout << "Enter student's surname: ";
        std::cin >> students[i].surname;
        std::cout << "Enter student's course: ";
        std::cin >> students[i].course;
        std::cout << "Enter student's specialty (0 - ComputerScience, 1 - Informatics, 2 - MathAndEconomics, 3 - PhysicsAndInformatics, 4 - LaborEducation): ";
        int specialty;
        std::cin >> specialty;
        students[i].specialty = static_cast<Specialty>(specialty);
        std::cout << "Enter the physics grade: ";
        std::cin >> students[i].physicsGrade;
        std::cout << "Enter the math grade: ";
        std::cin >> students[i].mathGrade;
        switch (students[i].specialty) {
        case ComputerScience:
            std::cout << "Enter the programming grade: ";
            std::cin >> students[i].programmingGrade;
            break;
        case Informatics:
            std::cout << "Enter the numerical methods grade: ";
            std::cin >> students[i].numericalMethodsGrade;
            break;
        default:
            std::cout << "Enter the pedagogy grade: ";
            std::cin >> students[i].pedagogyGrade;
            break;
        }
    }

    // Print table
    cout << "==============================================================================================" << endl;
    cout << "| # | Surname       | Course | Specialization               | Physics | Mathematics | Additional Grade |" << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < students.size(); ++i) {
        cout << "| " << setw(1) << right << i + 1 << " | ";
        cout << setw(13) << left << students[i].surname << " | ";
        cout << setw(6) << right << students[i].course << " | ";

        switch (students[i].specialty) {
        case ComputerScience:
            cout << setw(28) << left << "Computer Science" << " | ";
            cout << setw(7) << right << students[i].physicsGrade << " | ";
            cout << setw(11) << right << students[i].mathGrade << " | ";
            cout << setw(16) << right << students[i].programmingGrade << " |" << endl;
            break;
        case Informatics:
            cout << setw(28) << left << "Informatics" << " | ";
            cout << setw(7) << right << students[i].physicsGrade << " | ";
            cout << setw(11) << right << students[i].mathGrade << " | ";
            cout << setw(16) << right << students[i].numericalMethodsGrade << " |" << endl;
            break;
        case MathAndEconomics:
            cout << setw(28) << left << "Math and Economics" << " | ";
            cout << setw(7) << right << students[i].physicsGrade << " | ";
            cout << setw(11) << right << students[i].mathGrade << " | ";
            cout << setw(16) << right << students[i].pedagogyGrade << " |" << endl;
            break;
        case PhysicsAndInformatics:
            cout << setw(28) << left << "Physics and Informatics" << " | ";
            cout << setw(7) << right << students[i].physicsGrade << " | ";
            cout << setw(11) << right << students[i].mathGrade << " | ";
            cout << setw(16) << right << students[i].numericalMethodsGrade << " |" << endl;
            break;
        case LaborEducation:
            cout << setw(28) << left << "Labor Training" << " | ";
            cout << setw(7) << right << students[i].physicsGrade << " | ";
            cout << setw(11) << right << students[i].mathGrade << " | ";
            cout << setw(16) << right << students[i].pedagogyGrade << " |" << endl;
            break;
        }
    }
    cout << "==============================================================================================" << endl;

    int excellentCount = countExcellentStudents(students);
    std::cout << "Number of students with excellent grades: " << excellentCount << endl;

    double physics5Percentage = calculatePhysics5Percentage(students);
    std::cout << "Percentage of students who got a grade of 5 in Physics: " << physics5Percentage << "%" << endl;

    return students;
}

void writeStudentsToBinaryFile(const std::vector<Student>& students, const std::string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    for (const auto& student : students) {
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    }
    file.close();
    std::cout << "Data has been written to the binary file successfully." << endl;
}

std::vector<Student> readStudentsFromBinaryFile(const std::string& filename) {
    std::vector<Student> students;
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for reading." << endl;
        return students;
    }

    Student student;
    while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        students.push_back(student);
    }
    file.close();
    return students;
}

int main() {
    std::vector<Student> students = createStudents();
    std::string filename;
    std::cout << "Enter the filename to save the data: ";
    std::cin >> filename;

    // Write data to file
    writeStudentsToBinaryFile(students, filename);

    // Read data from file
    std::vector<Student> studentsFromFile = readStudentsFromBinaryFile(filename);

    return 0;
}
