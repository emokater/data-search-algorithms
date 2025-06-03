/// \file  flower.cpp
/// \brief Implementation of the Flower class methods and operator overloading.

#include "../headers/flower.h"

/// \brief Primary constructor of the Flower class.
Flower::Flower(string name, string color, string smell, vector<string> regions) {
    name_ = name;
    color_ = color;
    smell_ = smell;
    regions_ = regions;
}

bool Flower::EqFlowers(const Flower& other) const {
    if (name_ == other.name_) {
        return true;
    }
    return false;
}

/// \brief "Greater than" operator based on key fields.
bool Flower::operator>(const Flower& other) const {
    if (name_ != other.name_) {
        return name_ > other.name_;
    }
    return false;
}

/// \brief "Less than" operator based on key fields.
bool Flower::operator<(const Flower& other) const {
    if (name_ != other.name_) {
        return name_ < other.name_;
    }
    return false;
}

/// \brief "Greater than or equal to" operator based on key fields.
bool Flower::operator>=(const Flower& other) const {
    if (EqFlowers(other) || (*this > other)) {
        return true;
    }
    return false;
}

/// \brief "Less than or equal to" operator based on key fields.
bool Flower::operator<=(const Flower& other) const {
    if (EqFlowers(other) || (*this < other)) {
        return true;
    }
    return false;
}

bool Flower::operator==(const Flower& other) const {
    return EqFlowers(other);
}

/// \brief Copy assignment operator.
Flower& Flower::operator=(const Flower& other) {
    name_ = other.name_;
    color_ = other.color_;
    smell_ = other.smell_;
    regions_ = other.regions_;

    return *this;
}