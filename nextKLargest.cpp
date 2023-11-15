#include "BST.h"
#include <iostream>
#include <vector>
using namespace std;

// helper function
// sort the BST in in-order traversal
vector<int> sort_bst(Node *root) {
    // recursive on the root->left, create a left vector, add that vector at the beginning of bst
    vector<int> bst;
    if (root->left != nullptr) {
        vector<int> left = sort_bst(root->left);
        bst.insert(bst.begin(), left.begin(), left.end());
    }

    // push back root->key
    bst.push_back(root->key);
    
    // recursive on the root->right, create a right vector, add that vector from the end of bst
    if (root->right != nullptr) {
        vector<int> right = sort_bst(root->right);
        bst.insert(bst.end(), right.begin(), right.end());
    }
    return bst;
}

/* return the next kth largest key after x. 
return the largest key in the tree if k is larger than the number of keys larger than x.
note that x needs not be a key in the tree. */
int BST::nextKLargest(int x, int k) {
    // sort the BST in in-order traversal
    vector<int> bst = sort_bst(root);

    // if x is < 1st element
    if (x < bst.at(0)) {
        // if k > size of the array
        if (k > bst.size()) {
            return bst.at(bst.size() - 1);
        }
        else {
            return bst.at(k-1);
        }
    }

    // find the index of x in bst
    int index_x;
    bool found = false;
    for(int i = 0; i < bst.size() - 1; i++) {
        if (bst.at(i) == x) {
            index_x = i;
            found = true;
        }
    }

    // if x is not in bst
    if (found == false) {
        for (int i = 0; i < bst.size() - 2; i++) {
            if ((x > bst.at(i)) && (x < bst.at(i + 1))) {
                index_x = i;
            }
        }
    }

    // return the last element if k is larger than the number of keys larger than x
    int index_last = bst.size() - 1;
    int num_keys = index_last - index_x;
    if (k > num_keys) {
        return bst.at(index_last);
    }
    else {
        int index_k = index_x + k;
        return bst.at(index_k);
    }

    return 0;
}