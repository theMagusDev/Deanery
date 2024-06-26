// Copyright (C) 2024 Yuriy Magus


#include <utility>

#include "../include/Exception.h"

CustomException::CustomException(const char* message) {
    this->message = std::string(message);
}

const char* CustomException::what() const noexcept {
    return this->message.c_str();
}
