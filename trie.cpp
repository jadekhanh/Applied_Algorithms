#include <string>
#include <iostream>
#include "trie.h"

using namespace std;

/*
    g++ -std=c++11 trie_test.cpp trie.cpp -o now

    References: 
    I use this website to have some inspirations for these functions:
    https://www.techiedelight.com/trie-implementation-insert-search-delete/

*/

/*
Insert (key, val) into the trie. If key is already present, update the corresponding value.
Update map_size and tree_size accordingly. If key is already present, these numbers should not change.
*/
void Trie::insert(string key, int val) {

    TrieNode* current = root;

    // iterate through the nodes
    for (int i = 0; i < key.size(); i++) {

        // create a new node if the path does not exist
        int idx = key[i] - 'a';
        if (current->children[idx] == NULL) {
            current->children[idx] = new TrieNode();   // create a new node with a new letter
            tree_size++;
        }

        // go to the next letter
        current = current->children[idx];
    }

    // if the key has not been inserted into the trie before
    if (current->val == 0) {
        map_size++;
    }

    // if the key is already present, update the corresponding value
    current->val = val;

    return;
}

/*
Search key and return the corresponding value. Return 0 if key is not present in the trie.
*/
int Trie::search(string key) {
    TrieNode* current = root;

    for (int i = 0; i < key.size(); i++) {
        int idx = key[i] - 'a';
        // return 0 if key is not present
        if (current->children[idx] == NULL) {
            return 0;
        }
        // go to the next level
        current = current->children[idx];
    }

    // return the corresponding value if the key is present
    return current->val;
}

/*
Remove key from the trie. Update map_size and tree_size accordingly.
If the node corresponding to the key is a leaf node, you should remove the node.
If the node corresponding to the key is not a leaf node, you should update its value accordingly but should not remove the node.
*/
void Trie::remove(string key) {
    
    // if the key is not in the trie, then nothing to delete
    if (this->search(key) == 0) {
        return;
    }

    else {

        TrieNode* parent = root;
        // travel down to the second to last node
        for (int i = 0; i < key.size() - 1; i++) {
            int idx = key[i] - 'a';
            parent = parent->children[idx];
        }

        TrieNode* current = root;
        int last = key.size() - 1;
        int idx_last = key[last] - 'a';
        current = parent->children[idx_last];
        // update the value of the current node
        current->val = 0;

        // check if current is a leaf node
        bool isleaf = true;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (current->children[i] != NULL) {
                isleaf = false;
                break;
            }
        }

        // if current is a leaf node, remove the node
        if (isleaf == true) {
            parent->children[idx_last] = NULL;
            current = NULL;
            tree_size--;
        }
        
        map_size--;

        return;
    }

}