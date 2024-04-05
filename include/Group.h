// Copyright (C) 2024 Yuriy Magus

#ifndef INCLUDE_GROUP_H
#define INCLUDE_GROUP_H

#include "Student.h"
#include <string>
#include <vector>

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
    Group(std::string& title);
    Group(std::string& title, Specialization spec);

    const std::string& getTitle() const;
    void setTitle(const std::string& newTitle);
    std::string getSpec() const;
    void setSpec(Specialization newSpec);
    std::vector<Student*> getStudents() const;
    std::string getHead(char separator = ' ') const;
    int getHeadID() const;
    void setHeadID(int id);
    void addToStudentsIDs(int id);
    std::vector<int> getStudentsIDs() const;

    void addStudent(Student* student);
    void removeStudent(Student& student);
    void electHead();
    Student* searchStudent(int studentID) const;
    Student* searchStudent(
        std::string& name,
        std::string& surname,
        std::string& patronymic
    ) const;
    bool checkStudentPresence(Student& student);
    double getAverageMark() const;
    void printGroupInfo() const;

 private:
    std::string title;
    Specialization spec = Specialization::UNINITIALIZED;
    Student* head = nullptr;
    int headID = -1; // used only for Deanery's createGroupsFromFile()
    std::vector<Student*> students;
    std::vector<int> studentsIDs; // used only for Deanery's createGroupsFromFile()

    static std::unordered_set<std::string*> occupiedTitles;
};


#endif // INCLUDE_GROUP_H
