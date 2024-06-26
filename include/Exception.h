// Copyright (C) 2024 Yuriy Magus

#ifndef INCLUDE_EXCEPTION_H_
#define INCLUDE_EXCEPTION_H_

#include <string>
#include <utility>

class CustomException : std::exception {
 public:
    explicit CustomException(const char* message);
    const char* what() const noexcept override;

 private:
    const char* message;
};

class StudentException : public CustomException {
 public:
    explicit StudentException(const char* message) :
        CustomException(message) {}
};
class InvalidNameException : public StudentException {
 public:
    explicit InvalidNameException(const char* message) :
        StudentException(message) {}
};
class InvalidSurnameException : public StudentException {
 public:
    explicit InvalidSurnameException(const char* message) :
        StudentException(message) {}
};
class InvalidPatronymicException : public StudentException {
 public:
    explicit InvalidPatronymicException(const char* message) :
        StudentException(message) {}
};
class InvalidStudentGroupException : public StudentException {
 public:
    explicit InvalidStudentGroupException(const char* message) :
        StudentException(message) {}
};
class InvalidMarkException : public StudentException {
 public:
    explicit InvalidMarkException(const char* message) :
        StudentException(message) {}
};
class InvalidIDException : public StudentException {
 public:
    explicit InvalidIDException(const char* message) :
        StudentException(message) {}
};

class GroupException : public CustomException {
 public:
    explicit GroupException(const char* message) :
        CustomException(message) {}
};
class DuplicatedGroupTitleException : public GroupException {
 public:
    explicit DuplicatedGroupTitleException(const char* message) :
        GroupException(message) {}
};
class NullSpecException : public GroupException {
 public:
    explicit NullSpecException(const char* message) :
        GroupException(message) {}
};

class FileHandlingException : public CustomException {
 public:
    explicit FileHandlingException(const char* message) :
        CustomException(message) {}
};
class FolderCreationException : public FileHandlingException {
 public:
    explicit FolderCreationException(const char* message) :
        FileHandlingException(message) {}
};
class FileOpeningException : public FileHandlingException {
 public:
    explicit FileOpeningException(const char* message) :
        FileHandlingException(message) {}
};


#endif  // INCLUDE_EXCEPTION_H_
