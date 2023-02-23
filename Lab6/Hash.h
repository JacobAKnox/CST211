#ifndef HASH_H
#define HASH_H

#include <vector>

using std::hash;

using std::pair;
using std::size_t;
using std::vector;

#include "Exception.h"

// Jacob Knox CST211 Lab6 Due: 3/2/2023
template <typename K, typename V>
class HashTable {
 public:
  typedef size_t (*HashFunction)(const K& key);
  typedef void (*Vistor)(const K& key, const V& value);

 private:
  size_t m_max_size;
  size_t m_size;
  vector<vector<pair<K, V>>> table;
  HashFunction hash;

  void Rehash() {
    // create a new table
    vector<vector<pair<K, V>>> new_table;
    new_table.resize(m_max_size);
    // move all the values to the new table
    for (size_t i = 0; i < m_max_size; ++i) {
      for (pair<K, V>& p : table[i]) {
        size_t pos = hash(p.first) % (m_max_size);
        new_table[pos].push_back(p);
      }
    }
    // set the new table
    table = new_table;
  }

  // calculate the position in the table
  size_t calculate_position(const K& key) const {
    return hash(key) % m_max_size;
  }

  // default hash function is std::hash
  // works for most default types
  static size_t defaultHash(const K& key) {
    return std::hash<K>{}(key);
  }

 public:
  HashTable();                                             // 1/1
  HashTable(HashFunction hash);                            // 1/1
  HashTable(const HashTable<K, V>& rhs);                   // 1/1
  HashTable(HashTable<K, V>&& rhs);                        // 1/1
  HashTable<K, V>& operator=(const HashTable<K, V>& rhs);  // 1/1
  HashTable<K, V>& operator=(HashTable<K, V>&& rhs);       // 1/1
  ~HashTable();                                            // 0/0

  V operator[](const K& key) const;  // 3/3
  V& operator[](const K& key);       // 1/1

  void Add(const K& key, const V& value);  // 1/1
  void Remove(const K& key);               // 2/2

  void setHash(HashFunction hash);  // 1/1

  void Traverse(Vistor v) const;  // 2/2

  // not required
  size_t size() const;
  size_t max_size() const;
  size_t hash_key(const K& key);
  bool contains(const K& key) const;
  HashFunction getHash() const {
    return hash;
  }
};

template <typename K, typename V>
HashTable<K, V>::HashTable() {
  // set defaults
  m_max_size = 10;
  m_size = 0;
  hash = defaultHash;
  table.resize(m_max_size);
}

template <typename K, typename V>
HashTable<K, V>::HashTable(HashFunction hash_func) {
  // set defaults and hash function
  m_max_size = 10;
  m_size = 0;
  hash = hash_func;
  table.resize(m_max_size);
}

template <typename K, typename V>
HashTable<K, V>::HashTable(const HashTable<K, V>& rhs) {
  // copy all values
  m_max_size = rhs.m_max_size;
  m_size = rhs.m_size;
  hash = rhs.hash;
  // std::vector::operator= handles copying the vector
  table = rhs.table;
}

template <typename K, typename V>
HashTable<K, V>::HashTable(HashTable<K, V>&& rhs) {
  // move all values
  m_max_size = rhs.m_max_size;
  m_size = rhs.m_size;
  // std::vector::operator= handles moving the vector
  table = rhs.table;
  // clear the rhs table
  rhs.m_max_size = 0;
  rhs.m_size = 0;
  hash = rhs.hash;
  rhs.table.clear();
}

template <typename K, typename V>
HashTable<K, V>& HashTable<K, V>::operator=(const HashTable<K, V>& rhs) {
  if (this != &rhs) {
    // copy all values
    m_max_size = rhs.m_max_size;
    m_size = rhs.m_size;
    hash = rhs.hash;
    // std::vector::operator= handles copying the vector
    table = rhs.table;
  }
  return *this;
}

template <typename K, typename V>
HashTable<K, V>& HashTable<K, V>::operator=(HashTable<K, V>&& rhs) {
  if (this != &rhs) {
    // move all values
    m_max_size = rhs.m_max_size;
    m_size = rhs.m_size;
    // std::vector::operator= handles moving the vector
    table = rhs.table;
    // clear the rhs table
    rhs.m_max_size = 0;
    rhs.m_size = 0;
    hash = rhs.hash;
    rhs.table.clear();
  }
  return *this;
}

