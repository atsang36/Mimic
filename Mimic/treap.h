#ifndef __TREAP
#define __TREAP
#include <string>
#include <cstdlib>
#include <string>

struct TreapNode {
  std::string key;
  int value;
    int priority;
  TreapNode* left;
  TreapNode* right;
  // you can add a constructor
};

class Treap {
  
  // add more helper functions here
  
 public:
    TreapNode *root;
  Treap() { // constructor
    srand(time(0));
    // your code here
  }
    void rotateLeft(TreapNode* &node);
    void rotateRight(TreapNode* &node);
    int findNode(TreapNode* &root, std::string & key);
    void insertNode(TreapNode* &root, std::string &key, int &value);
    void insert(const std::string& key, int value);
    int find(const std::string& key);
    void printTreeHelper( TreapNode * root, int depth );
    void printTree( TreapNode * root );
    TreapNode* createNode(std::string key, int value);

    
};

#endif
