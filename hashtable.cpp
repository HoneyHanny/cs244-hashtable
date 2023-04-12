#include <cstdlib>
#include <iostream>
#include "hashtable.h"

int HashTable::hashfn(int key) {
	return compress(hash_code(key));
}
