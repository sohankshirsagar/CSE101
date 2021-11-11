#include <iostream>
#include <fstream>
#include "avl.h"
#include <sstream>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
  if (argc < 3) {
    throw std::invalid_argument("Usage: ./treewraooer <INPUT FILE> <OUTPUT FILE>");
  }
  ifstream input;
  ofstream output;

  input.open(argv[1]);
  output.open(argv[2]);

//   string command;
//   char *com, *dummy, *valstr, *op, *op1;
//   string val = "";

  string command;
  string val;
  char *com, *op;

  AVL myAVL;


  while (getline(input, command)) {
    if (command.length() == 0) {
      continue;
    }
    com = strdup(command.c_str());
    op = strtok(com, " \t");
    val = strtok(NULL, " \t");

    if (strcmp(op, "i") == 0) {
      cout << "Insert: " << val << endl;
      myAVL.put(val);
    }

    if (strcmp(op, "r") == 0) {
      string val2 = strtok(NULL, " \t");
      output << myAVL.rangeCount(myAVL.getRoot(), val, val2) << endl;
    }
  }
  // myAVL.countRange(10,20);
  // cout << myAVL.rangeCount(myAVL.getRoot(), 10, 99) << endl;
  // myAVL.print(myAVL.getRoot());
  input.close();
  output.close();
}
