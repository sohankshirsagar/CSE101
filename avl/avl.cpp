#include "avl.h"
#include <cmath>
#include <string>
#include <iostream>
#define DEBUG 0

using namespace std;

AVL :: AVL() {
  root = NULL;
}

Node* AVL :: getRoot() {
  return root;
}

int AVL :: calculateHeight(Node* node) {
  int height = 0;
  if (node == NULL) {
    return 0;
  }
  // cout << "Calculating Height for: " << node->key << endl;
  // only left node
  if (node->left == NULL && node->right != NULL) {
    height = node->right->height + 1;
    // only right node
  } else if (node->left != NULL && node->right == NULL) {
    height = node->left->height + 1;
    // have both left and right child
  } else if (node->left != NULL && node->right != NULL) {
    if (node->left->height >= node->right->height) {
      // left is greater height
      height = node->left->height + 1;
    } else{
      // right is greater height
      height = node->right->height + 1;
    }
  }
  return height;
}

void AVL :: put(string key) {
  bool added;
  // tree is empty
  if (root == NULL) {
    Node* newNode = new Node(key);
    root = newNode;
    added = true;
  } else {
    added = put(key, root, NULL, false);
  }
  if (added) {
    // cout << "added " << key << " correctly" << endl;
  }
}

bool AVL :: put(string key, Node* currentNode, Node* parent, bool leftChild) {
  // find where to insert node with binary search
  // height of new node is set to 0
  // height of intermediate node is set to 1 plus the max odf the left/right node heights
  bool result;
  if (key < currentNode->key) {
    if (currentNode->left == NULL) {
      Node* newNode = new Node(key);
      currentNode->left = newNode;
      result = true;
    } else {
      // keep going further on left side of the node
      result = put(key, currentNode->left, currentNode, true);
    }
  } else if (key > currentNode->key) {
    if (currentNode->right == NULL) {
      Node* newNode = new Node(key);
      currentNode->right = newNode;
      result = true;
    } else {
      // keep going further on the right side of the node
      result = put(key, currentNode->right, currentNode, false);
    }
  } else {
    // key was already there
    currentNode->key = key;
    result = false;
    if (DEBUG) cout << "Key already exists " << currentNode->key << endl;
  }

  if (result) {
    currentNode->height = calculateHeight(currentNode);
    if (DEBUG) {
      cout << "Calling rebalance for: " << currentNode->key << " Height: " << currentNode->height << endl;
      cout << "------------------------" << endl;
      print(root);
    }
    rebalance(currentNode, parent, leftChild);
  }
  return result;
}


