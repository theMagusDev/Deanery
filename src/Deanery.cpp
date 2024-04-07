// Copyright (C) 2024 Yuriy Magus

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstdio>
#include <direct.h>
#include <sys/stat.h>
#include <string>
#include <sstream>
#include "../include/Deanery.h"
#include "../include/Utilities.h"
#include "../include/Exception.h"

#define STUDENT_LINE_MAX_DIGITS_NUMBER 7
#define GROUP_LINE_MAX_DIGITS_NUMBER 7

Deanery::Deanery() {
    srand(time(nullptr));

    // check and create bd folder
    const char* dir = "../bd"; // directory
    struct stat myStat; // stat for check
    if (stat(dir, &myStat) != 0) {
        int returnCode = mkdir(dir);
        if (returnCode == -1) {
            throw FolderCreationException(std::string("Error creating bd folder."));
        }
    }
}

Deanery::Deanery(std::vector<Group*>& groups) : Deanery() {
    this->groups = std::move(groups);
}

std::vector<Student*> Deanery::createStudentsFromFile() {
    FILE* stream = fopen("../bd/students_data.txt", "r");
    if (stream == nullptr) {
        throw FileOpeningException(std::string("Error opening students_data file."));
    }
    fseek(stream, 0, SEEK_SET);

    int maxStudentLineLength = 0;
    std::string stringMaxStudentLineLength;
    char tempChar = getc(stream);
    while (tempChar != '#') {
        stringMaxStudentLineLength.push_back(tempChar);
        tempChar = getc(stream);
    }
    maxStudentLineLength = std::stoi(stringMaxStudentLineLength);

    char* buffer = new char[maxStudentLineLength];
    char* fgetsResult = fgets(buffer, maxStudentLineLength, stream);
    fgetsResult = fgets(buffer, maxStudentLineLength, stream);
    std::string tempLine;
    std::stringstream stringStream;

    Student* createdStudent;
    std::string studentIDstring;
    int studentID = -1;
    std::string name;
    std::string surname;
    std::string patronymic;
    Group* groupPtr;
    std::string groupTitle;
    std::string token;
    std::vector<int> marks;
    bool isMark10 = false;
    bool isOtherMark = false;
    std::vector<Student*> nonAssociatedStudents;

    while (fgetsResult != nullptr) {
        tempLine = buffer;
        stringStream = std::stringstream(tempLine);

        stringStream >> studentIDstring;
        studentID = std::stoi(studentIDstring);
        stringStream >> name;
        stringStream >> surname;
        stringStream >> patronymic;
        stringStream >> groupTitle;
        groupPtr = findGroup(groupTitle);

        createdStudent = new Student(studentID, name, surname, patronymic);

        while (stringStream >> token) {
            isMark10 = token.length() == 2 && token[0] == '1' && token[1] == '0';
            isOtherMark = token.length() == 1 && token[0] >= '0' && token[0] <= '9';
            if (!(isMark10 || isOtherMark)) {
                break;
            }
            createdStudent->putMark(std::stoi(token));
        }

        if (groupPtr == nullptr) {
            nonAssociatedStudents.push_back(createdStudent);
            std::cerr << "Error: group not found for student " << name << " " << surname << " " << patronymic << "." << std::endl;
        } else {
            createdStudent->enrollToGroup(groupPtr);
            groupPtr->addStudent(createdStudent);
            groupPtr->recoverHeadFromID();
        }

        fgetsResult = fgets(buffer, maxStudentLineLength, stream);
    }

    fclose(stream);
    delete[] buffer;

    return nonAssociatedStudents;
}

