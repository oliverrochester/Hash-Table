/*
Oliver Rochester
This is the hash table file, the file that takes orders from the pG6 file, and gives orders
to the hashnode file
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include "HashTable.h"
#include "DRT.h"
#include "HashNode.h"
using namespace std;

/*
has table constructor, it is an array of hashnodes,
initially loops through hashtable and sets all values to null
*/
HashTable::HashTable(int sz) {

    HS = sz;
    table = new HashNode * [HS];
    for (int i = 0; i < HS; i++)
        table[i] = NULL;
}

//hashtable deconstructor
HashTable::~HashTable() {

    for (int i = 0; i < HS; i++)
        delete table[i];
    delete[] table;
}

/*
hash function, based on the key given, it creates and return a number by multiplying, 
adding and modding the values of the chars together to determine where to put the data in the hashtable
*/
int HashTable::hf(string key) {

    int val = 0;
    for (int i = 0; i < key.length(); i++) {
        int ch = key[i];
        if (ch == 0) ch = 256;
        val = (val * 256 + ch) % HS;
    }
    return val;
}

/*
add method, first finds the hash valueb by calling hash function on the key,
if nothing in that array spot exists, immediately creates first node in that list,
if data already exists in that list, calls the hashnode add method on first element 
in that list.
*/
DRT* HashTable::add(string key, string data) { //very similar to sample code
    int hashnum = hf(key);
    if (table[hashnum] == NULL) {
        table[hashnum] = new HashNode(key, data);
        return new DRT(data, "", "");
    }
    else {
        return table[hashnum]->addnode(key, data);
    }
}

/*
searchnode method, finds hash value, then traverses through list to find specific key,
returns empty DRT if if nothing exists, else returns the nodes data
*/
DRT* HashTable::searchnode(string key) { //searches the tree for the given key

    int val = hf(key);
    if (!table[val]) return new DRT("", "", "");
    return table[val]->searchnode(key);
}

/*
hash table remove method, finds hash value of key, then calls hashnode remove
method to find specific key
*/
DRT* HashTable::remove(string key) { //removes an item from the list
    int hashnum = hf(key);
    HashNode* prev = NULL;
    return table[hashnum]->remove(key, prev, table[hashnum]);
   
    
}

/*
hash table search method, if key to search in is empty, returns, empty drt,
otherwise calls the search node method on the key
*/
DRT* HashTable::search(string key) { //Database search method
      //checks to see if we're searching on the empty string, if so builds a DRT with first() and last (), otherwise calls searchnode

    if (key == "") return new DRT("", "", "");
    return searchnode(key);
}

/*
modify method, if it is calls add method to adjust data
calls remove method to delete data
*/
DRT* HashTable::modify(string key, string data) { //Database modify method

    if (key == "") return new DRT("", "", "");
    if (data == "") return remove(key);
    return add(key, data);
}
