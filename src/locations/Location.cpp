#include "Location.h"
Location::Location(string n, string d) {
    name=n;
    description=d;
}

void Location::enter() {
    cout << "You are in " << name << endl;
    cout << description << endl;
}