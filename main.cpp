#include <random>
#include <iostream>
#include <vector>
#include "User.hpp"
#include "picosha2.h"
#include "Transaction.hpp"
#include "Blockchain.hpp"
#include "functions.hpp"
#include "BlockCandidate.h"
#include <ctime>
#include <cmath>
#include <algorithm>

std::vector<User> generateUsers(unsigned int count = 1000);



std::vector<Transaction> generateTransactions(std::vector<User>& users, int count = 10000);

bool validateTransaction(Transaction transactionToValidate, std::vector<Transaction> transactions);

int main() {
    srand(time(nullptr));

    auto users = generateUsers();

    auto transactions = generateTransactions(users);

    std::shuffle(transactions.begin(), transactions.end(), std::mt19937(std::random_device()()));

    std::vector<Transaction> transactionsToAddToTheBlock;

    Blockchain blockchain;

    int index = 0;
    std::vector<BlockCandidate> blockCandidates;

    for (auto transaction : transactions) {

        if (index >= 5) {
            break;
        }

        if (! validateTransaction(transaction, transactionsToAddToTheBlock)) {
            continue;
        }

        transactionsToAddToTheBlock.push_back(transaction);

        if (transactionsToAddToTheBlock.size() == 100) {
            blockCandidates.emplace_back(transactionsToAddToTheBlock);
            transactionsToAddToTheBlock.clear();
            index++;
        }
    }

    std::shuffle( blockCandidates.begin(), blockCandidates.end(), std::mt19937(std::random_device()()));

    bool hashFound = false;
    int maxTries = 10000;
    Block *validBlock = nullptr;
    std::string latestBlockHash = ! blockchain.getBlocks().empty() ? blockchain.getLatestBlock().getHash() : "";
    while(!hashFound) {
        for (const auto &blockCandidate : blockCandidates) {
            Block* block = new Block(latestBlockHash, blockCandidate.getTransactions(), false);
            block->generateHash(hashFound, maxTries);
            if (hashFound) {
                validBlock = block;
                break;
            }
            else {
                delete block;
            }
        }
        maxTries *= 2;
    }

    blockchain.addBlock(*validBlock);


    return 0;
}

bool validateTransaction(Transaction transactionToValidate, std::vector<Transaction> transactions) {
   double balance = transactionToValidate.getSender()->getStartingBalance();

    for (auto transaction : transactions) {
        if (transaction.getSender()->getPublicKey() == transactionToValidate.getSender()->getPublicKey()) {
            balance -= transaction.getAmount();
        }
        else if(transaction.getReceiver()->getPublicKey() == transactionToValidate.getSender()->getPublicKey()) {
            balance += transaction.getAmount();
        }
    }

    return balance >= transactionToValidate.getAmount();
}

std::vector<Transaction> generateTransactions(std::vector<User>& users, int count) {
    std::vector<Transaction> transactions;
    transactions.reserve(count);

    for (int i = 0; i < count; i++) {
        User* sender = &users[rand() % users.size()];
        User* receiver = &users[rand() % users.size()];
        double amount = rand() % 1000;

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
        users.emplace_back("Vartotojas no " + std::to_string(i), hash, 10000);
    }

    return users;
}