void Deanery::saveStudentsFile() const {
    // check and crate students file
    FILE* stream = fopen("../bd/students_data.txt", "w");
    if (stream == nullptr) {
        throw FileOpeningException(std::string("Error opening students_data file."));
    }

    fseek(stream, 0, SEEK_SET);
    size_t maxStudentStringLength = 0;
    fputs(std::string(STUDENT_LINE_MAX_DIGITS_NUMBER, '#').c_str(), stream);

    std::string studentLine;
    size_t fullStudentLineLength = 0;
    for (Group* group : groups) {
        for (Student* student : group->getStudents()) {
            studentLine = std::to_string(student->getId()) + " "
                          + student->getName() + " "
                          + student->getSurname() + " "
                          + student->getPatronymic() + " "
                          + student->getGroup()->getTitle();
            for (int mark : student->getMarks()) {
                studentLine.append(" " + std::to_string(mark));
            }
            // get length including null-termination and newline symbol
            fullStudentLineLength = studentLine.length() + 2;
            if (fullStudentLineLength > maxStudentStringLength) {
                maxStudentStringLength = fullStudentLineLength;
            }
            fputc('\n', stream);
            fputs(studentLine.c_str(), stream);
        }
    }

    fseek(stream, 0, SEEK_SET);
    fputs(std::to_string(maxStudentStringLength).c_str(), stream);
    fclose(stream);
}

void Deanery::createGroupsFromFile() {
    FILE* stream = fopen("../bd/groups_data.txt", "r");
    if (stream == nullptr) {
        throw FileOpeningException(std::string("Error opening groups_data file."));
    }
    fseek(stream, 0, SEEK_SET);

    int maxGroupLineLength = 0;
    std::string stringMaxGroupLineLength;
    char tempChar = getc(stream);
    while (tempChar != '#') {
        stringMaxGroupLineLength.push_back(tempChar);
        tempChar = getc(stream);
    }
    maxGroupLineLength = std::stoi(stringMaxGroupLineLength);

    char* buffer = new char[maxGroupLineLength];
    char* fgetsResult = fgets(buffer, maxGroupLineLength, stream);
    fgetsResult = fgets(buffer, maxGroupLineLength, stream);
    std::string tempLine;
    std::stringstream stringStream;

    Group* createdGroup = nullptr;
    std::string title;
    std::string stringSpecialization;
    Specialization specialization = Specialization::UNINITIALIZED;
    std::vector<int> studentsIDs;
    std::string headID;
    
    std::string token;

    while (fgetsResult != nullptr) {
        tempLine = buffer;
        stringStream = std::stringstream(tempLine);

        stringStream >> title;
        stringStream >> stringSpecialization;
        stringStream >> headID;
        // sorry, there is no switch-case for strings :(
        if (stringSpecialization == "MATH") {
            specialization = Specialization::MATH;
        } else {
            if (stringSpecialization == "COMPUTER_SCIENCE") {
                specialization = Specialization::COMPUTER_SCIENCE;
            } else {
                if (stringSpecialization == "LAW") {
                    specialization = Specialization::LAW;
                } else {
                    if (stringSpecialization == "ECONOMICS") {
                        specialization = Specialization::ECONOMICS;
                    } else {
                        if (stringSpecialization == "HUMANITIES") {
                            specialization = Specialization::HUMANITIES;
                        } else {
                            specialization = Specialization::UNINITIALIZED;
                        }
                    }
                }
            }
        }

        createdGroup = new Group(title, specialization);
        createdGroup->setHeadID(std::stoi(headID));

        while (stringStream >> token) {
            if (!checkStringContainsOnlyDigits(token)) {
                break;
            }
            createdGroup->addToStudentsIDs(std::stoi(token));
        }

        this->addGroup(createdGroup);

        fgetsResult = fgets(buffer, maxGroupLineLength, stream);
    }

    fclose(stream);
    delete[] buffer;
}

