#ifndef STRINGUTILS
#define STRINGUTILS
#include <string>

namespace StringUtils {
    
    void parseName(const std::string& fullName, std::string* firstName, std::string* lastName);
    
    std::string getUsername(const std::string& email);
}

#endif