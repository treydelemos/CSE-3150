#include "logger.h"
#include <string>
#include <iostream>

// ======================= TODOs =======================

void addReading(const std::string& label, double value,
                std::string labels[], double values[],
                int& size, int capacity) {
    if (size == capacity) {
        throw std::string("Full");
    } else {
        labels[size] = label;
        values[size] = value;
        size++;
    }
}

void updateValue(double* valuePtr, double newValue) {
    if (valuePtr != nullptr) {
        *valuePtr = newValue;
    }
}

void printReading(const std::string& label, const double& value) {
    std::cout << label << ": " << value << std::endl;
}

double average(const double values[], int size) {
    if (size == 0) {
        throw std::string("Empty");
    }
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += values[i];
    }
    return sum / size;
}

double minValue(const double values[], int size) {
    if (size == 0) {
        throw std::string("Empty");
    }
    double minVal = values[0];
    for (int i = 1; i < size; ++i) {
        if (values[i] < minVal) {
            minVal = values[i];
        }
    }
    return minVal;
}

double maxValue(const double values[], int size) {
    if (size == 0) {
        throw std::string("Empty");
    }
    double maxVal = values[0];
    for (int i = 1; i < size; ++i) {
        if (values[i] > maxVal) {
            maxVal = values[i];
        }
    }
    return maxVal;
}
