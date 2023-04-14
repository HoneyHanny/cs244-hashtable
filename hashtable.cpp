#include "hashtable.h"
#include <cstdio>

using namespace std;

HashTable::HashTable(int N) {
	this->N = N;
	table = (int*)malloc(N * sizeof(int));
	count = 0;
	for (int i = 0; i < N; i++)
		table[i] = EMPTY;
}

// if full or contains return -1
// else return num of collision
int HashTable::insert(int key) {
	if (count == N || search(key) >= 0) // search(key) >= 0 indicates table contains the key
		return -1;
	if (key == EMPTY || key == DEFUNCT)
		return -2;

	int cells = 0;
	int i = hashfn(key);
	while (table[i] != EMPTY && table[i] != DEFUNCT) {
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
int HashTable::search(int key) {
	int index = hashfn(key);
	int cells = 0;

	int i;
	for (i = index; key != table[i] && table[i] != EMPTY; cells++) {
		i++;
		if (i == N)
			i = 0;
		if (i == index && cells >= N)
			return (cells + 1) * -1; // not found
	}

	if (table[i] == EMPTY)
		return (1 + cells) * -1;

	return cells; // found
}

// vacant = 0
// defunct = -1
// occupied key
int HashTable::remove(int key) {
	int cells = search(key);
	if (cells < 0)
		return -1;

	int i = cells + hashfn(key);
	if (i >= N)
		i %= N;

	int right = i + 1;
	if (right == N)
		right = 0;

	if (table[right] == EMPTY) {
		do {
			table[i--] = EMPTY;
			if (i == -1)
				i = N - 1;
		} while (table[i] == DEFUNCT);
	} else {
		table[i] = DEFUNCT;
	}

	count--;
	return cells;
}


void HashTable::print() {
	for (int i = 0; i < N; i++) {
		cout << i << "\t";
	}
	cout << "\n";
	for (int i = 0; i < N; i++) {
		if (table[i] == EMPTY || table[i] == DEFUNCT)
			cout << "\t";
		else
			printf("%c\t", table[i]);
	}
	cout << "\n";
}
