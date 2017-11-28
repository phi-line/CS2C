#include <iostream>
#include "avl_tree.h"

using namespace std;

template <typename Key, typename Value>
void print_avl_tree(typename AVLTree<Key, Value>::Node* node,
                    int depth=0) {
    if (node != nullptr) {
        print_avl_tree<Key, Value>(node->right(), depth + 1);
        for(int j = 0; j < depth; ++j) {
            cout << "  ";
        }
        cout << "{" << node->key() << ", "
        << node->value() << " [" << node->height() << "]}" << endl;
        print_avl_tree<Key, Value>(node->left(), depth + 1);
    }
}

template <typename Key, typename Value>
void print_avl_tree(AVLTree<Key, Value>& t) {
    print_avl_tree<Key, Value>(t.root());
}

int main(const int argc, const char** argv) {
    AVLTree<int, int> avl;
    
    srand(20);
    
    for (int i = 0; i < 25; ++i){
        avl[rand() % 100];
    }
    
    print_avl_tree(avl);
    return 0;
}