void AVL :: rebalance(Node* node, Node* parent, bool leftChild) {
  if (node == NULL) {
    return;
  }
  // calc balance
  int leftHeight;
  int rightHeight;
  int balance;
  if (node->left != NULL) {
    leftHeight = node->left->height + 1;
  } else {
    leftHeight = 0;
  }
  if (node->right != NULL) {
    rightHeight = node->right->height + 1;
  } else {
    rightHeight = 0;
  }
  balance = rightHeight - leftHeight;
  // unbalanced
  if (abs(balance) > 1) {
    Node* pivot;
    if (balance > 0) {
      // right heavy
      int left;
      int right;
      if (node->right->left != NULL) {
        left = node->right->left->height + 1;
      } else {
        left = 0;
      }
      if (node->right->right != NULL) {
        right = node->right->right->height + 1;
      } else {
        right = 0;
      }
      if (right > left) {
        // right right heavy
        // rotate left
        if (DEBUG) {
          cout << endl;
          cout << "Right-Right rotating: " << (node->key) << endl << endl;
        }
        pivot = node->right;
        node->right = node->right->left;
        pivot->left = node;
        node = pivot;
        node->left->height = calculateHeight(node->left);
        node->height = calculateHeight(node);
      } else {
        // right left heavy
        // rotate right, rotate left
         if (DEBUG) {
          cout << endl;
          cout << "Right-Left rotating: " << (node->key) << endl << endl;
        }
        pivot = node->right->left;
        node->right->left = node->right->left->right;
        pivot->right = node->right;
        node->right = pivot;
        pivot = node->right;
        node->right = node->right->left;
        pivot->left = node;
        node = pivot;
        if (node->right != NULL) {
          node->right->height = calculateHeight(node->right);
        }
        if (node->left != NULL) {
          node->left->height = calculateHeight(node->left);
        }
        node->height = calculateHeight(node);
      }
    } else {
      // left heavy
      int left;
      int right;
      if (node->left->left != NULL) {
        left = node->left->left->height + 1;
      } else {
        left = 0;
      }
      if (node->left->right != NULL) {
        right = node->left->right->height + 1;
      } else {
        right = 0;
      }
      if (right < left) {
        // left left heavy
        // rotate right
         if (DEBUG) {
          cout << endl;
          cout << "Left-Left rotating: " << (node->key) << endl << endl;
        }
        pivot = node->left;
        node->left = node->left->right;
        pivot->right = node;
        node = pivot;
        node->right->height = calculateHeight(node->right);
        node->height = calculateHeight(node);
      } else {
        // left right heavy
        // rotate left, rotate right
         if (DEBUG) {
          cout << endl;
          cout << "Left-Right rotating: " << (node->key) << endl << endl;
        }
        pivot = node->left->right;
        node->left->right = node->left->right->left;
        pivot->left = node->left;
        node->left = pivot;
        pivot = node->left;
        node->left = node->left->right;
        pivot->right = node;
        node = pivot;
        if (node->left != NULL) {
          node->left->height = calculateHeight(node->left);
        }
        if (node->right != NULL) {
          node->right->height = calculateHeight(node->right);
        }
        node->height = calculateHeight(node);
      }
    }
    if (parent) {
      if (leftChild) {
        parent->left = pivot;
      } else {
        parent->right = pivot;
      }
    } else {
      root = pivot;
    }
  } else {
    // balanced tree
  }
}

// print in tree shape
void AVL :: print(Node* root) {
  print(root, 0);
}

void AVL :: print(Node* node, int depth) {
  // base case
  if (node == NULL) {
    return;
  }
  print(node->right, depth + 1);
  string line = "";
  for (int i = 0; i < depth; i++) {
    line = line + " ";
  }
  line = line + node->key + ", " + to_string(node->height);
  cout << line << endl;
  print(node->left, depth + 1);
}

void AVL :: prePrint() {
  prePrint(root);
  cout << endl;
}

void AVL :: prePrint(Node* currentNode) {
  if (currentNode != NULL) {
    cout << currentNode->key << " ";
    prePrint(currentNode->left);
    prePrint(currentNode->right);
  }
}
 string AVL :: printInOrder() {
  cout << "here: " << endl;
  return printInOrder(root);
}
string AVL :: printInOrder(Node* start) {
  if (start == NULL) {
    return "";
  }
  string leftpart = printInOrder(start->left);
  string rightpart = printInOrder(start->right);
  string output = (start->key);
  if (leftpart.length() != 0) {
    output = leftpart + " " + output;
  }
  if (rightpart.length() != 0) {
    output = output + " " + rightpart;
  }
  return output;
}

Node* AVL :: get(string key) {
  return get(key, root);
}

Node* AVL :: get(string key, Node* currentNode) {
  if (currentNode == NULL) {
    return NULL;
  } else {
    if (key == currentNode->key) {
      return currentNode;
    } else if (key < currentNode->key) {
      return get(key, currentNode->left);
    } else {
      return get(key, currentNode->right);
    }
  }
}

int AVL :: rangeCount(Node* currentNode, string start, string end) {
  if (currentNode == NULL) {
    return 0;
  }

  int leftNum = rangeCount(currentNode->left, start, end);
  int rightNum = rangeCount(currentNode->right, start, end);

  if (currentNode->key >= start && currentNode->key <= end) {
    return leftNum + rightNum + 1;
  } else {
    return leftNum + rightNum;
  }
}
