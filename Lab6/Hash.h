#ifndef HASH_H
#define HAHS_H

#include <vector>

using std::vector;
using std::pair;

// Jacob Knox CST211 Lab6 Due: 3/2/2023
template <typename K, typename V>
class HashTable {
 private:
  size_t max_size;
  vector<vector<pair<K, V>>> table;

  typedef int (*HashFunction)(const K& key);
  typedef void (*Visitor)(const V& value);

 public:
  HashTable() = default;
  HashTable(const HashTable<K, V>& rhs) = default;
  HashTable(HashTable<K, V>&& rhs) = default;
  HashTable<K, V>& operator=(const HashTable<K, V>& rhs) = default;
  HashTable<K, V>& operator=(HashTable<K, V>&& rhs) = default;
  ~HashTable() = default;
  
  V operator[](const K& key) const;
  V& operator[](const K& key);

  void Add(const K& key, const V& value);
  void Remove(const K& key);

  void setHash(HashFunction hash);

  void Traverse(Vistor v) const;
};
#endif  // HASH_H
