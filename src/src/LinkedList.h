
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "stdafx.h"
#include <stdlib.h>
#include <fstream>
#include <stack>
#include "output.h"
using namespace std;
struct Node {
    string data = "candas";
    string type;
    Node* left = NULL;
    Node* right = NULL;
};
void ADDINGCP(Node* element, Node* cur, std::stack<int> parantheses, std::vector<string> inputs)
{
    Node* tara = cur;
    if (tara->data == inputs[parantheses.top() + 1]) {

        if (parantheses.size() % 2 == 0) {
            while (tara) {
                if (tara->right != NULL)
                    tara = tara->right;
                else {
                    tara->right = element;
                    break;
                }
            }
        }
        else {
            while (tara) {
                if (tara->left != NULL)
                    tara = tara->left;
                else {
                    tara->left = element;
                    break;
                }
            }
        }
        return;
    }
    if (tara->left != NULL)
        ADDINGCP(element, tara->left, parantheses, inputs);
    if (tara->right != NULL)
        ADDINGCP(element, tara->right, parantheses, inputs);
}
void ADDING(Node* element, Node* cur, std::stack<int> parantheses, std::vector<string> inputs)
{
    Node* tara = cur;
    if (tara->data == inputs[parantheses.top() - 1]) {

        if (parantheses.size() % 2 == 0) {
            while (tara) {
                if (tara->right != NULL)
                    tara = tara->right;
                else {
                    tara->right = element;
                    break;
                }
            }
        }
        else {
            while (tara) {
                if (tara->left != NULL)
                    tara = tara->left;
                else {
                    tara->left = element;
                    break;
                }
            }
        }
        return;
    }
    if (tara->left != NULL)
        ADDING(element, tara->left, parantheses, inputs);
    if (tara->right != NULL)
        ADDING(element, tara->right, parantheses, inputs);
}
void Print(Node* head, int count, std::ofstream& File)
{
    Node* cur = head;
    int i;
    if (cur) {
        for (i = 0; i < count; i++)
            out(File, " |   ");
        if (1 == 1) {
            if (cur->type == "Directory")
                outend(File, " |---<" + cur->data + ">");
            else
                outend(File, " |--- " + cur->data);
        }
        if (cur->right != NULL) {
            if (cur->type == "Directory")
                Print(cur->right, count + 1, File);
            else
                Print(cur->right, count, File);
        }
        if (cur->left != NULL) {
            if (cur->type == "Directory" && count > 0 && cur->right == NULL)
                Print(cur->left, count + 1, File);
            else
                Print(cur->left, count, File);
        }
    }
}
void PrintD(Node* head, int count, std::ofstream& File)
{
    Node* cur = head;
    int i;
    if (cur) {
        for (i = 0; i < count; i++)
            out(File, " |   ");
        if (1 == 1) {
            if (cur->type == "Directory")
                outend(File, " |---<" + cur->data + ">");
            else
                outend(File, " |--- " + cur->data);
        }
        if (cur->right != NULL) {
            if (cur->type == "Directory" && count == 0)
                PrintD(cur->right, count + 1, File);
            else if (cur->type == "Directory" && cur->left != NULL)
                PrintD(cur->left, count + 1, File);
            else if (cur->type == "Directory")
                PrintD(cur->right, count + 1, File);
            else
                PrintD(cur->right, count, File);
        }
        if (cur->left != NULL) {
            if (cur->type == "Directory" && cur->right == NULL)
                PrintD(cur->left, count + 1, File);
            else
                PrintD(cur->left, count, File);
        }
    }
}
void search(string x, Node* firstNode, std::ofstream& File)
{
    Node* cur = firstNode;
    if (cur->data == x) {
        if (cur->right == NULL) {
            outend(File, "<" + cur->data + ">");
            PrintD(cur->left, 0, File);
        }
        else if (cur->left == NULL) {
            outend(File, "<" + cur->data + ">");
            PrintD(cur->right, 0, File);
        }
        else {
            outend(File, "<" + cur->data + ">");
            PrintD(cur->right, 0, File);
        }
    }
    if (cur->right != NULL)
        search(x, cur->right, File);
    if (cur->left != NULL)
        search(x, cur->left, File);
}
void searchAll(string x, Node* firstNode, Node** last)
{
    Node* cur = firstNode;
    if (cur->data == x) {
        *last = cur;
        return;
    }
    if (cur->right != NULL)
        searchAll(x, cur->right, last);
    if (cur->left != NULL)
        searchAll(x, cur->left, last);
}

