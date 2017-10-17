#include <iostream>
#include <vector>
#include <iomanip>
#include <random>

using namespace std;

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
};

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    vector<int> values;
    const int n = argc > 1 ? stoi(argv[1]) : 100;
    for (int j = 0; j < n; ++j) {
        values.push_back(j);
    }
    BinaryTreeNode(123);
    
    random_shuffle(values.begin(), values.end());
    
    BinaryTreeNode evil(n / 2);
    
    for (int x : values) {
        evil.insert(x);
    }
    
    cout << "Height of Tree: " << evil.height();
    
    return 0;
}
