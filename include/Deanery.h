// Copyright (C) 2024 Yuriy Magus

#ifndef INCLUDE_DEANERY_H
#define INCLUDE_DEANERY_H

#include <vector>
#include "Group.h"

class Student;
class Group;

class Deanery {
 public:
    Deanery();
    explicit Deanery(std::vector<Group*>& groups);

    void addGroup(Group* group);
    void placeMarksToAllAtRandom(Group* group) const;
    void printPerformanceData() const;
    void transferToGroup(const std::vector<Student*>& students, Group& group) const;
    Group* findGroup(const std::string& name) const;
    std::vector<Student*>* expelStudents(std::vector<Student*>& studentsToExpel);
    void loadDataFromFile();
    void saveDataToFile();

private:
    std::vector<Group*> groups;

    std::vector<Student*> createStudentsFromFile();
    void saveStudentsFile() const;
    void createGroupsFromFile();
    void saveGroupsFile() const;
    void clearStudents();
    void clearGroups();
};


#endif // INCLUDE_DEANERY_H
