#include <iostream>
#include "parser.h"
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace StringUtils {
    void parseName(const std::string& fullName, std::string* firstName,std::string* lastName){
        size_t space_pos = fullName.find(' ');
        if (space_pos == string::npos){
        cout << "Please re-enter first and last name" << endl;
        return;
        }
        *firstName = fullName.substr(0, space_pos);
        *lastName = fullName.substr(space_pos+1);
    
    }
    std::string getUsername(const std::string& email){
        size_t atsymbol = email.find('@');
        if (atsymbol != std::string::npos) {
            return email.substr(0, atsymbol);
        }
        return "";
    }
}

