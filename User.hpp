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
    double balance;
public:
    User(std::string name, std::string publicKey, double balance) : name(name), publicKey(publicKey), balance(balance) {}

    std::string getName() {
        return name;
    }

    std::string getPublicKey() {
        return publicKey;
    }

    double getBalance() {
        return balance;
    }

};


#endif //BLOCKCHAIN_USER_HPP
