#ifndef AVL_H
#define AVL_H

#include <string>

using namespace std;

class Node {
  public:
    string key;
    int height;
    Node *left, *right;

    Node() {
      key = "";
      height = 0;
      left = NULL;
      right = NULL;
    }

    Node(string val) {
      key = val;
      left = NULL;
      right = NULL;
    }
};

class AVL {
  private:
    Node *root;
    int calculateHeight(Node*);
    bool put(string, Node*, Node*, bool);
    void rebalance(Node*, Node*, bool);
    void print(Node*, int);
    string printInOrder(Node*);
    Node* get(string, Node*);
    void prePrint(Node*);
  public:
    AVL();
    Node* getRoot();
    void put(string);
    void print(Node*);
    string printInOrder();
    Node* get(string);
    int calcSubtree(Node*);
    int calcSubtreeHelper(Node*);
    int rangeCount(Node*, string, string);
    void prePrint();
};

#endif
