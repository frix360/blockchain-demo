//
// Created by Ignas on 11/10/2019.
//

#ifndef BLOCKCHAIN_BLOCKCANDIDATE_H
#define BLOCKCHAIN_BLOCKCANDIDATE_H


#include <vector>
#include "Transaction.hpp"

class BlockCandidate {
private:
    std::vector<Transaction> transactions;
public:
    BlockCandidate(std::vector<Transaction> transactions) : transactions(transactions){}
    std::vector<Transaction> getTransactions() const {
        return transactions;
    }
};


#endif //BLOCKCHAIN_BLOCKCANDIDATE_H
