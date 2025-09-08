#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

void printGreeting(string name) {
    string msg = "hello " + name + "!";
    int len = msg.size();
    string stars(len+4, '*');
    string edge = "*" + string(len+2, ' ') + "*";
    string middle = "* " + msg + " *";
    cout << stars << endl
    << edge << endl <<
    middle << endl <<
    edge << endl <<
    stars << endl;

    }

int main()  {
    cout << "enter name: ";
    string name;
    cin >> name;
    printGreeting(name);
    return 0;
    }
