#include <iostream>
#include "../include/Deanery.h"
#include "../include/Student.h"
#include "../include/Group.h"
#include "../include/Exception.h"

using namespace std;

void studentConstructorsDemo();
void studentMethodsDemo();
void groupMethodsDemo();
void deaneryMethodsDemo();
void deaneryLoadMethod();

int main() {
//    studentConstructorsDemo();
//    studentMethodsDemo();
//    groupMethodsDemo();
//    deaneryMethodsDemo();
//    deaneryLoadMethod();

    return 0;
}

void studentConstructorsDemo() {
    // Create a student correctly
    Student* artem = new Student(1, "Artem", "Ivanov", "Sergeevich");

    // Let's create student with duplicated or negative ID:
    Student* petya = new Student(1, "Petya", "Petrov", "Vasilievich");
    // Error in student Petya Petrov Vasilievich: duplicated student ID, generating automatically: 2
    Student* roma = new Student(-1, "Roman", "Petrov", "Vasilievich");
    // Error in student Roman Petrov Vasilievich: student ID mustn't be negative, generating automatically: 3

    // Let's set duplicated ID
    petya->setId(1);
    // Error in student Petya Petrov Vasilievich: duplicated student ID

    // Let's create a student with incorrect name
    try {
        Student *wrongStudent = new Student(4, "Elena228", "Petrova", "Vladimirovna");
    } catch (InvalidNameException& exception) {
        cout << "Invalid name, message: " << exception.getMessage() << endl;
        // Invalid name, message: Invalid name! Only English letters and '-' are allowed; 0 < length <= 34. Got Elena228
    }
    // incorrect surname, patronymic:
    try {
        Student *wrongStudent = new Student(4, "Elena", "Petr0va", "Vladimirovna");
    } catch (InvalidSurnameException& exception) {
        cout << "Invalid surname, message: " << exception.getMessage() << endl;
        // IInvalid surname, message: Invalid surname! Only English letters and '-' are allowed; 0 < length <= 34. Got Petr0va
    }
    try {
        Student *wrongStudent = new Student(4, "Elena", "Petrova", "Vlad1m1r0vna");
    } catch (InvalidPatronymicException& exception) {
        cout << "Invalid patronymic, message: " << exception.getMessage() << endl;
        // Invalid patronymic, message: Invalid patronymic! Only English letters and '-' are allowed; 0 < length <= 34. Got Vlad1m1r0vna
    }
    // but hyphen is allowed
    Student* correctStudent = new Student(244, "Ann", "Lloyd-Atkinson", "Vladimirovna"); // OK
}

void studentMethodsDemo() {
    Student* artem = new Student(1, "Artem", "Ivanov", "Sergeevich");

    // Let's try to set incorrect values:
    artem->setId(-1);
    // Error in student Artem Ivanov Sergeevich: student ID mustn't be negative
    try {
        artem->setName("Artem228PRO!");
    } catch (InvalidNameException& exception) {
        cout << "Invalid name, message: " << exception.getMessage() << endl;
        // Invalid name, message: Invalid name! Only English letters and '-' are allowed; 0 < length <= 34. Got Artem228PRO!
    }
    try {
        artem->setSurname("IvanovSuper111");
    } catch (InvalidSurnameException& exception) {
        cout << "Invalid surname, message: " << exception.getMessage() << endl;
        // Invalid surname, message: Invalid surname! Only English letters and '-' are allowed; 0 < length <= 34. Got IvanovSuper111
    }
    try {
        artem->setPatronymic("Serg33vi4");
    } catch (InvalidPatronymicException& exception) {
        cout << "Invalid patronymic, message: " << exception.getMessage() << endl;
        // Invalid patronymic, message: Invalid patronymic! Only English letters and '-' are allowed; 0 < length <= 34. Got Serg33vi4
    }

    cout << artem->getId() << endl; // 1
    cout << artem->getName() << endl; // Artem
    cout << artem->getSurname() << endl; // Ivanov
    cout << artem->getPatronymic() << endl; // Sergeevich
    cout << artem->getGroup() << endl; // 0
    cout << artem->getAverageMark() << endl; // -1
    // error: Error in student Artem Ivanov Sergeevich: student do not have any marks, can not calculate average
    artem->printStudentPerformance(); // Student Artem Ivanov Sergeevich: no marks

    for (int mark = 0; mark < 10; mark++) {
        artem->putMark(mark);
    }
    cout << artem->getAverageMark() << endl; // 4.5
    artem->printStudentPerformance();
    // Student Artem Ivanov Sergeevich: average mark is 4.5, marks: 0 1 2 3 4 5 6 7 8 9

    Group* cst1 = new Group("23CST1", Specialization::COMPUTER_SCIENCE);
    cst1->addStudent(artem);
    artem->enrollToGroup(cst1);
    cout << artem->getGroup()->getTitle() << endl; // 23CST1
}

