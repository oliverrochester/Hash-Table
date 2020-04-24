/*
Oliver Rochester
This is the DRT file, this gives us the layout for how to return a data
*/
#include <string>
#include "DRT.h"
using namespace std;

//DRT constructor
DRT::DRT(string d, string n, string p) {

    data = d; next = n; prev = p;
}

string DRT::getdata() { return data; }

string DRT::getnext() { return next; }

string DRT::getprev() { return prev; }