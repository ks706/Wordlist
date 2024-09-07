// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Karman Sidhu>
// St.# : <301456933>
// Email: <kss26@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//
#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//
// IMPORTANT: no global variables are permitted in this file!
//
// It is okay to define helper functions defined outside the class.
//

class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement an AVL tree for the word list. You can *add*
    // extra variables/methods/features to this struct if you like, but you must
    // keep its name the same, and also keep the word, count, left, and right
    // variables as defined.
    //
    struct Node
    {
        string word;
        int count;
        int height;
        Node *left;
        Node *right;
    };

    Node *root = nullptr;

    //
    // IMPORTANT: root is the only variable that can be defined in this class.
    // It should point to the top node of your AVL tree. When root == nullptr,
    // the tree is empty.
    //
    // No variables other than root are permitted!
    //

    public:
    //recursively deletes AVL tree using post order traversal
    void deleteAVL(Node *r)
    {
        if(r == nullptr)
        {
            return;
        }
                
        deleteAVL(r->left);
        deleteAVL(r->right);
        
        delete r;
    }

    //
    //  destructor: de-allocate all memory allocated by the class.
    //
    ~Wordlist() 
    {
        deleteAVL(root);
    }

    //default constructor
    Wordlist()
    {

    }

    //constructor which reads the given file into a wordlist
    //used codes for reading files from https://www.w3schools.com/cpp/cpp_files.asp
    Wordlist(const string &filename)
    {
        string word;

        //open file
        ifstream readFile(filename);

        //reads every word in the file into wordlist
        while (readFile >> word) 
        {
             add_word(word);
        }
    
        //closes file
        readFile.close();
    }

    //does an inorder search to see if w is in tree 
    //sets count if is, does nothing if it isnt
    void treeSearch(Node *p,const string &w,int &count) const
    {
        if (p == nullptr)
        {
            return;
        }

        treeSearch(p->left,w,count);
        
        if(p->word == w)
        {
            count = p->count;
        }
        
        treeSearch(p->right,w,count);
    }

    //
    // Returns the number of times w occurs as a word in the word list.
    //
    int get_count(const string &w) const
    {

        int count = 0;
        treeSearch(root,w,count);

        return count; 
    }

    //
    // Returns true if w is in the word list, false otherwise.
    //
    bool contains(const string &w) const
    {
        if(get_count(w) > 0)
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    //does an inorder traversal to count nodes
    //sets count if is, does nothing if it isnt
    void nodeCount(Node *p, int &count) const
    {
        if (p == nullptr)
        {
            return;
        }

        nodeCount(p->left,count);
        
        if(p != nullptr)
        {
            count++;
        }
            
        nodeCount(p->right,count);
    }

    //
    // Returns the number of nodes in the word list.
    //
    int num_different_words() const
    {
        int count = 0;
        nodeCount(root,count);
        return count;
    }

    //does an inorder traversal to count nodes
    //sets count if is, does nothing if it isnt
    void wordCount(Node *p, int &count) const
    {
        if (p == nullptr)
        {
            return;
        }

        wordCount(p->left,count);
        
        if(p != nullptr)
        {
            count += p->count;
        }
            
        wordCount(p->right,count);
    }

    //
    // Returns the total number of words in the word list, i.e. the sum of the
    // word counts.
    //
    int total_words() const
    {
        int count = 0;
        wordCount(root,count);
        return count;
    }

    //does an inorder traversal to see if tree is in ascending order
    void isAscending(Node *p, bool &sorted, string &w) const
    {
        if (p == nullptr)
        {
            return;
        }

        isAscending(p->left,sorted,w);
        
        if(p->word < w)
        {
            sorted = false;
        }
        
        w = p->word;
        
        isAscending(p->right,sorted,w);
    }

    //
    // Returns true if the words in the word list are in ascending sorted order,
    // false otherwise.
    //
    // For an AVL implementation, this should return true if the AVL tree is a
    // BST, and false otherwise.
    //
    bool is_sorted() const
    {
        bool sorted = true;
        string w = "";
        isAscending(root,sorted,w);
       
        return sorted;
    }

    //does an inorder traversal to count singletons
    //sets count if is, does nothing if it isnt
    void highestCount(Node *p, int &max, string &mostFreq) const
    {
        if (p == nullptr)
        {
            return;
        }

        highestCount(p->left,max,mostFreq);
        
        if(p->count > max)
        {
            max = p->count;
            mostFreq = p->word;
            //converts integer to string
            string maxAsString = to_string(max);
            //concatenates strings toghether
            mostFreq = mostFreq + " " + maxAsString;
        }
            
        highestCount(p->right,max,mostFreq);
    }

    //
    // Returns a string of the most frequent word in the format "word freq".
    // E.g. if the most frequent word is "the" with count 5437, then "the 5437"
    // is returned. 
    //
    // If there is a tie, the first word in the list is returned. For an AVL
    // implementation, this means return the word that occurs first
    // alphabetically.
    //
    // Assumes the list is not empty.
    //
    string most_frequent() const
    {
        int max = 0;
        string freq = "";
        highestCount(root,max,freq);
        
        return freq;
    }

    //does an inorder traversal to count singletons
    //sets count if is, does nothing if it isnt
    void singletonsCount(Node *p, int &count) const
    {
        if (p == nullptr)
        {
            return;
        }

        singletonsCount(p->left,count);
        
        if(p->count == 1)
        {
            count++;
        }
            
        singletonsCount(p->right,count);
    }


    //
    // Returns the number of nodes with count 1.
    //
    int num_singletons() const
    {
        int count = 0;
        singletonsCount(root,count);
        return count;
    }

    // A utility function to get the
    // height of the tree
    //using code from https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
    int height(Node *r)
    {
        if (r == nullptr)
        {
            return 0;
        }
        
        else
        {
            return r->height;
        }
        
    }

    //returns larger of 2 integers
    int max(int x, int y)
    {
        if(x > y)
        {
            return x;
        }

        else
        {
            return y;
        }
    }

    //returns height balance property
    uint heightBalance(Node *r)
    {
        if(r == nullptr)
        {
            return 0;
        }

        else 
        {
            return height(r->left) - height(r->right);
        }

    }

    //using code from https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;
    
        // Perform rotation
        x->right = y;
        y->left = T2;
    
        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;                   
        x->height = max(height(x->left), height(x->right)) + 1;
                        
    
        // Return new root
        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;
    
        // Perform rotation
        y->left = x;
        x->right = T2;
    
        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;                   
        y->height = max(height(y->left), height(y->right)) + 1;
                        
        // Return new root
        return y;
    }
    
    //using code from https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
    Node* insertAVL(Node *r, const string &w)
    {
        if(r == nullptr)
        {
            r = new Node;
            r->word = w;
            r->count = 1;
            r->height = 1;
            r->left = nullptr;
            r->right = nullptr;
            return r;
        }
        
        if(w > r->word)
        {
            r->right = insertAVL(r->right, w);
        }

        else if(w < r->word)
        {
           r->left = insertAVL(r->left, w);
        }

        else if(w == r->word)
        {
            r->count++;
            return r;
        }

        r->height = 1 + max(height(r->left),height(r->right));

        int balance = heightBalance(r);

        // Left Left Case
        if (balance > 1 && w < r->left->word)
        {
            return rightRotate(r);
        }
       
        // Right Right Case
        if (balance < -1 && w > r->right->word)
        {
            return leftRotate(r);
        }
            
 
        // Left Right Case
        if (balance > 1 && w > r->left->word)
        {
            r->left = leftRotate(r->left);
            return rightRotate(r);
        }
 
        // Right Left Case
        if (balance < -1 && w < r->right->word)
        {
            r->right = rightRotate(r->right);
            return leftRotate(r);
        }            

        return r;
    }

    //
    // Adds w to the word list. If w is already in the word list, then increment
    // its count. Otherwise add a new Node (with count 1) at the alphabetically
    // correct location for the word.
    //
    void add_word(const string &w)
    {              
        root = insertAVL(root, w);
    }

    void print_inOrder(Node *p,int &count) const
    {
        if (p == nullptr)
        {
            return;
        }

        print_inOrder(p->left,count);
        cout << count;
        cout << ". {";
        cout << "\"" << p->word << "\"" ;
        cout << ", " << p->count ;
        cout << '}' << endl;
        count++;
        print_inOrder(p->right,count);
    }

    //prints word in ascending order
    void print_words() const
    {
        int count = 1;
        print_inOrder(root,count);
    }


}; // class Wordlist

//
// Make sure to thoroughly test your code as you go!
//