void groupMethodsDemo() {
    Student* vladislav = new Student(1, "Vladislav", "Petrov", "Vasilievich");
    vladislav->putMark(10);
    Student* artem = new Student(2, "Artem", "Ivanov", "Sergeevich");
    artem->putMark(7);
    Student* petya = new Student(3, "Petya", "Petrov", "Vasilievich");
    petya->putMark(5);
    Student* olga = new Student(4, "Olga", "Smirnova", "Ivanovna");
    olga->putMark(7);
    Student* sergei = new Student(5, "Sergei", "Kuznetsov", "Dmitrievich");
    sergei->putMark(8);
    Student* maria = new Student(6, "Maria", "Popova", "Alexandrovna");
    maria->putMark(4);
    Student* pavel = new Student(7, "Pavel", "Morozov", "Viktorovich");
    pavel->putMark(9);
    Student* ekaterinaVolkova = new Student(8, "Ekaterina", "Volkova", "Petrovna");
    ekaterinaVolkova->putMark(7);
    Student* dmitri = new Student(9, "Dmitri", "Kozlov", "Ivanovich");
    dmitri->putMark(5);

    Group* cst1 = new Group("23CST1", Specialization::COMPUTER_SCIENCE);
    cst1->addStudent(vladislav); // OK
    cst1->addStudent(vladislav);
    // Error in group 23CST1: student Vladislav Petrov Vasilievich already presents in this group.
    vladislav->enrollToGroup(cst1);
    cst1->addStudent(olga);
    olga->enrollToGroup(cst1);
    cst1->addStudent(petya);
    petya->enrollToGroup(cst1);
    cst1->addStudent(artem);
    artem->enrollToGroup(cst1);
    cst1->addStudent(sergei);
    sergei->enrollToGroup(cst1);
    cst1->addStudent(maria);
    maria->enrollToGroup(cst1);
    cst1->addStudent(pavel);
    pavel->enrollToGroup(cst1);
    cst1->addStudent(ekaterinaVolkova);
    ekaterinaVolkova->enrollToGroup(cst1);
    cst1->addStudent(dmitri);
    dmitri->enrollToGroup(cst1);

    cout << cst1->getHead() << endl; // No head
    cst1->electHead();
    cout << cst1->getHead() << endl; // Ekaterina Volkova Petrovna (may differ)

    cout << cst1->getSpec() << endl; // Computer science
    try {
        cst1->setSpec(Specialization::UNINITIALIZED);
    } catch (NullSpecException& exception) {
        cout << "Exception setting spec, message: " << exception.getMessage() << endl;
        // Exception setting spec, message: Setting spec to uninitialized state is prohibited!
    }
    cst1->setSpec(Specialization::MATH);
    cout << cst1->getSpec() << endl; // Math

    cst1->printGroupInfo();
    /*
     Group '23CST1':
    Specialization: Math
    Head: Ekaterina Volkova Petrovna
    Average mark: 6.88889
    Number of students: 9
     */
}

