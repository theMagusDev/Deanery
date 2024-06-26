// Copyright (C) 2024 Yuriy Magus

#include <utility>
#include <iostream>
#include <cstdlib>
#include "../include/Student.h"
#include "../include/Exception.h"

std::set<int> Student::occupiedIDs;

Student::Student(
    int id,
    std::string name,
    std::string surname,
    std::string patronymic
) {
    if (Student::isStringCorrect(name)) {
        this->name = std::move(name);
    } else {
        throw InvalidNameException((
           "Invalid name! Only English letters and '-' are allowed; "
           "0 < length <= 34. Got " + name).c_str());
    }
    if (Student::isStringCorrect(surname)) {
        this->surname = std::move(surname);
    } else {
        throw InvalidSurnameException((
            "Invalid surname! Only English letters and '-' are allowed; "
            "0 < length <= 34. Got " + surname).c_str());
    }
    if (Student::isStringCorrect(patronymic)) {
        this->patronymic = std::move(patronymic);
    } else {
        throw InvalidPatronymicException((
            "Invalid patronymic! Only English letters and '-' are allowed; "
            "0 < length <= 34. Got " + patronymic).c_str());
    }

    bool IDisOccupied =
            Student::occupiedIDs.find(id) != Student::occupiedIDs.end();
    if (!IDisOccupied && id >= 0) {
        this->id = id;
        Student::occupiedIDs.insert(id);
    } else {
        srand(time(nullptr));
        int generatedID = rand() % (occupiedIDs.size() * 2) + 1;
        while (occupiedIDs.find(generatedID) != occupiedIDs.end()) {
            generatedID = rand() % (occupiedIDs.size() * 2) + 1;
        }
        this->id = generatedID;
        Student::occupiedIDs.insert(generatedID);

        if (IDisOccupied) {
            std::cerr << "Error in student " << getFullName()
                << ": duplicated student ID, generating automatically: "
                << generatedID << std::endl;
        } else {
            std::cerr << "Error in student " << getFullName()
                << ": student ID mustn't be negative, "
                   "generating automatically: "
                << generatedID << std::endl;
        }
    }

    this->group = nullptr;
}

Student::~Student() {
    Student::occupiedIDs.erase(this->id);
    this->id = -1;
    this->name.clear();
    this->surname.clear();
    this->patronymic.clear();
    this->group = nullptr;
    this->marks.clear();
}

int Student::getId() const {
    return id;
}

void Student::setId(int newId) {
    bool IDisOccupied =
            Student::occupiedIDs.find(newId) != Student::occupiedIDs.end();
    if (!IDisOccupied && newId >= 0) {
        this->id = newId;
        Student::occupiedIDs.insert(newId);
    } else {
        if (IDisOccupied) {
            std::cerr << "Error in student " << getFullName()
                << ": duplicated student ID" << std::endl;
        } else {
            std::cerr << "Error in student " << getFullName()
                << ": student ID mustn't be negative" << std::endl;
        }
    }
}

const std::string &Student::getName() const {
    return name;
}

void Student::setName(const std::string& newName) {
    if (Student::isStringCorrect(newName)) {
        this->name = newName;
    } else {
        throw InvalidNameException((
            "Invalid name! Only English letters and '-' are allowed; "
            "0 < length <= 34. Got " + newName).c_str());
    }
}

const std::string &Student::getSurname() const {
    return surname;
}

void Student::setSurname(const std::string& newSurname) {
    if (Student::isStringCorrect(newSurname)) {
        this->surname = newSurname;
    } else {
        throw InvalidSurnameException((
            "Invalid surname! Only English letters and '-' are allowed; "
            "0 < length <= 34. Got " + newSurname).c_str());
    }
}

const std::string &Student::getPatronymic() const {
    return patronymic;
}

void Student::setPatronymic(const std::string& newPatronymic) {
    if (Student::isStringCorrect(newPatronymic)) {
        this->patronymic = newPatronymic;
    } else {
        throw InvalidPatronymicException((
            "Invalid patronymic! Only English letters and '-' are allowed; "
            "0 < length <= 34. Got " + newPatronymic).c_str());
    }
}

const std::string& Student::getFullName() const {
    return *(new std::string(name + " " + surname + " " + patronymic));
}

std::vector<int> Student::getMarks() const {
    return this->marks;
}

Group* Student::getGroup() const {
    return this->group;
}

void Student::enrollToGroup(Group* newGroup) {
    if (this->group != nullptr) {
        this->group->removeStudent(this);
    }
    if (newGroup == nullptr) {
        throw InvalidStudentGroupException("Invalid group: nullptr passed!");
    } else {
        this->group = newGroup;
    }
}

void Student::putMark(int newMark) {
    bool isValidMark = (newMark >= 0) && (newMark <= 10);

    if (isValidMark) {
        marks.push_back(newMark);
    } else {
        throw InvalidMarkException((
            "Invalid mark: expected 0 <= mark <= 10, "
            + std::to_string(newMark) + "got.").c_str());
    }
}

double Student::getAverageMark() const {
    if (marks.empty()) {
        std::cerr << "Error in student " << getFullName()
            << ": student do not have any marks, "
               "can not calculate average" << std::endl;
        return -1.0;
    }

    double result = 0.0;
    for (int mark : marks) {
        result += static_cast<double>(mark);
    }
    result = result / static_cast<double>(marks.size());

    return result;
}

void Student::printStudentPerformance(const std::string& prefix) const {
    std::cout << prefix << "Student "
    << getName() << " " << getSurname() << " " << getPatronymic() << ": ";
    if (this->marks.empty()) {
        std::cout << "no marks" << std::endl;
    } else {
        std::cout << "average mark is " << getAverageMark() << ", marks:";
        for (int mark : marks) {
            std::cout << " " << mark;
        }
        std::cout << std::endl;
    }
}

bool Student::isStringCorrect(const std::string& str) {
    if (str.length() > 34 || str.empty()) {
        return false;
    }
    bool isUpperCaseLetter = false;
    bool isLowerCaseLetter = false;
    bool isHyphen = false;
    for (char strChar : str) {
        isUpperCaseLetter = strChar >= 'A' && strChar <= 'Z';
        isLowerCaseLetter = strChar >= 'a' && strChar <= 'z';
        isHyphen = (strChar == '-');
        if (!(isUpperCaseLetter || isLowerCaseLetter || isHyphen)) {
            return false;
        }
    }

    return true;
}

// help function for Group's removeStudent function
void Student::eraseGroup() {
    this->group = nullptr;
}
