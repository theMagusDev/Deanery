// Copyright (C) 2024 Yuriy Magus


#include <utility>

#include "../include/Exception.h"

CustomException::CustomException(std::string message) {
    this->message = std::move(message);
}

const char* CustomException::what() const noexcept {
    return this->message.c_str();
}