void deaneryMethodsDemo() {
    Student* vladislav = new Student(1, "Vladislav", "Petrov", "Vasilievich");
    Student* artem = new Student(2, "Artem", "Ivanov", "Sergeevich");
    Student* petya = new Student(3, "Petya", "Petrov", "Vasilievich");
    Student* olga = new Student(4, "Olga", "Smirnova", "Ivanovna");
    Student* sergei = new Student(5, "Sergei", "Kuznetsov", "Dmitrievich");
    Student* maria = new Student(6, "Maria", "Popova", "Alexandrovna");
    Student* pavel = new Student(7, "Pavel", "Morozov", "Viktorovich");
    Student* ekaterinaVolkova = new Student(8, "Ekaterina", "Volkova", "Petrovna");
    Student* dmitri = new Student(9, "Dmitri", "Kozlov", "Ivanovich");

    vladislav->putMark(10);
    sergei->putMark(8);
    olga->putMark(7);
    petya->putMark(5);
    maria->putMark(4);
    pavel->putMark(9);
    ekaterinaVolkova->putMark(7);
    dmitri->putMark(5);
    artem->putMark(7);

    Group* cst1 = new Group("23CST1", Specialization::COMPUTER_SCIENCE);
    cst1->addStudent(vladislav); // OK
    cst1->addStudent(vladislav);
    // Error in group 23CST1: student Vladislav Petrov Vasilievich already presents in this group.
    vladislav->enrollToGroup(cst1);
    cst1->addStudent(olga);
    olga->enrollToGroup(cst1);
    cst1->addStudent(petya);
    petya->enrollToGroup(cst1);
    cst1->addStudent(artem);
    artem->enrollToGroup(cst1);
    cst1->addStudent(sergei);
    sergei->enrollToGroup(cst1);
    cst1->addStudent(maria);
    maria->enrollToGroup(cst1);
    cst1->addStudent(pavel);
    pavel->enrollToGroup(cst1);
    cst1->addStudent(ekaterinaVolkova);
    ekaterinaVolkova->enrollToGroup(cst1);
    cst1->addStudent(dmitri);
    dmitri->enrollToGroup(cst1);
    cst1->electHead();

    Student* anna = new Student(10, "Anna", "Yakovleva", "Sergeevna");
    Student* alex = new Student(11, "Alex", "Fedorov", "Nikolaevich");
    Student* natalia = new Student(12, "Natalia", "Nikitina", "Vladimirovna");
    Student* andrey = new Student(13, "Andrey", "Ilyin", "Sergeevich");
    Student* alyona = new Student(14, "Alyona", "Orlova", "Viktorovna");
    Student* maxim = new Student(15, "Maxim", "Antonov", "Ivanovich");
    Student* tatiana = new Student(16, "Tatiana", "Gavrilova", "Petrovna");

    anna->putMark(8);
    anna->putMark(6);
    alex->putMark(9);
    alex->putMark(3);
    natalia->putMark(5);
    natalia->putMark(7);
    andrey->putMark(10);
    andrey->putMark(2);
    alyona->putMark(4);
    alyona->putMark(8);
    maxim->putMark(7);
    maxim->putMark(6);
    tatiana->putMark(9);
    tatiana->putMark(4);

    Group* math1 = new Group("23MATH1", Specialization::MATH);
    math1->addStudent(anna);
    anna->enrollToGroup(math1);
    math1->addStudent(alex);
    alex->enrollToGroup(math1);
    math1->addStudent(natalia);
    natalia->enrollToGroup(math1);
    math1->addStudent(andrey);
    andrey->enrollToGroup(math1);
    math1->addStudent(alyona);
    alyona->enrollToGroup(math1);
    math1->addStudent(maxim);
    maxim->enrollToGroup(math1);
    math1->addStudent(tatiana);
    tatiana->enrollToGroup(math1);
    math1->electHead();

    Student* vladimir = new Student(17, "Vladimir", "Golubev", "Viktorovich");
    Student* yulia = new Student(18, "Yulia", "Tarasova", "Sergeevna");
    Student* stanislav = new Student(19, "Stanislav", "Sokolov", "Nikolaevich");
    Student* anastasia = new Student(20, "Anastasia", "Kuzmina", "Alexandrovna");
    Student* fedor = new Student(21, "Fedor", "Egorov", "Vladimirovich");
    Student* polina = new Student(22, "Polina", "Korolyova", "Sergeevna");
    Student* mikhail = new Student(23, "Mikhail", "Zaytsev", "Ivanovich");

    vladimir->putMark(6);
    vladimir->putMark(8);
    yulia->putMark(8);
    yulia->putMark(7);
    stanislav->putMark(5);
    stanislav->putMark(9);
    anastasia->putMark(10);
    anastasia->putMark(3);
    fedor->putMark(4);
    fedor->putMark(8);
    polina->putMark(6);
    polina->putMark(7);
    mikhail->putMark(9);
    mikhail->putMark(5);

    Group* mbbe1 = new Group("23MBBE", Specialization::ECONOMICS);
    mbbe1->addStudent(vladimir);
    vladimir->enrollToGroup(mbbe1);
    mbbe1->addStudent(yulia);
    yulia->enrollToGroup(mbbe1);
    mbbe1->addStudent(stanislav);
    stanislav->enrollToGroup(mbbe1);
    mbbe1->addStudent(anastasia);
    anastasia->enrollToGroup(mbbe1);
    mbbe1->addStudent(fedor);
    fedor->enrollToGroup(mbbe1);
    mbbe1->addStudent(polina);
    polina->enrollToGroup(mbbe1);
    mbbe1->addStudent(mikhail);
    mikhail->enrollToGroup(mbbe1);
    mbbe1->electHead();

    Deanery* hseDeanery = new Deanery();
    hseDeanery->addGroup(cst1);
    hseDeanery->addGroup(math1);
    hseDeanery->addGroup(mbbe1);

    hseDeanery->printPerformanceData();
    // '-->' points to student which will be expelled.
    /*
     <= Performance data =>
     Group '23CST1':
     Specialization: Computer science
     Head: Sergei Kuznetsov Dmitrievich
     Average mark: 6.88889
     Number of students: 9
      Student Vladislav Petrov Vasilievich: average mark is 10, marks: 10
      Student Olga Smirnova Ivanovna: average mark is 7, marks: 7
      Student Petya Petrov Vasilievich: average mark is 5, marks: 5
      Student Artem Ivanov Sergeevich: average mark is 7, marks: 7
      Student Sergei Kuznetsov Dmitrievich: average mark is 8, marks: 8
      Student Maria Popova Alexandrovna: average mark is 4, marks: 4
      Student Pavel Morozov Viktorovich: average mark is 9, marks: 9
      Student Ekaterina Volkova Petrovna: average mark is 7, marks: 7
      Student Dmitri Kozlov Ivanovich: average mark is 5, marks: 5
     Group '23MATH1':
     Specialization: Math
     Head: Maxim Antonov Ivanovich
     Average mark: 6.28571
     Number of students: 7
      Student Anna Yakovleva Sergeevna: average mark is 7, marks: 8 6
-->   Student Alex Fedorov Nikolaevich: average mark is 6, marks: 9 3
      Student Natalia Nikitina Vladimirovna: average mark is 6, marks: 5 7
      Student Andrey Ilyin Sergeevich: average mark is 6, marks: 10 2
      Student Alyona Orlova Viktorovna: average mark is 6, marks: 4 8
      Student Maxim Antonov Ivanovich: average mark is 6.5, marks: 7 6
      Student Tatiana Gavrilova Petrovna: average mark is 6.5, marks: 9 4
     Group '23MBBE':
     Specialization: Economics
     Head: Polina Korolyova Sergeevna
     Average mark: 6.78571
     Number of students: 7
      Student Vladimir Golubev Viktorovich: average mark is 7, marks: 6 8
      Student Yulia Tarasova Sergeevna: average mark is 7.5, marks: 8 7
      Student Stanislav Sokolov Nikolaevich: average mark is 7, marks: 5 9
-->   Student Anastasia Kuzmina Alexandrovna: average mark is 6.5, marks: 10 3
      Student Fedor Egorov Vladimirovich: average mark is 6, marks: 4 8
-->   Student Polina Korolyova Sergeevna: average mark is 6.5, marks: 6 7
      Student Mikhail Zaytsev Ivanovich: average mark is 7, marks: 9 5
     */

    vector<Student*> studentsToBeExpelled;
    studentsToBeExpelled.push_back(mbbe1->searchStudent("Polina", "Korolyova", "Sergeevna"));
    studentsToBeExpelled.push_back(mbbe1->searchStudent("Anastasia", "Kuzmina", "Alexandrovna"));
    studentsToBeExpelled.push_back(math1->searchStudent(11)); // Alex
    cout << "Students to be expelled: " << endl;
    for (Student* student : studentsToBeExpelled) {
        cout << student->getFullName() << endl;
    }
    /*
     Students to be expelled:
     Polina Korolyova Sergeevna
     Anastasia Kuzmina Alexandrovna
     Alex Fedorov Nikolaevich
     */
    vector<Student*>* expelledStudents = hseDeanery->expelStudents(studentsToBeExpelled);
    cout << "Students expelled: " << endl;
    for (Student* student : *expelledStudents) {
        cout << student->getFullName() << endl;
    }
    /*
     Students expelled:
     Polina Korolyova Sergeevna
     Anastasia Kuzmina Alexandrovna
     Alex Fedorov Nikolaevich
     */
    hseDeanery->printPerformanceData();
    /*
     <= Performance data =>
     Group '23CST1':
     Specialization: Computer science
     Head: Sergei Kuznetsov Dmitrievich
     Average mark: 6.88889
     Number of students: 9
      Student Vladislav Petrov Vasilievich: average mark is 10, marks: 10
      Student Olga Smirnova Ivanovna: average mark is 7, marks: 7
      Student Petya Petrov Vasilievich: average mark is 5, marks: 5
      Student Artem Ivanov Sergeevich: average mark is 7, marks: 7
      Student Sergei Kuznetsov Dmitrievich: average mark is 8, marks: 8
      Student Maria Popova Alexandrovna: average mark is 4, marks: 4
      Student Pavel Morozov Viktorovich: average mark is 9, marks: 9
      Student Ekaterina Volkova Petrovna: average mark is 7, marks: 7
      Student Dmitri Kozlov Ivanovich: average mark is 5, marks: 5
     Group '23MATH1':
     Specialization: Math
     Head: Maxim Antonov Ivanovich
     Average mark: 6.33333
     Number of students: 6
      Student Anna Yakovleva Sergeevna: average mark is 7, marks: 8 6
      Student Natalia Nikitina Vladimirovna: average mark is 6, marks: 5 7
      Student Andrey Ilyin Sergeevich: average mark is 6, marks: 10 2
      Student Alyona Orlova Viktorovna: average mark is 6, marks: 4 8
      Student Maxim Antonov Ivanovich: average mark is 6.5, marks: 7 6
      Student Tatiana Gavrilova Petrovna: average mark is 6.5, marks: 9 4
     Group '23MBBE':
     Specialization: Economics
     Head: Yulia Tarasova Sergeevna
     Average mark: 6.9
     Number of students: 5
      Student Vladimir Golubev Viktorovich: average mark is 7, marks: 6 8
      Student Yulia Tarasova Sergeevna: average mark is 7.5, marks: 8 7
      Student Stanislav Sokolov Nikolaevich: average mark is 7, marks: 5 9
      Student Fedor Egorov Vladimirovich: average mark is 6, marks: 4 8
      Student Mikhail Zaytsev Ivanovich: average mark is 7, marks: 9 5
     */

    hseDeanery->placeMarksToAllAtRandom(cst1);
    hseDeanery->printPerformanceData();
    /*
     <= Performance data =>
     Group '23CST1':
     Specialization: Computer science
     Head: Maria Popova Alexandrovna
     Average mark: 7.5
     Number of students: 9
      Student Vladislav Petrov Vasilievich: average mark is 8.5, marks: 10 7
      Student Olga Smirnova Ivanovna: average mark is 8, marks: 7 9
      Student Petya Petrov Vasilievich: average mark is 7.5, marks: 5 10
      Student Artem Ivanov Sergeevich: average mark is 7.5, marks: 7 8
      Student Sergei Kuznetsov Dmitrievich: average mark is 7.5, marks: 8 7
      Student Maria Popova Alexandrovna: average mark is 6, marks: 4 8
      Student Pavel Morozov Viktorovich: average mark is 9.5, marks: 9 10
      Student Ekaterina Volkova Petrovna: average mark is 7, marks: 7 7
      Student Dmitri Kozlov Ivanovich: average mark is 6, marks: 5 7
     ...
     */

    vector<Student*> studentsToBeTransferred;
    studentsToBeTransferred.push_back(yulia); // from mbbe1
    studentsToBeTransferred.push_back(mikhail); // from mbbe1
    studentsToBeTransferred.push_back(olga); // from cst1
    studentsToBeTransferred.push_back(anna); // from math
    hseDeanery->transferToGroup(studentsToBeTransferred, cst1);
    hseDeanery->printPerformanceData();
    /*
     * <= Performance data =>
    Group '23CST1':
    Specialization: Computer science
    Head: Ekaterina Volkova Petrovna
    Average mark: 7.16667
    Number of students: 12
     Student Vladislav Petrov Vasilievich: average mark is 9, marks: 10 8
     Student Olga Smirnova Ivanovna: average mark is 6.5, marks: 7 6
     Student Petya Petrov Vasilievich: average mark is 6.5, marks: 5 8
     Student Artem Ivanov Sergeevich: average mark is 7, marks: 7 7
     Student Sergei Kuznetsov Dmitrievich: average mark is 7.5, marks: 8 7
     Student Maria Popova Alexandrovna: average mark is 5.5, marks: 4 7
     Student Pavel Morozov Viktorovich: average mark is 8, marks: 9 7
     Student Ekaterina Volkova Petrovna: average mark is 7, marks: 7 7
     Student Dmitri Kozlov Ivanovich: average mark is 7.5, marks: 5 10
     Student Yulia Tarasova Sergeevna: average mark is 7.5, marks: 8 7
     Student Mikhail Zaytsev Ivanovich: average mark is 7, marks: 9 5
     Student Anna Yakovleva Sergeevna: average mark is 7, marks: 8 6
    Group '23MATH1':
    Specialization: Math
    Head: Andrey Ilyin Sergeevich
    Average mark: 6.2
    Number of students: 5
     Student Natalia Nikitina Vladimirovna: average mark is 6, marks: 5 7
     Student Andrey Ilyin Sergeevich: average mark is 6, marks: 10 2
     Student Alyona Orlova Viktorovna: average mark is 6, marks: 4 8
     Student Maxim Antonov Ivanovich: average mark is 6.5, marks: 7 6
     Student Tatiana Gavrilova Petrovna: average mark is 6.5, marks: 9 4
    Group '23MBBE':
    Specialization: Economics
    Head: Vladimir Golubev Viktorovich
    Average mark: 6.66667
    Number of students: 3
     Student Vladimir Golubev Viktorovich: average mark is 7, marks: 6 8
     Student Stanislav Sokolov Nikolaevich: average mark is 7, marks: 5 9
     Student Fedor Egorov Vladimirovich: average mark is 6, marks: 4 8
     */

    hseDeanery->saveDataToFile();
}

void deaneryLoadMethod() {
    Deanery* hseDeanery = new Deanery();
    hseDeanery->loadDataFromFile();
    hseDeanery->printPerformanceData();
}
