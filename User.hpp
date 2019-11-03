#include <utility>

//
// Created by Ignas on 10/17/2019.
//

#ifndef BLOCKCHAIN_USER_HPP
#define BLOCKCHAIN_USER_HPP

#include <string>


class User {
private:
    std::string name;
    std::string publicKey;
    double startingBalance;
public:
    User(std::string name, std::string publicKey, double startingBalance) : name(name), publicKey(publicKey), startingBalance(startingBalance) {}

    std::string getName() const {
        return name;
    }

    std::string getPublicKey() const {
        return publicKey;
    }

    double getStartingBalance() const {
        return startingBalance;
    }
};


#endif //BLOCKCHAIN_USER_HPP
