#include <iostream>
#include "parser.h"
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(){
    cout << "Enter your full name:";
    string fullName;
    std::getline(cin, fullName);
    
    cout << "Enter your email address:";
    string email;
    std::getline(cin, email);

    string* firstName = new string;
    string* lastName = new string;

    StringUtils::parseName(fullName, firstName, lastName);
    string Username = StringUtils::getUsername(email); 

     cout << "First name: " << *firstName << endl;
    cout << "Last name: " << *lastName << endl;
    cout << "Username: " << Username << endl;

    // Free heap-allocated memory
    delete firstName;
    delete lastName;

    return 0;

}