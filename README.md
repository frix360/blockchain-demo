
# blockchan-demo

## Task description
Description of this task is located [here](https://github.com/blockchain-group/Blockchain-technologijos/blob/master/pratybos/2uzduotis-Blockchain.md).
## Install instructions
1. Clone repository ```$ git clone https://github.com/frix360/blockchain-demo.git```
2. cd to ```blockchain-demo``` directory
3. Compile the program using CMakeLists.txt

## What does this program do?
This program is a the basic implementation of a working blockchain, implementing the basic blockchain principles.

#### How it all works:

1. Generate **n** (default 1000) users. Each user has *name*, *public key* and *balance*. All these properties are generated at random.
2. Generate **n** (default 10000) transactions between users. Each transaction consists of *sender*, *receiver* and *amount*
3. Transactions are then randomized and added to the block. The block consists of *hash*, *previous block hash*, *timestamp*, *version*, *merkel root hash*, *nonce*, *difficulty target* and *transactions*. In this example each block holds 100 transactions.

After running the program we will see this output:

```
Sugeneruotas blokas no. 1
Sugeneruotas blokas no. 2
Sugeneruotas blokas no. 3
Sugeneruotas blokas no. 4
Sugeneruotas blokas no. 5
Sugeneruotas blokas no. 6
Sugeneruotas blokas no. 7
Sugeneruotas blokas no. 8
Sugeneruotas blokas no. 9
Sugeneruotas blokas no. 10
```

**NOTE:** *After release v0.2 block generation logic was tweaked according to the task description.*

---
#### How the block is created?

1. Get current timestamp
2. Generate merkel root hash (currently not real merkel root hash)
3. Generate block hash:
--  Attempt to hash all properties of the block using a hashing function. There are 2 hashing functions used in the project: **custom** function, that is not really reliable, and C++ implementation of the **sha256** algorithm (third-party library)
--  If hash does not satisfy difficulty target requirements, increase the nonce.
-- Repeat until hash satisfies difficulty target requirement.
4. Validate the new block. 
5. If block is valid, add created block to the blockchain.

---

## Changelog

[v0.3](https://github.com/frix360/blockchain-demo/releases/tag/v0.3) - (2019-11-30)

**Changed**
- Merkle tree hashing implemented with the correct logic.
---
[v0.2](https://github.com/frix360/blockchain-demo/releases/tag/v0.2) - (2019-11-10)

**Added**
- **Balance checking.**  Instead of storing balance of each user as a property, it is now dynamically calculated from the transactions data. This new balance checking logic is used to **validate** a transaction.
- Transaction hash **validation**.
- Block mining is now simulated according to the task description with the use of the **BlockCandidate** class.

---
[v0.1](https://github.com/frix360/blockchain-demo/releases/tag/v0.1) - (2019-10-19)

**Initial commit**
- Basic Blockchain class implementation 
---
