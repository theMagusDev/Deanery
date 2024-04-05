#include <utility>

#include "../include/Exception.h"

CustomException::CustomException(std::string message) {
    this->message = std::move(message);
}

std::string CustomException::getMessage() const {
    return this->message;
}
