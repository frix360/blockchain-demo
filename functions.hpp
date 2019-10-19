//
// Created by Ignas on 10/18/2019.
//

#ifndef BLOCKCHAIN_FUNCTIONS_HPP
#define BLOCKCHAIN_FUNCTIONS_HPP

#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

int validAsciCodes[]{48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 97, 98, 99, 100, 101, 102, 103, 104, 106, 107, 108};

unsigned long stringToNumberHash(const std::string &str) {
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned long hash = 0;

    for (std::size_t i = 0; i < str.length(); i++) {
        hash = hash * a + str[i];
        a = a * b;
    }
    return hash;
}


int getAsciNumber(int number, int lastNumber) {
    return validAsciCodes[number + lastNumber-1];
}

std::string stringToHash(const std::string &input, int hashSize = 64) {
    unsigned long long intHash = stringToNumberHash(input);

    std::string numbersString = std::to_string(intHash);

    while (numbersString.size() <= hashSize) {
        intHash += (numbersString.size() * intHash);
        numbersString += std::to_string(intHash);
    }

    numbersString = numbersString.substr(0, hashSize); // limit the size of the string

    std::ostringstream oss;

    int lastNumber = 0;

    for (auto number : numbersString) {
        int val = number - '0';
        oss << char(getAsciNumber(val, lastNumber));

        lastNumber = val;
    }

    return oss.str();
}

std::string time_in_HH_MM_SS_MMM()
{
    using namespace std::chrono;

    // get current time
    auto now = system_clock::now();

    // get number of milliseconds for the current second
    // (remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(now);

    // convert to broken time
    std::tm bt = *std::localtime(&timer);

    std::ostringstream oss;

    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

#endif //BLOCKCHAIN_FUNCTIONS_HPP
