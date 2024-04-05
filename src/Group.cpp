// Copyright (C) 2024 Yuriy Magus

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../include/Group.h"
#include "../include/Exception.h"

Group::Group(std::string& title) {
    if (Group::occupiedTitles.find(&title) != Group::occupiedTitles.end()) {
        this->title = title;
    } else {
        throw DuplicatedGroupTitleException(std::string("Duplicated group title: got " + title));
    }
}

Group::Group(std::string &title, Specialization spec) : Group(title) {
    this->spec = spec;
}

const std::string& Group::getTitle() const {
    return this->title;
}

void Group::setTitle(const std::string &newTitle) {
    this->title = newTitle;
}

std::string Group::getSpec() const {
    switch (spec) {
        case Specialization::UNINITIALIZED:
            return "Uninitialized";
        case Specialization::MATH:
            return "Math";
        case Specialization::COMPUTER_SCIENCE:
            return "Computer science";
        case Specialization::LAW:
            return "Law";
        case Specialization::ECONOMICS:
            return "Economics";
        case Specialization::HUMANITIES:
            return "Humanities";
        default:
            return "Unknown";
    }
}

void Group::setSpec(Specialization newSpec) {
    if (newSpec != Specialization::UNINITIALIZED) {
        Group::spec = newSpec;
    } else {
        throw NullSpecException(std::string("Setting spec to uninitialized state is prohibited!"));
    }
}

std::vector<Student*> Group::getStudents() const {
    return this->students;
}

std::string Group::getHead(char separator) const {
    if (this->head == nullptr) {
        return "No head";
    } else {
        return head->getName() + separator + head->getSurname() + separator + head->getPatronymic();
    }
}

void Group::addStudent(Student* student) {
    for (Student* studentPtr : students) {
        if (studentPtr == student) {
            std::cerr << "Error: student already presents in this group." << std::endl;
        }
        if (student->getId() == headID) {
            this->head = student;
        }
    }

    students.push_back(student);
}

void Group::removeStudent(Student& student) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i] == &student) {
            students.erase(students.begin() + i);
            student.eraseGroup();
            if (&student == this->head) {
                electHead();
            }
            return;
        }
    }

    std::cerr << "Error: no student " << student.getName() << " " + student.getSurname() << " " + student.getPatronymic() << " found." << std::endl;
}

void Group::electHead() {
    if (students.empty()) {
        std::cerr << "Error electing head: group " << title << " is empty." << std::endl;
        this->head = nullptr;
        return;
    }

    this->head = students[rand() % students.size()];
    this->headID = this->head->getId();
}

Student* Group::searchStudent(int studentID) const {
    for (Student* student : students) {
        if (student->getId() == studentID) {
            return student;
        }
    }

    return nullptr;
}

Student *Group::searchStudent (
    std::string &name,
    std::string &surname,
    std::string &patronymic
) const {
    bool nameMatches = false;
    bool surnameMatches = false;
    bool patronymicMatches = false;

    for (Student* student : students) {
        nameMatches = student->getName() == name;
        surnameMatches = student->getName() == surname;
        patronymicMatches = student->getPatronymic() == patronymic;
        if (nameMatches && surnameMatches && patronymicMatches) {
            return student;
        }
    }

    return nullptr;
}

double Group::getAverageMark() const {
    double result = 0.0;
    for (Student* student : students) {
        result += student->getAverageMark();
    }
    result = result / static_cast<double>(students.size());

    return result;
}

void Group::printGroupInfo() const {
    std::cout << "Group '" << getTitle() << "': " << std::endl;
    std::cout << "Specialization: " << getSpec() << std::endl;
    std::cout << "Head: " << getHead() << std::endl;
    std::cout << "Average mark: " << getAverageMark() << std::endl;
    std::cout << "Number of students: " << students.size() << std::endl;
}

bool Group::checkStudentPresence(Student& student) {
    for (Student* studentIterator : students) {
        if (studentIterator == &student) {
            return true;
        }
    }

    return false;
}

int Group::getHeadID() const {
    if (head == nullptr) {
        return -1;
    }

    return head->getId();
}

void Group::setHeadID(int id) {
    if (id >= 0) {
        this->headID = id;
    } else {
        throw InvalidIDException(std::string("Invalid head's id: it must not be negative."));
    }
}

void Group::addToStudentsIDs(int id) {
    if (id >= 0) {
        studentsIDs.push_back(id);
    } else {
        throw InvalidIDException(std::string("Invalid head's id: it must not be negative."));
    }
}

std::vector<int> Group::getStudentsIDs() const {
    return this->studentsIDs;
}
