// Copyright (C) 2024 Yuriy Magus

#ifndef INCLUDE_STUDENT_H_
#define INCLUDE_STUDENT_H_

#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include "Group.h"

class Group;

class Student {
 public:
    Student(int id,
            std::string name,
            std::string  surname,
            std::string  patronymic);
    ~Student();

    int getId() const;
    void setId(int newId);
    const std::string& getName() const;
    void setName(const std::string &newName);
    const std::string& getSurname() const;
    void setSurname(const std::string &newSurname);
    const std::string& getPatronymic() const;
    void setPatronymic(const std::string &newPatronymic);
    const std::string& getFullName() const;
    std::vector<int> getMarks() const;
    Group* getGroup() const;

    void enrollToGroup(Group* newGroup);
    void eraseGroup();
    void putMark(int newMark);
    double getAverageMark() const;
    void printStudentPerformance(const std::string& prefix = "") const;

 private:
    int id;
    std::string name;
    std::string surname;
    std::string patronymic;
    Group* group;
    std::vector<int> marks;

    static std::set<int> occupiedIDs;

    bool isStringCorrect(const std::string& str) const;
};


#endif  // INCLUDE_STUDENT_H_
