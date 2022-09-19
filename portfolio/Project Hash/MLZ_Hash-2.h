#ifndef MLZ_HASH_H_INCLUDED
#define MLZ_HASH_H_INCLUDED

#include<bits/stdc++.h>
using namespace std;

class mlzHash
{
    int bucket;    // No. of buckets

    // Pointer to an array containing buckets
    list<int> *hashTable;
public:
    mlzHash (int V);  // Constructor

    // inserts a key into hash table
    void insertItem(int x);

    // deletes a key from hash table
    void deleteItem(int key);

    // hash function to map values to key
    int hashFunction(int x) {
        return (x % bucket);
    }

    void displayHash();
};

mlzHash::mlzHash(int b)
{
    this->bucket = b;
    hashTable = new list<int>[bucket];
}

void mlzHash::insertItem(int key)
{
    int index = hashFunction(key);
    hashTable[index].push_back(key);
}

void mlzHash::deleteItem(int key)
{
  // get the hash index of key
  int index = hashFunction(key);

  // find the key in (index)th list
  list <int> :: iterator i;
  for (i = hashTable[index].begin();
           i != hashTable[index].end(); i++) {
    if (*i == key)
      break;
  }

  // if key is found in hash table, remove it
  if (i != hashTable[index].end())
    hashTable[index].erase(i);
}

// function to display hash table
void mlzHash::displayHash() {
  for (int i = 0; i < bucket; i++) {
    cout << i;
    for (auto x : hashTable[i])
      cout << " --> " << x;
    cout << endl;
  }
}


#endif // MLZ_HASH_H_INCLUDED
