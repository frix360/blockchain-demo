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
    int difficultyTarget = 4;
    std::vector<Transaction> data;

    bool isHashVectorValid(std::string generatedHash) {
        if (! generatedHash.empty() && difficultyTarget <= 0) {
            return true;
        }

        auto startIterator = begin(generatedHash);
        auto endIterator = begin(generatedHash) + difficultyTarget;

        int concurrentZeros = 0;
        for (auto it = startIterator; it != endIterator; ++it) {
            if (*it == '0') {
                concurrentZeros++;
            }
        }


        return concurrentZeros == difficultyTarget;
    }

    void generateMerkelRootHash() {
        std::vector<std::string> hashes;
        hashes.reserve(data.size());

        for (auto transaction : data) {
            hashes.push_back(sha256(transaction.toString()));

        }

        if (hashes.empty()) {
            return;
        }
        else if(hashes.size() == 1) {
           merkelRootHash = hashes[0];
        }

        while (hashes.size() > 1) {
            if (hashes.size() % 2 != 0) {
                hashes.push_back(hashes.back());
            }

            assert(hashes.size() % 2 == 0);

            std::vector<std::string> merkle;

            for (auto it = hashes.begin(); it != hashes.end(); it += 2) {
                std::string combinedHash = *it + *(it+1);
                merkle.push_back(sha256(combinedHash));
            }

            hashes = merkle;
        }

        merkelRootHash = hashes[0];
    }


public:
    Block(std::string previousHash, std::vector<Transaction> data, bool shouldGenerateHash = false)
            : previousHash(std::move(previousHash)), data(std::move(data)) {

        timestamp = time_in_HH_MM_SS_MMM();
        generateMerkelRootHash();
        if (shouldGenerateHash) {
            bool hashGenerated = false;
            hash = generateHash(hashGenerated);
        } else {
            hash = "";
        }


    }

    std::string generateHash( bool &hashValid, int maxTries = 100000) {
        int counter = 0;
        std::string generatedHash;
        std::string strToHash = timestamp + std::to_string(version) + std::to_string(nonce) + merkelRootHash;

           //generatedHash = stringToHash(strToHash);
           generatedHash = sha256(strToHash);
           // picosha2::hash256_hex_string(stringToHash, generatedHash);

        while ( counter < maxTries) {
            hashValid = isHashVectorValid(generatedHash);
            if (hashValid) {
                hash = generatedHash;
                break;
            }

            nonce++;
            counter++;
            strToHash = timestamp + std::to_string(version) + std::to_string(nonce) + merkelRootHash;
            generatedHash = sha256(strToHash);
            // generatedHash = stringToHash(strToHash);
        }


        return generatedHash;
    }

    std::string getHash() const {
        return hash;
    }

    std::string getPreviousHash() {
        return previousHash;
    }
    void setPreviousHash(std::string hash) {
        previousHash = std::move(hash);
    }

    std::vector<Transaction> getTransactions() {
        return data;
    }
};


#endif //BLOCKCHAIN_BLOCK_HPP
