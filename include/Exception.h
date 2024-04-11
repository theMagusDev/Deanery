// Copyright (C) 2024 Yuriy Magus

#ifndef INCLUDE_EXCEPTION_H_
#define INCLUDE_EXCEPTION_H_

#include <string>
#include <utility>

class CustomException : std::exception {
 public:
    explicit CustomException(std::string message);
    std::string getMessage() const;

 private:
    std::string message;
};

class StudentException : public CustomException {
 public:
    explicit StudentException(std::string message) :
        CustomException(std::move(message)) {}
};
class InvalidNameException : public StudentException {
 public:
    explicit InvalidNameException(std::string message) :
        StudentException(std::move(message)) {}
};
class InvalidSurnameException : public StudentException {
 public:
    explicit InvalidSurnameException(std::string message) :
        StudentException(std::move(message)) {}
};
class InvalidPatronymicException : public StudentException {
 public:
    explicit InvalidPatronymicException(std::string message) :
        StudentException(std::move(message)) {}
};
class InvalidStudentGroupException : public StudentException {
 public:
    explicit InvalidStudentGroupException(std::string message) :
        StudentException(std::move(message)) {}
};
class InvalidMarkException : public StudentException {
 public:
    explicit InvalidMarkException(std::string message) :
        StudentException(std::move(message)) {}
};
class InvalidIDException : public StudentException {
 public:
    explicit InvalidIDException(std::string message) :
        StudentException(std::move(message)) {}
};

class GroupException : public CustomException {
 public:
    explicit GroupException(std::string message) :
        CustomException(std::move(message)) {}
};
class DuplicatedGroupTitleException : public GroupException {
 public:
    explicit DuplicatedGroupTitleException(std::string message) :
        GroupException(std::move(message)) {}
};
class NullSpecException : public GroupException {
 public:
    explicit NullSpecException(std::string message) :
        GroupException(std::move(message)) {}
};

class FileHandlingException : public CustomException {
 public:
    explicit FileHandlingException(std::string message) :
        CustomException(std::move(message)) {}
};
class FolderCreationException : public FileHandlingException {
 public:
    explicit FolderCreationException(std::string message) :
        FileHandlingException(std::move(message)) {}
};
class FileOpeningException : public FileHandlingException {
 public:
    explicit FileOpeningException(std::string message) :
        FileHandlingException(std::move(message)) {}
};


#endif  // INCLUDE_EXCEPTION_H_
