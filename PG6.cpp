/*
Oliver Rochester
This file is the main file of the program. It implements the loop for entering commands,
processing the commands, add items to the database, removing them andlooking them up
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include "HashTable.h"
#include "DRT.h"
#include "PG6.h"
using namespace std;

//main method that creates a hash table with the appropriate size
//runs a for loop and calls to process the commands
int main(int argc, char** argv) {
    Studs = new HashTable(100003);
	while (ProcessCommand());
    delete Studs;
	return 0;
}

//method to distinguish if your adding , removing , or looking up data in database
bool ProcessCommand() {
    string cmd; 
    getline(cin, cmd);
    if (cmd == "EXIT") return false;
    else if (cmd.substr(0, 3) == "ADD") AddCommand(cmd);
    else if (cmd.substr(0, 6) == "REMOVE") RemoveCommand(cmd);
    else if (cmd.substr(0, 6) == "LOOKUP") LookupCommand(cmd);
    else cout << "Invalid Command!" << endl;
    return true;
}

void Print() {

}

void RPrint() {

}

/*
add method, does a search of database on given data,
depending on data returned from search, it adds correct data accordingly
*/
void AddCommand(string cmd) {
    int q1, q2;
    for (q1 = 0; cmd[q1] != '\"'; q1++);
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
    string k = cmd.substr(q1 + 1, q2 - q1 - 1);
    cout << k << endl;
    DRT* T = Studs->search(k);

    if (T->getdata() == "") {
        delete T;
        T = Studs->modify(k, "1");
    }
    else {
        string d = to_string(stoi(T->getdata()) + 1);
        delete T;
        T = Studs->modify(k, d);
    }
    cout << "1 copy of \"" << k << "\" has been added to the library." << endl;
    delete T;
}

/*
remove method, does a search of database on given data,
depending on data returned from search, it adds/removes correct data accordingly
*/
void RemoveCommand(string cmd) {
    int q1, q2;
    for (q1 = 0; cmd[q1] != '\"'; q1++);
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
    string k = cmd.substr(q1 + 1, q2 - q1 - 1);
    DRT* T = Studs->search(k);
    if (T->getdata() == "")
        cout << "\"" << k << "\" does not exist in the library." << endl;
    else {
        if (T->getdata() == "1") {
            delete T;
            T = Studs->modify(k, "");
        }
        else {
            string d = to_string(stoi(T->getdata()) - 1);
            delete T;
            T = Studs->modify(k, d);
        }
        cout << "1 copy of \"" << k << "\" has been removed from the library." << endl;
        delete T;
    }
}

/*
lookup method, does a search of database on given data,
depending on data returned from search, it outputs correct data accordingly
*/
void LookupCommand(string cmd) {
    int q1, q2;
    for (q1 = 0; cmd[q1] != '\"'; q1++);
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
    string k = cmd.substr(q1 + 1, q2 - q1 - 1);
    DRT* T = Studs->search(k);
    if (T->getdata() == "") {
        cout << "\"" << k << "\" does not exist in the library." << endl;
    }
    else {
        cout << k << " has " << T->getdata() << " copies in the database" << endl;
    }
}
