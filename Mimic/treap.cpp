//
//  treap.cpp
//  Project2
//
//  Created by Andy Tsang on 2017-06-10.
//  Copyright © 2017 Andy Tsang. All rights reserved.
//

#include <stdio.h>
#include <cassert>
#include <vector>
#include "treap.h"

int Treap::find(const std::string &key){                //find function that calls insert function findNode 
    std::string keyCopy = key;
    return findNode(root, keyCopy);
    
}

void Treap::insert(const std::string& key, int value){   //insert function that calls helper function insertNode
    std::string keyCopy = key;
    insertNode(root,keyCopy,value);
    
    
}

int Treap::findNode(TreapNode* &root, std::string & key){
    if (root == NULL){                               //if given root is null return -1
        return -1;
    }
    
    if (root->key == key){
        return root->value;                           //if the current value is equal to key return that value
    }
    if (root->key < key ){                           //if smaller than key then search left side
        return findNode(root->right, key);
    }
    
    if (root->key > key){                            //if larger than key search right side
        return findNode(root->left, key);
    
    }
  return -1;                                       // if unable to find key then return -1
    
}

void Treap::insertNode(TreapNode* &root, std::string &key, int &value){
    if (root == NULL){
        root = createNode(key, value);         //if the root is null then make the root the newNode
        return;
    }
    
    if (root->key == key){
        root->value = value;
        return;                                //if there is already a node with that key replace its value with the new value
    }
    
    if (key < root->key){
        insertNode(root->left, key, value);             //insert left subtree
        if (root->left->priority <= root->priority){     // fix heap property if violated
            rotateRight(root);
        }
    }
    
    else{
        insertNode(root->right, key, value);             //insert right subtree
        
        if (root->right->priority <= root->priority){     //fix heap property if violated
            rotateLeft(root);
        }
        
    }
    
}

//taken from lab8 with some modifications
void Treap::rotateLeft(TreapNode* &node){   // rotate left
    assert(node != NULL);
    assert(node->right != NULL);
    TreapNode * temp = node->right;       //temp = to right node of parent
    node->right = temp->left;            //make the right node of parent to be the left node of the right node of parent
    temp->left = node;                  //make the left of the right node of the parent to be the parent node
    node = temp;                       //make the parent node equal to the right node of the parent
    
}

//taken from lab8 with some modifications
void Treap::rotateRight(TreapNode* &node){   //rotate right
    assert(node != NULL);
    assert(node->left != NULL);
    TreapNode * temp = node->left;      //temp = to left node of parent
    node->left = temp->right;          //make the left node to be the right node of the left node of parent
    temp->right = node;               //make the right of the left node of the parent to be the parent node
    node = temp;                     //make the parent node equal to the left node of the parent
}

TreapNode* Treap::createNode(std::string key, int value){ // create a new treapNode with random priority, key, value, and left/right = NULL
    TreapNode* newNode = new TreapNode;
    newNode->priority = rand();
    newNode->key = key;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}








