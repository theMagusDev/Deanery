// Copyright (C) 2024 Yuriy Magus

#ifndef INCLUDE_GROUP_H_
#define INCLUDE_GROUP_H_

#include "Student.h"
#include <string>
#include <vector>
#include <unordered_set>

enum class Specialization {
    UNINITIALIZED,
    MATH,
    COMPUTER_SCIENCE,
    LAW,
    ECONOMICS,
    HUMANITIES
};

class Student;

class Group {
 public:
    explicit Group(std::string title);
    Group(std::string title, Specialization spec);
    ~Group();

    const std::string& getTitle() const;
    void setTitle(const std::string& newTitle);
    std::string getSpec() const;
    void setSpec(Specialization newSpec);
    Specialization getSpecEnum() const;
    std::vector<Student*> getStudents() const;
    std::string getHead(char separator = ' ') const;
    int getHeadID() const;
    void setHeadID(int id);
    void addToStudentsIDs(int id);
    std::vector<int> getStudentsIDs() const;

    void addStudent(Student* student);
    void removeStudent(Student* student);
    void electHead();
    void recoverHeadFromID();
    Student* searchStudent(int studentID) const;
    Student* searchStudent(
        std::string name,
        std::string surname,
        std::string patronymic) const;
    bool checkStudentPresence(const Student& student);
    double getAverageMark() const;
    void printGroupInfo() const;

 private:
    std::string title;
    Specialization spec = Specialization::UNINITIALIZED;
    Student* head = nullptr;
    int headID = -1;
    std::vector<Student*> students;
    std::vector<int> studentsIDs;
    // headID and studentsIDs are used only for Deanery's createGroupsFromFile()

    static std::unordered_set<std::string> occupiedTitles;
};


#endif  // INCLUDE_GROUP_H_
