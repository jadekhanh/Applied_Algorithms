#include <vector>
#include "bfilter.h"
#include <string>
using namespace std;

/*
    References:

    I took the DJB hash function from the website given in the problem:

    http://www.partow.net/programming/hashfunctions/index.html#AvailableHashFunctions


*/

// DJB hash function:
class DJB : public HashFun {
    unsigned int operator()(const std::string& key) {
        unsigned int hash = 5381;
        unsigned int i = 0;
        for (unsigned int i = 0; i < key.size(); i++) {
            hash = ((hash << 5) + hash) + key[i];
        }
        return hash;
    }
};

void BloomFilter::add_hash_funs() {
    DJB *h1 = new DJB();
    this->hash_funs.push_back(h1);
}

void BloomFilter::insert(const std::string& key) {
    // Here's how you can call your hash functions that you added in add_hash_funs()
    // unsigned int first_hash_result = this->call_hash(0, key);
    // std::cout << "Hash of '" << key << "' is '" << first_hash_result << "' using the first hash function." << std::endl;
    // unsigned int second_hash_result = this->call_hash(1, key);
    // std::cout << "Hash of '" << key << "' is '" << second_hash_result << "' using the second hash function." << std::endl;

    // You'll need to use the results of the hash function to update this->filter
    // Here's an example
    // (this->filter)[first_hash_result % 330] = 1;

    for (int i = 0; i < hash_funs.size(); i++) {
        (this->filter)[this->call_hash(i, key) % 330] = 1;
    }
}

bool BloomFilter::member(const std::string& key) {
    // This function should report true if key is potentially in the bloom filter.
    // It should only return false if you know for sure that key is not in the bloom filter.

    for (int i = 0; i < hash_funs.size(); i++) {
        if ((this->filter)[this->call_hash(i, key) % 330] == 1) {
            return true;
        }
        else {
            return false;
        }
    }
}