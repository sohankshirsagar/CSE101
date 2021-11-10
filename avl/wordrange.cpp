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

  string command;
  char *com, *dummy, *valstr, *op;
  int val = 0;

  AVL myAVL;

  while (getline(input, command)) {
    if (command.length() == 0) {
      continue;
    }
    com = strdup(command.c_str());
    op = strtok(com, " \t");

    valstr = strtok(NULL, " \t");
    if (valstr != NULL) {
      val = strtol(valstr, &dummy, 10);
    }
    // put into list
    if (strcmp(op, "i") == 0) {
      cout << "Put " + to_string(val) << endl;
      myAVL.put(val);
      // myAVL.print(myAVL.getRoot());
    }
  }
  input.close();
  output.close();
}
