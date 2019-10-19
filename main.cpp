#include <random>

#include <iostream>
#include <vector>
#include "User.hpp"
#include "picosha2.h"
#include "Transaction.hpp"
#include "Blockchain.hpp"
#include "functions.hpp"
#include <ctime>
#include <cmath>
#include <algorithm>

std::vector<User> generateUsers(unsigned int count = 1000);



std::vector<Transaction> generateTransactions(std::vector<User>& users, int count = 10000);

int main() {
    srand(time(nullptr));

    auto users = generateUsers();

    auto transactions = generateTransactions(users);

    std::shuffle(transactions.begin(), transactions.end(), std::mt19937(std::random_device()()));

    std::vector<Transaction> transactionsToAddToTheBlock;

    Blockchain blockchain;

    int index = 0;
    for (auto transaction : transactions) {
        transactionsToAddToTheBlock.push_back(transaction);

        if (transactionsToAddToTheBlock.size() == 100) {
            blockchain.createBlock(transactionsToAddToTheBlock);
            std::cout << "Sugeneruotas blokas no. " << ++index  << std::endl;
            transactionsToAddToTheBlock.clear();
        }
    }

    return 0;
}

std::vector<Transaction> generateTransactions(std::vector<User>& users, int count) {
    std::vector<Transaction> transactions;
    transactions.reserve(count);

    for (int i = 0; i < count; i++) {
        User* sender = &users[rand() % users.size()];
        User* receiver = &users[rand() % users.size()];
        double amount = rand() % (int) std::floor(sender->getBalance());

        auto transaction = Transaction(*sender, *receiver, amount);

        transactions.emplace_back(transaction);
    }

    return transactions;
}

std::vector<User> generateUsers(unsigned int count) {
    std::vector<User> users;

    users.reserve(count);
    for (int i = 0; i < count; i++) {
        std::string hash;
        picosha2::hash256_hex_string(std::to_string(i), hash);
        users.emplace_back("Vartotojas no " + std::to_string(i), hash, rand() % 100000);
    }

    return  users;
}
