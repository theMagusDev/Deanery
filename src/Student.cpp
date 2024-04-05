#include <utility>
#include <iostream>
#include <cstdlib>
#include "../include/Student.h"
#include "../include/Exception.h"

std::unordered_set<int> Student::occupiedIDs;

Student::Student(
    int id,
    std::string name,
    std::string surname,
    std::string patronymic
) {
    bool IDisOccupied = Student::occupiedIDs.find(id) == Student::occupiedIDs.end();
    if (!IDisOccupied && id >= 0) {
        this->id = id;
    } else {
        if (IDisOccupied) {
            std::cerr << "Error: duplicated student ID, generating automatically." << std::endl;
        } else {
            std::cerr << "Error: student ID mustn't be negative, generating automatically." << std::endl;
        }
        srand(time(nullptr));
        int generatedID = rand() % (occupiedIDs.size() * 2) + 1;
        while (occupiedIDs.find(generatedID) != occupiedIDs.end()) {
            generatedID = rand() % (occupiedIDs.size() * 2) + 1;
        }
        this->id = generatedID;
    }

    if (isStringCorrect(name)) {
        this->name = std::move(name);
    } else {
        throw InvalidNameException(std::string("Invalid name! Only English letters and '-' are allowed; 0 < length <= 34. Got " + name));
    }
    if (isStringCorrect(surname)) {
        this->surname = std::move(surname);
    } else {
        throw InvalidSurnameException(std::string("Invalid surname! Only English letters and '-' are allowed; 0 < length <= 34. Got " + surname));
    }
    if (isStringCorrect(patronymic)) {
        this->patronymic = std::move(patronymic);
    } else {
        throw InvalidPatronymicException(std::string("Invalid patronymic! Only English letters and '-' are allowed; 0 < length <= 34. Got " + patronymic)) ;
    }

    this->group = nullptr;
}

Student::~Student() {
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
    Student::id = newId;
}

const std::string &Student::getName() const {
    return name;
}

void Student::setName(const std::string &newName) {
    Student::name = newName;
}

const std::string &Student::getSurname() const {
    return surname;
}

void Student::setSurname(const std::string &newSurname) {
    Student::surname = newSurname;
}

const std::string &Student::getPatronymic() const {
    return patronymic;
}

void Student::setPatronymic(const std::string &newPatronymic) {
    Student::patronymic = newPatronymic;
}

std::vector<int> Student::getMarks() const {
    return this->marks;
}

Group* Student::getGroup() const {
    return this->group;
}

void Student::enrollToGroup(Group* newGroup) {
    this->group = newGroup;
    if (newGroup == nullptr) {
        throw InvalidStudentGroupException(std::string("Invalid group: nullptr passed!"));
    } else {
        newGroup->addStudent(this);
    }
}

void Student::putMark(int newMark) {
    bool isValidMark = (newMark >= 0) && (newMark <= 10);

    if (isValidMark) {
        marks.push_back(newMark);
    } else {
        throw InvalidMarkException(std::string("Invalid mark: expected 0 <= mark <= 10, " + std::to_string(newMark) + "got."));
    }
}

double Student::getAverageMark() const {
    double result = 0.0;
    for (int mark : marks) {
        result += static_cast<double>(mark);
    }
    result = result / static_cast<double>(marks.size());

    return result;
}

void Student::printStudentPerformance(const std::string& prefix) const {
    std::cout << prefix << "Student "
    << getName() << " " << getSurname() << " " << getPatronymic()
    << ": average mark is " << getAverageMark() << std::endl;
}

bool Student::isStringCorrect(const std::string& str) const {
    if (str.length() > 34 || str.empty()) {
        return false;
    }
    bool isUpperCaseLetter = false;
    bool isLowerCaseLetter = false;
    bool isDash = false;
    for (char strChar : str) {
        isUpperCaseLetter = strChar > 'A' && strChar < 'Z';
        isLowerCaseLetter = strChar > 'a' && strChar < 'z';
        isDash = (strChar == '-');
        if (!(isUpperCaseLetter || isLowerCaseLetter || isDash)) {
            return false;
        }
    }

    return true;
}

// help function for Group's removeStudent function
void Student::eraseGroup() {
    this->group = nullptr;
}
