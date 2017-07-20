#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "treap.h"
//#include "treap.cpp"


using namespace std;

// Replace all characters except letters (A-Z,a-z) in line with ' ',
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string & line) {
  for( string::iterator it = line.begin(); it != line.end(); ++it ) {
    if( !isalpha(*it) ) {
      if( (*it != '-' && *it != '\'') ||
	  it == line.begin() || it+1 == line.end() ||
	  !isalpha(*(it-1)) || !isalpha(*(it+1)) ) {
	*it = ' ';
      }
    } else {
      *it = tolower(*it);
    }
  }
}

// Helper to print the tree sideways. Taken from lab8
void Treap::printTreeHelper( TreapNode * root, int depth ) {
    if( root == NULL ) return;
    printTreeHelper( root->right, depth + 1 );
    cout << setw( 3 * depth ) << "";	// output 3 * depth spaces
    std::cout << root->key << root->value << std::endl;
    printTreeHelper( root->left, depth + 1 );
}

// Good for debugging.
// Print out the tree sideways. Taken from lab8
void Treap::printTree( TreapNode * root ) {
    printTreeHelper( root, 0 );
}


int main(int argc, char *argv[]) {
    Treap* testTreap = new Treap;
    testTreap->root = NULL;
//    TreapNode* n = testTreap->root = new TreapNode;
//    n->key = "n";
//    n->value = 0;
//    n->priority = 0;
//     TreapNode* c = n->left =  new TreapNode;
//    c->key = "c";
//    c->value = 5;
//    c->priority = 5;
//    TreapNode* p = n->right = new TreapNode;
//    p->key = "p";
//    p->value = 2;
//    p->priority = 2;
//    
//    TreapNode* a = c->left =  new TreapNode;
//    a->key = "a";
//    a->value = 7;
//    a->priority = 7;
//    TreapNode* e = c->right = new TreapNode;
//    e->key = "e";
//    e->value = 9;
//    e->priority = 9;
//
////    testTreap->insert("n",0);
////    testTreap->insert("c",5);
////    testTreap->insert("p",2);
////    testTreap->insert("a",7);
////    testTreap->insert("e",9);
////    testTreap->insert("d",4);
////    TreapNode* rootTest = testTreap->root;
//    cout << "Before Insertion: " << endl;
//    testTreap->printTree(n);
//    testTreap->insert("d", 4);
//    cout << "After Insertion: " << endl;
//    testTreap->printTree(n);
//    

    
  if( argc < 2 || argc > 3 ) {
    cerr << "Usage: " << argv[0] << " n book.txt" << endl;
    exit(1);
  }

  int n = atoi(argv[1]);
  
  ifstream fin;
  fin.open(argv[2]);
  if( !fin.is_open() ) {
    cerr << "Unable to open " << argv[1] << endl;
    exit(2);
  }
    
    vector<string> wordList; // word[r] is the r-th word
    vector<int> all_word_ranks; // ranks of all words in the text
    vector<vector<int> > follower_ranks;
    // follower_ranks[r] is a vector of ranks of followers of word[r]

  string line;
  string word;
  int r = 0;                 //int value that represents the nth new word
int previousValue = 0;       //previous value represents the value of the previous word

  while( !fin.eof() ) {
    getline(fin,line);
    lowercaseWords(line);
    istringstream iss(line, istringstream::in);
    while( iss >> word ) {
//      cout <<word<<endl;
        int value = testTreap->find(word);   //find the word in the treap and return the value of the word, if word isnt present than return -1
        if (value == -1){                   //if word not found insert a new word with value n(the rth new element), and push it into vector wordList
            testTreap->insert(word, r);
            wordList.push_back(word);

            value = r;                    // now make value = r and increment r by one to represent the next new value;
            r++;
        }
        follower_ranks.resize(r);         // resize follower ranks vector by r
        
        if (r-1 > 0){                    // if there are more than 0 elements then add the value to the vector of followers for the previous value
            follower_ranks[previousValue].push_back(value);
        
        }
        previousValue = value;          //update the previous value to be the current value
        
        all_word_ranks.insert(all_word_ranks.end(), value); //insert the value into the all word ranks vector
        
    }
      
  }
    
    long sizeWordList = wordList.size();            //size of the wordList vector
//    long sizeAllWords = all_word_ranks.size();            //size of the all words vector (used only for testing)
//    long sizeFollower = follower_ranks.size();            //size of the followers vector (used  only for testing)
    
    
//    cout << "WordList size: " << sizeWordList << endl;         //tests to see if the vectors contain the correct elements
//    for (int i = 0; i < sizeWordList; i++){
//        cout << wordList[i] << ", ";
//    }
//    cout << "All Words size: " << sizeAllWords << endl;
//    for (int i = 0; i<sizeAllWords; i++){
//        cout << all_word_ranks[i]<< ", ";
//    }
//    cout << "Followers Size: " << sizeFollower << endl;
//    for (int i=0; i< sizeFollower; i++){
//        for (int j = 0; j<= follower_ranks[i].size(); j++){
//            cout << follower_ranks[i][j] << endl;
//        }
//       cout << &follower_ranks[i] << ", ";
//    }
    
    if (n == 0){
        for (int i =0; i < sizeWordList; i++){           //iterate through WordList
            vector<int> subVector = follower_ranks[i];    //subVector is the follower list for the current word
            cout << wordList[i] << " : ";                  //print out the word at i with semi colon
            for (std::vector<int>::const_iterator i = subVector.begin(); i != subVector.end(); ++i){
                cout << wordList[*i] << ' ';
                // print out all the elemnts in the followers list for the current word (code idea taken from stacksoverflow
            }
            cout << " " << endl;
            // placed at the end of each line to to end the current line and start at the next line
        }
        
    }
    else {
        vector<int> A = all_word_ranks;             //vector A set to be vector of all word ranks
        for (int i = 0; i < n; i++){               //repeat n times
            int j = rand() % A.size();             //Choose a random index j into A. (j = rand() % A.size())
            cout << wordList[A[j]] << " ";        //Output word[A[j]].
            if (!follower_ranks[A[j]].empty()){
                A = follower_ranks[A[j]];       //if current word has no follower set A to all word ranks vector 
            }
            else
                A = all_word_ranks;           //Set A to be the vector followers[A[i]]
        }
    }

  fin.close();

  return 0;
}
