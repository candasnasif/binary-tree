
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "stdafx.h"
#include <stdlib.h>
#include <fstream>
#include "myfunctions.h"
using namespace std;
class input {
public:
    input();
    std::vector<string> take_inputs(string file_name); /*This function read the txt file and keep in the a vector and return this vector*/
    std::vector<string> take_commands(char* file_name);
};
input::input()
{
}
std::vector<string> input::take_inputs(string parameter)
{
    std::vector<string> inputs;
    char ch;
    string sen;
    int i;
    for (i = 0; i < parameter.size(); i++) {
        ch = parameter[i];
        if (ch == '(' || ch == ')' || ch == ',') {
            inputs.push_back(sen);
            if (ch != ',')
                inputs.push_back(Conversation_char(ch));
            sen = "";
        }
        else if (ch != ',')
            sen = sen + Conversation_char(ch);
    }
    return inputs; /*return the vector*/
}
std::vector<string> take_commands(char* file_name)
{
    ifstream myfile(file_name);
    string line;
    std::vector<string> inputs;
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            inputs.push_back(line);
        }
    }
    return inputs;
}

Format!Style:
C++ online code formatter © 2014 by KrzaQ

Powered by vibe.d, the D language and clang-format