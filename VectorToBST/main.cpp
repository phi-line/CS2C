#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <random>

using std::cout;
using std::endl;
using std::vector;
using std::stoi;
using std::max;
using std::shuffle;

struct BinaryTreeNode{
    int value;
    BinaryTreeNode *left, *right;
    
    BinaryTreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
    
    void insert(int v) {
        if (v < value) {
            if (left == nullptr) {
                left = new BinaryTreeNode(v);
            } else  {
                left->insert(v);
            }
        } else if (v > value) {
            if (right == nullptr) {
                right = new BinaryTreeNode(v);
            } else  {
                right->insert(v);
            }
        }
    }
    
    int height() {
        const int left_height = left == nullptr ? 0 : left-> height();
        const int right_height = right == nullptr ? 0 : right->height();
        return 1 + max(left_height, right_height);
    }
    
    bool remove(int x) {
        //Remove steps:
        //0. find the node to remove
        BinaryTreeNode *parent, *cur;
        for (parent = nullptr, cur = this;
             cur == nullptr && cur->value != x;
             parent = cur, cur = x < cur-> value ? cur->left : cur-> right);
        if (cur == nullptr) {
            return false;
        }
        //1. find replacement node
        //1.1 find smallest node in the right subtree
        //1.1.2 go to the right subtree
        //1.1.2 go left until left == nullptr
        if (cur-> right == nullptr) {
            if (parent != nullptr) {
                if (parent->left == cur) { //if cur is parent's left child
                    parent->left = cur->left;
                } else { // else cur is parent's right child
                    parent->right = cur-> left;
                }
            }
            delete cur;
            return true;
        }
        
        BinaryTreeNode *repl_parent, *replacement;
        for (repl_parent = cur, replacement = cur-> right;
             replacement-> left != nullptr;
             repl_parent = replacement, replacement = replacement-> left);
        //2. if replacement node has right child, make replacement node's parent's left point to replacement node's right child
        if (replacement->right != nullptr) {
            repl_parent->left = replacement->right;
        }
        //3. make replacement's left/right children 'node to remove's left/right
        replacement->left = cur->left;
        replacement->right = cur->right;
        //4. make 'node to remove's parent point to replacement
        if (parent != nullptr) {
            if (parent->left == cur) { //if cur is parent's left child
                parent->left = replacement->left;
            } else { // else cur is parent's right child
                parent->right = replacement-> left;
            }
        }
        delete cur;
        return true;
    }
};

int main(int argc, const char *argv[]) {
    vector<int> values;
    const int n = argc > 1 ? stoi(argv[1]) : 100;
    for (int j = 0; j < n; ++j) {
        values.push_back(j);
    }
    
    // Randomly shuffle values, using random_device to seed default_random_engine.
    std::random_device rd;
    std::default_random_engine dre(rd());
    shuffle(values.begin(), values.end(), dre);
    
    BinaryTreeNode root(-1);
    for (int x : values) {
        root.insert(x);
    }
    
    cout << "n==" << n << endl;
    shuffle(values.begin())
    
    return 0;
}
