//
// Created by Ignas on 10/17/2019.
//

#ifndef BLOCKCHAIN_BLOCKCHAIN_HPP
#define BLOCKCHAIN_BLOCKCHAIN_HPP


#include "Block.hpp"

class Blockchain {
private:
    std::vector<Block> blocks;

public:
    Blockchain() = default;


    std::vector<Block> getBlocks() {
        return blocks;
    }
    Block getLatestBlock() {
        return blocks.back();
    }
    bool isValid() {
        bool hashValid = false;
        for (int i = 1; i < blocks.size(); i++) {
            if (blocks[i].getHash() != blocks[i].generateHash(hashValid, 1) || blocks[i].getPreviousHash() != blocks[i - 1].getHash()) {
                return false;
            }
        }

        return true;
    }
    void addBlock(Block block) {
        if (block.getHash().empty()) {
            std::cout << "Block is not yet mined!";
            return;
        }
        if (blocks.empty()) {
            blocks.push_back(block);
        } else {
            auto latestBlock = getLatestBlock();
            block.setPreviousHash(latestBlock.getHash());
            blocks.push_back(block);
        }
    }
    void createBlock(std::vector<Transaction> transactions, bool shouldGenerateHash) {
        if (blocks.empty()) {
            std::string a = "0";
            Block newBlock = Block(a, transactions, false);
            blocks.emplace_back(newBlock.getPreviousHash(), transactions); // Genesis block
        }
        else {
            if (isValid()) {
                auto latestBlock = getLatestBlock();
                blocks.emplace_back(Block(latestBlock.getHash(), transactions, shouldGenerateHash));
            }
        }
    }

    double getBalance(const User &user) {
        double balance = user.getStartingBalance();
        for (auto block : blocks) {
            for (auto transaction : block.getTransactions()) {
                if (transaction.getSender()->getPublicKey() == user.getPublicKey()) {
                    balance -= transaction.getAmount();
                }
                else if(transaction.getReceiver()->getPublicKey() == user.getPublicKey()) {
                    balance += transaction.getAmount();
                }
            }
        }
        return balance;
    }
};
#endif //BLOCKCHAIN_BLOCKCHAIN_HPP