void Deanery::saveGroupsFile() const {
    // check and crate students file
    FILE* stream = fopen("../bd/groups_data.txt", "w");
    if (stream == nullptr) {
        throw FileOpeningException(std::string("Error opening groups_data file."));
    }

    fseek(stream, 0, SEEK_SET);
    size_t maxStudentStringLength = 0;
    fputs(std::string(GROUP_LINE_MAX_DIGITS_NUMBER, '#').c_str(), stream);

    std::string groupLine;
    size_t fullGroupLineLength = 0;
    std::string groupSpec;
    for (Group* group : groups) {
        switch (group->getSpecEnum()) {
            case Specialization::UNINITIALIZED:
                groupSpec = "UNINITIALIZED";
                break;
            case Specialization::MATH:
                groupSpec = "MATH";
                break;
            case Specialization::COMPUTER_SCIENCE:
                groupSpec = "COMPUTER_SCIENCE";
                break;
            case Specialization::LAW:
                groupSpec = "LAW";
                break;
            case Specialization::ECONOMICS:
                groupSpec = "ECONOMICS";
                break;
            case Specialization::HUMANITIES:
                groupSpec = "HUMANITIES";
                break;
            default:
                groupSpec = "UNINITIALIZED";
                break;
        }
        groupLine = group->getTitle() + " "
                + groupSpec + " "
                + std::to_string(group->getHeadID());
        for (Student* student : group->getStudents()) {
            groupLine.append(" " + std::to_string(student->getId()));
        }
        // get length including null-termination and newline symbol
        fullGroupLineLength = groupLine.length() + 2;
        if (fullGroupLineLength > maxStudentStringLength) {
            maxStudentStringLength = fullGroupLineLength;
        }
        fputc('\n', stream);
        fputs(groupLine.c_str(), stream);
    }

    fseek(stream, 0, SEEK_SET);
    fputs(std::to_string(maxStudentStringLength).c_str(), stream);
    fclose(stream);
}

void Deanery::placeMarksToAllAtRandom(Group* group) const {
    if (group->getStudents().empty()) {
        return;
    }

    for (Student* student : group->getStudents()) {
        student->putMark((rand() % 5) + 6); // range: 6-10
    }
}

// One function to print in console and give performance statistics
void Deanery::printPerformanceData() const {
    if (groups.empty()) {
        std::cout << "No groups with students found, can not print anything." << std::endl;
        return;
    }

    std::cout << "<= Performance data =>" << std::endl;
    for (Group* group : groups) {
        group->printGroupInfo();
        for (Student* student : group->getStudents()) {
            student->printStudentPerformance(" ");
        }
    }
}

void Deanery::transferToGroup(const std::vector<Student*>& students, Group& group) const {
    for (Student* student : students) {
        if (!group.checkStudentPresence(*student)) {
            student->enrollToGroup(&group);
            group.addStudent(student);
        }
    }
}

// Function to expel students, given in vector.
// Returns the vector of successfully expelled students.
std::vector<Student*>* Deanery::expelStudents(std::vector<Student*>& studentsToExpel) {
    std::vector<Student*>* expelledStudents = new std::vector<Student*>;

    Group* studentGroup = nullptr;
    for (Student* studentIterator : studentsToExpel) {
        studentGroup = studentIterator->getGroup();
        if (studentGroup != nullptr) {
            studentGroup->removeStudent(*studentIterator);
        }
        expelledStudents->push_back(studentIterator);
    }

    return expelledStudents;
}

Group* Deanery::findGroup(const std::string& name) const {
    for (Group* group : groups) {
        if (group->getTitle() == name) {
            return group;
        }
    }

    return nullptr;
}

/**
 * 1) calls removeStudent in each group;
 * 2) frees allocated for removed students memory.
 */
void Deanery::clearStudents() {
    for (Group* group : groups) {
        for (Student* student : group->getStudents()) {
            group->removeStudent(*student);
            delete student;
        }
    }
}

/**
 * 1) frees allocated for removed students memory;
 * 2) erases groups vector.
 */
void Deanery::clearGroups() {
    for (Group* group : groups) {
        delete group;
    }
    groups.clear();
}

void Deanery::loadDataFromFile() {
    clearStudents();
    clearGroups();

    createGroupsFromFile();
    createStudentsFromFile();
}

void Deanery::saveDataToFile() {
    saveStudentsFile();
    saveGroupsFile();
}

void Deanery::addGroup(Group* group) {
    for (Group* groupIterator : groups) {
        if (groupIterator == group) {
            return;
        }
    }

    groups.push_back(group);
}
