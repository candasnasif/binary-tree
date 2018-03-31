#ifndef OUTPUT_H_
#define OUTPUT_H_
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "stdafx.h"
#include <stdlib.h>
#include <fstream>
using namespace std;
void out(std::ofstream& dumFile,string x){
	dumFile << x;
}
void outend(std::ofstream& dumFile, string x){
	dumFile << x<<endl;
}
#endif