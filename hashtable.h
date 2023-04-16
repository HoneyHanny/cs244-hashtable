#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>

#define _DEBUG
#ifdef _DEBUG
#define DEBUG(x) do { std::cerr << x; } while (0)
#define DEBUGN(x) do { std::cerr << x << std::endl; } while (0)
#else
#define DEBUG(x)
#define DEBUGN(x)
#endif

#define EMPTY ' '
#define DEFUNCT '?'

using namespace std;

class HashTable {
	int* table;
	int N;
	int count;

	// Since our key is an integer, we will use it as its own hashcode
	inline int hash_code(int key) { return key; }

	// This hash table uses the MAD compression function
	// where a = 59, b = 17, p = 509
	//
	//
	//				[(ai+b) % p] % N
	//
	//
	inline int compress(int code) { return ((59 * code + 17) % 509) % N; }

	// Using the knowledge that a hash function is composed of two portions
	inline int hashfn(int key) { return compress(hash_code(key)); }

public:
    HashTable(int N);

    int insert(char  key);
    int search(char  key);
    int remove(char  key);
    void print();

};

#endif // HASHTABLE_H
