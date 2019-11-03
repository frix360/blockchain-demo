//
// Created by Ignas on 10/17/2019.
//

#ifndef BLOCKCHAIN_TRANSACTION_HPP
#define BLOCKCHAIN_TRANSACTION_HPP


#include <string>
#include "User.hpp"

class Transaction {
private:
    User* sender;
    User* receiver;
    double amount;

public:
    Transaction(User& sender, User& receiver, double amount): sender(&sender), receiver(&receiver), amount(amount){}

    std::string toString() {
        return sender->getPublicKey() + receiver->getPublicKey() + std::to_string(amount);
    }

    User* getSender() {
        return sender;
    }

    User* getReceiver() {
        return receiver;
    }
    double getAmount() {
        return amount;
    }
};


#endif //BLOCKCHAIN_TRANSACTION_HPP
