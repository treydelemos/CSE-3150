#include <iostream>
#include "greeting_utils.h"
#include <string>

using std::cout;
using std::endl;
using std::string;


namespace Greeting_Utils {
    string create_message(const std::string& name){
        return "Hello, " + name + "!";
    }

    char* format_as_c_string(const std::string& msg){
        int len = msg.size();
        char* arr = new char[len+1];
        for(int x = 0; x<len; x++){
            arr[x] = msg[x];

        }
        arr[len] = '\0';
        return arr;
    }
    
}
