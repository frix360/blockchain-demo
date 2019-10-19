cmake_minimum_required(VERSION 3.13)
project(Blockchain)

set(CMAKE_CXX_STANDARD 17)

add_executable(Blockchain main.cpp Block.hpp Blockchain.hpp Transaction.hpp picosha2.h User.hpp functions.hpp sha256.h sha256.cpp)