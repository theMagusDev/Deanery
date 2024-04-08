cmake_minimum_required(VERSION 3.26)
project(Deanery)
project(${PROJECT_NAME})
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(deanery_lib ${SRC_FILES})
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

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
target_link_libraries(Deanery deanery_lib)
