/// \file hash.h
/// \brief Defines a hash table for storing Flower objects using separate chaining for collision resolution.
/// 
/// Provides:
/// - hashFunc_rs: A string-based hash function (RS algorithm).
/// - Item: A node in the linked list used for collision resolution.
/// - HashTable: A hash table that stores vectors of Flower objects under string keys.

#ifndef HASH_H
#define HASH_H

#include <string>
#include <vector>
#include <iostream>
#include "flower.h"

/// \brief Size of the hash table
#define SIZE 14
using namespace std;

/**
 * \brief Compute a hash value for a string using the RS (Robert Sedgwicks) algorithm.
 *
 * The function iterates over each character in the key, updating the hash with a multiplier
 * and accumulating the result. Finally, the value is taken modulo SIZE to obtain a hash-table index.
 *
 * \param key The input string to hash.
 * \return    An unsigned int in the range [0, SIZE-1], representing the hash-table index.
 */
unsigned int hashFunc_rs(string key) {
    unsigned int a = 63689;
    unsigned int b = 378551;
    unsigned int hash = 0;
    unsigned int i = 0;

    int len = key.length();

    for (i = 0; i < len; ++i) {
        hash = hash * a + (unsigned char)key[i];
        a = a * b;
    }

    return (hash % SIZE);
}

/**
 * \class Item
 * \brief Represents an item (node) in the linked list for a hash table slot.
 *
 * Each item stores:
 * - key_: The string key that hashes to this slot.
 * - values_: A pointer to a vector of Flower objects associated with this key.
 * - next_:  Pointer to the next item in the same slot’s linked list (for chaining).
 */
class Item {
public:
    string key_;                ///< The string key for this item.
    vector<Flower> *values_;    ///< Pointer to a vector of Flower objects with this key.
    Item *next_;                ///< Pointer to the next Item in the chain (collision list).

public:
    /// \defgroup constructors
    /// \{
    Item() {
        key_ = "";
        values_ = new vector<Flower>();
        next_ = nullptr;
    }

    Item(const string& key, const Flower& value) {
        key_ = key;
        values_ = new vector<Flower>();
        values_->push_back(value);
        next_ = nullptr;
    } 
    /// \}
};

/**
 * \class HashTable
 * \brief Implements a hash table using separate chaining to store Flower objects by their string names.
 *
 * The table uses:
 * - hashFunc_rs to map string keys to hash table slot indices.
 * - An array of pointers to Item (linked-list heads) of size SIZE.
 * - A collision counter to track how many chaining operations occurred.
 *
 * \note The Flower class must provide a method GetName() returning a string key.
 */
class HashTable {
public:
    /**
     * \brief Construct a hash table and insert a vector of Flower objects into it.
     *
     * For each Flower in data:
     * 1. Compute its key via GetName(), and hash to an index.
     * 2. If the bucket is empty, create a new Item.
     * 3. If the bucket already has items, traverse the chain:
     *    - If an existing Item has the same key, append the Flower to its vector.
     *    - Otherwise, add a new Item at the end of the chain and increment collisions.
     *
     * \param data A vector of Flower objects to insert into the hash table.
     */
    HashTable(const vector<Flower>& data) {
        NullTable();

        count = data.size();

        for (size_t i = 0; i < count; ++i) {
            string key = data[i].GetName();
            Flower value = data[i];
            unsigned int hash = hashFunc_rs(key);

            if (!items_[hash]) {
                items_[hash] = new Item(key, value);
                unq_count += 1;
            } else {
                Item *where = items_[hash];
                int is_collis = 1;

                while (true) {
                    if (key == where->key_) {
                        where->values_->push_back(value);
                        is_collis = 0;
                        break;
                    } else {
                        if (where->next_) {
                            where = where->next_;
                        } else {
                            break;
                        }
                    }
                }

                if (is_collis) {
                    collisions += 1;
                    unq_count += 1;
                    where->next_ = new Item(key, value);
                }
            }
        }
    }

    /// \brief Destructor. Frees memory for all Items and their vectors.
    ~HashTable() {
        for (int i = 0; i < SIZE; ++i) {
            SupportDelete(items_[i]);
        }
    }

    /**
     * \brief Search for all Flower objects associated with a given key.
     *
     * \param key The string key to search for.
     * \return    Pointer to a vector of Flower objects if the key is found;
     *            nullptr if the key does not exist in the table.
     */
    vector<Flower>* Search(const string& key) const {
        vector<Flower> *res = nullptr;

        unsigned int hash = hashFunc_rs(key);
        Item *cur = items_[hash];
        while(cur) {
            if (cur->key_ == key) {
                res = cur->values_;
                break;
            }
            cur = cur->next_;
        }

        return res;
    }

    long long GetCount() { return count; }
    long long GetCountUnq() { return unq_count; }
    long long GetCollisions() { return collisions; }
    Item** GetItems() { return items_; }

    /// @brief Print the contents of the hash table to stdout.
    void GetTable() {
        for (int i = 0; i < SIZE; ++i) {
            Item *cur = items_[i];

            cout << i << "   \t";
            if (!cur) {
                cout << "-" << endl;
            } else {
                while (cur) {
                    cout << cur->key_ << "(" << cur->values_->size() << ")" << "   \t";
                    cur = cur->next_;
                }
                cout << endl;
            }
        }
        
        cout << endl << "Count: " << count << endl << "Collisions: " << collisions;
    }

private:
    Item *items_[SIZE];         ///< Array of bucket heads (linked-list pointers).
    long long count;            ///< Total number of Flower objects inserted.
    long long unq_count = 0;    ///< number of unique keys
    long long collisions = 0;   ///< Number of collisions detected during insertion.

private:
    /// @brief   Initializes all buckets to nullptr.
    void NullTable() {
        for (int i = 0; i < SIZE; ++i) {
            items_[i] = nullptr;
        }
    }
    
    /// @brief Recursively deletes a linked list of Items starting from `cur`.
    void SupportDelete(Item *cur) {
        while (cur) {
            Item *next_node = cur->next_;
            delete cur->values_;
            delete cur;
            cur = next_node;
        }
    }
};

#endif