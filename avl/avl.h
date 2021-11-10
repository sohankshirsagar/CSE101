#ifndef AVL_H
#define AVL_H

#include <string>

using namespace std;

class Node {
  public:
    int key;
    int height;
    Node *left, *right;

    Node() {
      key = 0;
      height = 0;
      left = NULL;
      right = NULL;
    }

    Node(int val) {
      key = val;
      left = NULL;
      right = NULL;
    }
};

class AVL {
  private:
    Node *root;
    int calculateHeight(Node*);
    bool put(int, Node*, Node*, bool);
    void rebalance(Node*, Node*, bool);
    void print(Node*, int);
    string printInOrder(Node*);
  public:
    AVL();
    Node* getRoot();
    void put(int);
    void print(Node*);
    string printInOrder();
};

#endif