template <typename K, typename V>
HashTable<K, V>::~HashTable() {
  // clear the values
  m_max_size = 0;
  m_size = 0;
  hash = nullptr;
  // std::vector and std::pair handle freeing memory
  table.clear();
}

template <typename K, typename V>
V HashTable<K, V>::operator[](const K& key) const {
  // get the hash of the key
  size_t hash_key = calculate_position(key);
  // get the vector at the hash key
  vector<pair<K, V>>& vec = table[hash_key];
  // loop through the vector
  for (size_t i = 0; i < vec.size(); i++) {
    // if the key matches, return the value
    if (vec[i].first == key) {
      return vec[i].second;
    }
  }
  // if the key is not found, throw an exception
  throw Exception("Key not found");
}

template <typename K, typename V>
V& HashTable<K, V>::operator[](const K& key) {
  // get the hash of the key
  size_t hash_key = calculate_position(key);
  // get the vector at the hash key
  vector<pair<K, V>>& vec = table[hash_key];
  // loop through the vector
  for (size_t i = 0; i < vec.size(); i++) {
    // if the key matches, return the value
    if (vec[i].first == key) {
      return vec[i].second;
    }
  }
  // if the key is not found throw an exception
  throw Exception("Key not found");
}

template <typename K, typename V>
void HashTable<K, V>::Add(const K& key, const V& value) {
  // get the hash of the key
  size_t hash_key = calculate_position(key);
  // get the vector at the hash key
  vector<pair<K, V>> vec = table[hash_key];
  // loop through the vector
  for (size_t i = 0; i < vec.size(); i++) {
    // if the key matches, replace the value
    if (vec[i].first == key) {
      vec[i].second = value;
      return;
    }
  }
  // if the key is not found, add it to the vector
  vec.push_back(pair<K, V>(key, value));
  // set the vector at the hash key
  table[hash_key] = vec;
  // increment the size
  m_size++;

  // check if the table needs to be resized
  if (m_size > m_max_size * 0.75) {
    // resize the table
    m_max_size *= 2;
    Rehash();
  }
}

template <typename K, typename V>
void HashTable<K, V>::Remove(const K& key) {
  // get the hash of the key
  size_t hash_key = calculate_position(key);
  // get the vector at the hash key
  vector<pair<K, V>> vec = table[hash_key];
  // loop through the vector
  for (size_t i = 0; i < vec.size(); i++) {
    // if the key matches, remove the value
    if (vec[i].first == key) {
      vec.erase(vec.begin() + i);
      // set the vector at the hash key
      table[hash_key] = vec;
      // decrement the size
      m_size--;
      return;
    }
  }
  // if the key is not found throw an exception
  throw Exception("Key not found");
}

template <typename K, typename V>
void HashTable<K, V>::setHash(HashFunction hash) {
  // set the hash function
  this->hash = hash;
  // rehash the table
  Rehash();
}

template <typename K, typename V>
void HashTable<K, V>::Traverse(Vistor v) const {
  // loop through the table
  for (size_t i = 0; i < table.size(); i++) {
    // get the vector at the hash key
    vector<pair<K, V>> vec = table[i];
    // loop through the vector
    for (size_t j = 0; j < vec.size(); j++) {
      // call the visitor function
      v(vec[j].first, vec[j].second);
    }
  }
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K& key) const {
  // get the hash of the key
  size_t hash_key = calculate_position(key);
  // get the vector at the hash key
  vector<pair<K, V>> vec = table[hash_key];
  // loop through the vector
  for (size_t i = 0; i < vec.size(); i++) {
    // if the key matches, return true
    if (vec[i].first == key) {
      return true;
    }
  }
  // if the key is not found, return false
  return false;
}

template <typename K, typename V>
size_t HashTable<K, V>::size() const {
  // return the size
  return m_size;
}

template <typename K, typename V>
size_t HashTable<K, V>::max_size() const {
  // return the max size
  return m_max_size;
}

// hash a key with the hash function, meant to be used for testing the hash
template <typename K, typename V>
size_t HashTable<K, V>::hash_key(const K& key) {
  // hash the key
  return hash(key);
}

#endif  // HASH_H
