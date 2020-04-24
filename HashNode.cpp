/*
Oliver Rochester
This is the hashnode file that implements all of hashnodes methods and the uses of recursion
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include "HashNode.h"
#include "DRT.h"
using namespace std;

/*
hashnode constructor
*/
HashNode::HashNode(string key, string data) {

	k = key; d = data; next = NULL;
}

/*
hashnode deconstructor
*/
HashNode::~HashNode() { //destructor

	delete next;
}

/*
hashnode search method, uses recursion to find data based on key given
*/
DRT* HashNode::searchnode(string key) {

	if (k == key) return new DRT(d, "", "");
	if (!next) return new DRT("", "", "");
	return next->searchnode(key);
}

/*
hash node add method uses recursion to find correct spot to add a new hashnode
*/
DRT* HashNode::addnode(string key, string data) {
	if (this->k == key) {
		this->d = data;
		return new DRT(data, "", "");
	}
	if (this->next == NULL) {
		this->next = new HashNode(key, data);
		return new DRT(data, "", "");
	}
	else {
		return this->next->addnode(key, data);
	}
}

//get key method
string HashNode::getk() { return k; }
//get data method
string HashNode::getd() { return d; }

/*
hasnode remove method, takes in list head pointer, if node to be removed is listhead
and if there is a next, listhead node gets deleted and list head points to next in the list.
if node to be deleted is not the list head, it makes use  of the p hashnode that is passed in to be able to 
point nodes around other nodes. Uses recursion to find correct node to delete.
*/
DRT* HashNode::remove(string key, HashNode* p, HashNode*& listhead) {
	if (listhead->k == key) {
		if (listhead->next) {
			HashNode* temp = listhead;
			listhead = listhead->next;
			delete temp;
		}
		else {
			HashNode* temp = listhead;
			listhead = NULL;
			delete temp;
			
		}
		return new DRT("", "", "");
	}
	else if (this->k == key) {
		p->next = this->next;
		delete this;
		return new DRT("", "", "");
	}
	else {
		p = this;
		return this->remove(key, p, listhead);
	}
}

//set next method
void HashNode::setnext(HashNode* p) { next = p; }

