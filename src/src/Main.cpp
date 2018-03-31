

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <stack>
#include "myfunctions.h"
#include "input.h"
#include "LinkedList.h"
#include "output.h"

using namespace std;
int main(int argc, char* argv[])
{
    input parameters;
    int i;
    std::string c = string(argv[1]);
    std::stack<int> paranthese;
    std::vector<string> inputs1 = parameters.take_inputs(c);
    std::vector<string> inputs;
    ofstream output;
    output.open("argv[3]", ios::out | ios::trunc);
    for (i = 0; i < inputs1.size(); i++) {
        if (inputs1[i] != "")
            inputs.push_back(inputs1[i]);
    }
    Node* firstNode = new Node;
    firstNode->data = inputs[0];
    firstNode->right = NULL;
    firstNode->left = NULL;
    int j;
    Node* last = new Node;
    for (i = 1; i < inputs.size(); i++) {
        if (inputs[i] == "(")
            paranthese.push(i);
        else if (inputs[i] == ")")
            paranthese.pop();
        else {
            Node* newNode = new Node;
            newNode->data = inputs[i];
            if (inputs[i + 1] == "(")
                newNode->type = "Directory";
            else
                newNode->type = "File";
            newNode->left = NULL;
            newNode->right = NULL;
            ADDING(newNode, firstNode, paranthese, inputs);
        }
    }
    std::vector<string> commands = take_commands(argv[2]);
    std::vector<string> words;
    std::vector<string> url;
    std::vector<string> urld;
    Node* temp = firstNode;
    for (i = 0; i < commands.size(); i++) {
        if (commands[i] != "ls") {
            words = str_split_x(commands[i]);
            if (words[0] == "ls") {
                if (words[1].find("/") == std::string::npos) {
                    temp = firstNode;
                    searchAll(words[1], temp, &temp);
                    if (temp->data == words[1])
                        ;
                    search(words[1], firstNode, output);
                    outend(output, "");
                    outend(output, "--------------------");
                    outend(output, "");
                }
                else {
                    url = str_split(words[1]);
                    temp = firstNode;
                    int control = 0;
                    for (j = 0; j < url.size(); j++) {
                        searchAll(url[j], temp, &temp);
                        if (temp->data != url[j])
                            control = 1;
                    }
                    if (control == 0) {
                        search(url[url.size() - 1], firstNode, output);
                        outend(output, "");
                        outend(output, "--------------------");
                        outend(output, "");
                    }
                }
            }
            else if (words[0] == "cp") {
                url = str_split(words[2]);
                temp = firstNode;
                int control = 0;
                for (j = 0; j < url.size(); j++) {
                    searchAll(url[j], temp, &temp);
                    if (temp->data != url[j])
                        control = 1;
                }
                if (control == 0) {

                    std::stack<int> parantheseCP;
                    Node* source = new Node;
                    if (temp->type == "Directory") {
                        source->data = temp->data;
                        source->type = temp->type;
                        source->right = NULL;
                        source->left = NULL;
                        std::vector<string> targetURL;
                        urld = str_split(words[3]);
                        for (j = 0; j < urld.size(); j++) {
                            targetURL.push_back(urld[j]);
                            targetURL.push_back("(");
                        }
                        temp = firstNode;
                        control = 0;
                        for (j = 0; j < urld.size(); j++) {
                            searchAll(urld[j], temp, &temp);
                            if (temp->data != urld[j])
                                control = 1;
                        }
                        if (control == 0) {
                            for (j = 0; j < targetURL.size(); j++) {
                                if (targetURL[j] == "(")
                                    parantheseCP.push(j);
                            }
                            ADDING(source, firstNode, parantheseCP, targetURL);
                        }
                    }
                    else {
                        source->data = temp->data;
                        source->type = temp->type;
                        source->right = temp->right;
                        source->left = temp->left;
                        std::vector<string> targetURL;
                        urld = str_split(words[3]);
                        for (j = 0; j < urld.size() - 1; j++) {
                            targetURL.push_back(urld[j]);
                            if (j != urld.size() - 2)
                                targetURL.push_back("(");
                        }
                        temp = firstNode;
                        control = 0;
                        for (j = 0; j < urld.size() - 1; j++) {
                            searchAll(urld[j], temp, &temp);
                            if (temp->data != urld[j])
                                control = 1;
                        }
                        if (control == 0) {
                            for (j = 0; j < targetURL.size(); j++) {
                                if (targetURL[j] == "(")
                                    parantheseCP.push(j);
                            }
                            ADDINGCP(source, firstNode, parantheseCP, targetURL);
                        }
                    }
                }
            }
            else if (words[0] == "mv") {
                url = str_split_x(words[1]);
                urld = str_split_x(words[2]);
            }
            else if (words[0] == "mkdir") {
            }
            else if (words[0] == "rm") {
            }
            else if (words[0] == "cd") {
            }
            else if (words[0] == "crtfl") {
            }
        }
        else {
            cout << "<" << firstNode->data << ">" << endl;
            Print(firstNode->left, 0, output);
            outend(output, "");
            outend(output, "--------------------");
            outend(output, "");
        }
    }
    return 0;
}
