#include <utility>
#include "sha256.h"

//
// Created by Ignas on 10/17/2019.
//

#ifndef BLOCKCHAIN_BLOCK_HPP
#define BLOCKCHAIN_BLOCK_HPP


#include <string>
#include <ctime>
#include "Transaction.hpp"
#include <vector>
#include "picosha2.h"
#include "functions.hpp"
#include <sstream>

class Block {
private:
    std::string hash;
    std::string previousHash;
    std::string timestamp;
    int version = 1;
    std::string merkelRootHash;
    long long nonce = 0;
    int difficultyTarget = 2;
    std::vector<Transaction> data;

    bool isHashVectorValid(std::string hash) {
        if (hash.length() > 0 && difficultyTarget <= 0) {
            return true;
        }

        auto startIterator = begin(hash);
        auto endIterator = begin(hash) + difficultyTarget;

        int concurrentZeros = 0;
        for (auto it = startIterator; it != endIterator; ++it) {
            if (*it == '0') {
                concurrentZeros++;
            }
        }


        return concurrentZeros == difficultyTarget;
    }

    void generateMerkelRootHash() {
        std::string stringToHash;
        for (auto transaction : data) {
            stringToHash += transaction.toString();
        }
        merkelRootHash = sha256(stringToHash);
    }


public:
    Block(std::string previousHash, std::vector<Transaction> data)
            : previousHash(previousHash), data(data) {

        timestamp = time_in_HH_MM_SS_MMM();
        generateMerkelRootHash();
        hash = generateHash();

    }

    std::string generateHash() {
        std::string generatedHash;
        std::string strToHash = timestamp + std::to_string(version) + std::to_string(nonce) + merkelRootHash;

           generatedHash = stringToHash(strToHash);
          // generatedHash = sha256(strToHash);
           // picosha2::hash256_hex_string(stringToHash, generatedHash);

        while (! isHashVectorValid(generatedHash)) {
            nonce++;
            strToHash = timestamp + std::to_string(version) + std::to_string(nonce) + merkelRootHash;
            //generatedHash = sha256(strToHash);
            generatedHash = stringToHash(strToHash);
        }


        return generatedHash;
    }

    std::string getHash() {
        return hash;
    }

    std::string getPreviousHash() {
        return previousHash;
    }

    std::vector<Transaction> getTransactions() {
        return data;
    }
};


#endif //BLOCKCHAIN_BLOCK_HPP
