#include <iostream>
#include "greeting_utils.h"
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(){
    cout << "Enter your full name:" << endl;
    string name;
    std::getline(cin, name);

    string greeting = Greeting_Utils::create_message(name);
    char* c_greeting = Greeting_Utils::format_as_c_string(greeting);
    cout << c_greeting << endl;
    delete[] c_greeting;
    return 0;

}