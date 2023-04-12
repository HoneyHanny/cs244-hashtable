#include <cstdlib>
#include <iostream>

using namespace std;

class HashTable {
	int* table;
	const int N;
	int count;

	// Since our key is an integer, we will use it as its own hashcode
	inline int hash_code(int key) {
		return key;
	}

	// This hash table uses a MAD compression function
	// where a = 59, b = 17, p = 509
	//
	//
	//				[(ai+b) % p] % N
	//
	//
	inline int compress(int code) {
		return ((59 * code + 17) % 509) % N;
	}

	// Using the knowledge that a hash function is composed of two portions
	inline int hashfn(int key) {
		return compress(hash_code(key));
	}

public:
    HashTable(int N) {
		this->N = N;
		table = (int*)malloc(N * sizeof(int));
		count = 0;
		for (int i = 0; i < N; i++)
			table[i] = 0;
    }
   
	// if full or contains return -1
	// else return num of collision
    int insert(int key) {
		if (count == N || search(key) >= 0) // search(key) >= 0 indicates table contains the key
			return -1;
		if (key == 0)
			return -2;

		int cells = 0;
		int i = hashfn(key);
		while (table[i] != 0) {
			cells++;
			i++;
			if (i == N)
				i = 0;
		}
		
		table[i] = key;
		count++;
		return cells;
    }
    
	// if exist non-negative
	// count number of cells it traversed not including the one with the key
	// not empty = cells
	// empty =  -1
    int search(int key) {
		int index = hashfn(key);
		int cells = 0;
		
		for (int i = index; key != table[i]; cells++) {
			i++;
			if (i == N)
				i = 0;
			if (i == index && cells >= N)
				return (-1 * cells) + 1;
		}

		return cells;
    }
   
    // int remove(int key) {
	// 	int cells = search(key);
	// 	if (cells == -1)
	// 		return -1;

	// 	int i = cells + key;
	// 	if (i >= N)
	// 		i %= N;

	// 	int right = i + 1;
	// 	if (right == N)
	// 		right = 0;

	// 	if (table[right] == 0) {
	// 		do {
	// 			table[i--] = 0;
	// 			if (i == -1)
	// 				i = N - 1;
	// 		} while (table[i] == -1);
	// 	} else {
	// 		table[i] = -1;
	// 	}

	// 	count--;
	// 	return cells;
    // }

	// vacant = 0
	// defunct = -1
	// occupied key
    int remove(int key) {
		int cells = search(key);
		if (cells == -1)
			return -1;

		int i = cells + key;
		if (i >= N)
			i = 0;

		int right = i + 1;
		if (right == N)
			right = 0;

		if (table[right] == 0) {
			do {
				table[i--] = 0;
				if (i == -1)
					i = N - 1;
			} while (table[i] == -1);
		} else {
			table[i] = -1;
		}

		count--;
		return cells;
    }

    
    void print() {
		for (int i = 0; i < N; i++) {
			cout << i << "\t";
		}
		cout << "\n";
		for (int i = 0; i < N; i++) {
			if (table[i] == '\0' || table[i] == -1)
				cout << "\t";
			else
				cout << table[i] << "\t";
		}
		cout << "\n";
    }
};
