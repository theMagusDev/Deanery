// Copyright (C) 2024 Yuriy Magus

#ifndef INCLUDE_DEANERY_H
#define INCLUDE_DEANERY_H

#include <vector>
#include "Group.h"

class Deanery {
 public:
    Deanery();
    explicit Deanery(std::vector<Group*>& groups);

    void placeMarksToAllAtRandom(Group* group) const;
    void printPerformanceData() const;
    void transferToGroup(const std::vector<Student*>& students, Group& group) const;
    Group* findGroup(const std::string& name) const;
    std::vector<Student*>* expelStudents(std::vector<Student*>& students);
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
    void initGroupFieldsLinks();
};


#endif // INCLUDE_DEANERY_H
