#pragma once

#include <memory>
#include <stack>

template <typename Key, typename Value=Key>
class AVLTree {
public:
    class Node {
    private:
        Key key_;
        Value value_;
        int height_;
        std::unique_ptr<Node> left_, right_;
        Node(const Key& key) : key_(key), height_(0) {}
        Node(const Key& key, const Value& value) : key_(key), value_(value), height_(0) {}

    public:
        Node *left() {
            return left_.get();
        }
        Node *right() {
            return right_.get();
        }
        const Key& key() const {
            return key_;
        }
        const Value& value() const {
            return value_;
        }
        const int height() const {
            return height_;
        }

        friend class AVLTree<Key, Value>;
    };
private:
    std::unique_ptr<Node> root_;
    int size_;

public:
    AVLTree() : size_(0) {}

    Value& operator[](const Key& key) {
        std::stack<std::unique_ptr<Node>*> parents;
        std::unique_ptr<Node> *cur;
        for (cur = &root_;
             cur->get() != nullptr;
             cur = (key < (*cur)->key_) ? &(*cur)->left_ : &(*cur)->right_) {
            parents.push(cur);
            if (key == (*cur)->key_) {
                return (*cur)->value_;
            }
        }
        
        Node* temp_node = new Node(key);
        cur->reset(temp_node);
        ++size_;
        balance(parents);
        return temp_node->value_;
    }

    int size() {
        return size_;
    }

    Node *root() {
        return root_.get();
    }
private:
    int height(Node* node) const {
        return (node == nullptr) ? -1 : node->height_;
    }

    void recalculate_height(Node* node) {
        node->height_ = std::max(height(node->left()) , height(node->right())) + 1;
    }

    static const int ALLOWED_IMBALANCE = 1;

    void balance(std::stack<std::unique_ptr<Node>*> parents) {
        while(!parents.empty()) {
            std::unique_ptr<Node>* cur = parents.top();
            Node* nodes[3];
            Node* sub_trees[4];
            if(height( cur->get()->left() ) - height( cur->get()->right() ) > ALLOWED_IMBALANCE) {
                if(height( cur->get()->left()->left() ) >= height( cur->get()->left()->right() ))
                    ll_rotation(cur, nodes, sub_trees);
                else
                    lr_rotation(cur, nodes, sub_trees);
            } else if(height( cur->get()->right() ) - height( cur->get()->left() ) > ALLOWED_IMBALANCE) {
                if(height( cur->get()->right()->right() ) >= height( cur->get()->right()->left() ))
                    rr_rotation(cur, nodes, sub_trees);
                else
                    rl_rotation(cur, nodes, sub_trees);
            }

            recalculate_height(cur->get());
            parents.pop();
        }
    }

    void ll_rotation(std::unique_ptr<Node>* cur, Node* (&nodes)[3], Node* (&sub_trees)[4]) {
        sub_trees[0] = cur->get()->left()->left()->left_.release();
        sub_trees[1] = cur->get()->left()->left()->right_.release();
        sub_trees[2] = cur->get()->left()->right_.release();
        sub_trees[3] = cur->get()->right_.release();
        nodes[0] = cur->get()->left()->left_.release();
        nodes[1] = cur->get()->left_.release();
        nodes[2] = cur->release();
        finish_rotation(cur, nodes, sub_trees);
    }

    void lr_rotation(std::unique_ptr<Node>* cur, Node* (&nodes)[3], Node* (&sub_trees)[4]) {
        sub_trees[0] = cur->get()->left()->left_.release();
        sub_trees[1] = cur->get()->left()->right()->left_.release();
        sub_trees[2] = cur->get()->left()->right()->right_.release();
        sub_trees[3] = cur->get()->right_.release();
        nodes[1] = cur->get()->left()->right_.release();
        nodes[0] = cur->get()->left_.release();
        nodes[2] = cur->release();
        finish_rotation(cur, nodes, sub_trees);
    }

    void rl_rotation(std::unique_ptr<Node>* cur, Node* (&nodes)[3], Node* (&sub_trees)[4]) {
        sub_trees[0] = cur->get()->left_.release();
        sub_trees[1] = cur->get()->right()->left()->left_.release();
        sub_trees[2] = cur->get()->right()->left()->right_.release();
        sub_trees[3] = cur->get()->right()->right_.release();
        nodes[1] = cur->get()->right()->left_.release();
        nodes[2] = cur->get()->right_.release();
        nodes[0] = cur->release();
        finish_rotation(cur, nodes, sub_trees);
    }

    void rr_rotation(std::unique_ptr<Node>* cur, Node* (&nodes)[3], Node* (&sub_trees)[4]) {
        sub_trees[0] = cur->get()->left_.release();
        sub_trees[1] = cur->get()->right()->left_.release();
        sub_trees[2] = cur->get()->right()->right()->left_.release();
        sub_trees[3] = cur->get()->right()->right()->right_.release();
        nodes[2] = cur->get()->right()->right_.release();
        nodes[1] = cur->get()->right_.release();
        nodes[0] = cur->release();
        finish_rotation(cur, nodes, sub_trees);
    }

    void finish_rotation(std::unique_ptr<Node>* cur, Node* (&nodes)[3], Node* (&sub_trees)[4]) {
        nodes[0]->left_.reset(sub_trees[0]);
        nodes[0]->right_.reset(sub_trees[1]);
        nodes[2]->left_.reset(sub_trees[2]);
        nodes[2]->right_.reset(sub_trees[3]);
        nodes[1]->left_.reset(nodes[0]);
        nodes[1]->right_.reset(nodes[2]);
        cur->reset(nodes[1]);

        recalculate_height(nodes[0]);
        recalculate_height(nodes[2]);
        recalculate_height(nodes[1]);
    }
};
