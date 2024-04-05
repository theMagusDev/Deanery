cmake_minimum_required(VERSION 3.26)
project(Deanery)

set(CMAKE_CXX_STANDARD 17)

add_executable(Deanery
        src/main.cpp
        src/Student.cpp
        include/Student.h
        src/Group.cpp
        include/Group.h
        src/Deanery.cpp
        include/Deanery.h
        src/Utilities.cpp
        include/Utilities.h
        include/Exception.h
        src/Exception.cpp)
