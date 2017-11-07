#pragma once

#include <memory>

namespace nonstd {
    
    template <typename T>
    class MultiSet {
    public:
        class Node {
        private:
            T value_;
            std::unique_ptr<Node> left_, right_;
            Node(const T& value) : value_(value) {}
        public:
            Node *left() {
                return left_.get();
            }
            Node *right() {
                return right_.get();
            }
            const T& value() const {
                return value_;
            }
            
            friend class MultiSet<T>;
        };

    private:
        std::unique_ptr<Node> root_;
        int size_;
        
    public:
        MultiSet() {
            size_ = 0;
        }
        
        MultiSet(std::initializer_list<T> ilist) : MultiSet() {
            for(T data : ilist)
                insert(data);
        }
        
        ~MultiSet() {
            // TODO
        }
        
        void insert(const T& value) {
            if(root_ == nullptr) {
                root_ = create_node(value);
                return;
            }
            
            Node* leaf = root_.get();
            while(true) {
                if(value < leaf->value_) {
                    if(leaf->left_)
                        leaf = leaf->left_.get();
                    else {
                        leaf->left_ = create_node(value);
                        return;
                    }
                }
                else { // default behaviour if value is >= leaf value
                    if(leaf->right_)
                        leaf = leaf->right_.get();
                    else
                    {
                        leaf->right_= create_node(value);
                        return;
                    }
                }
            }
        }

        int count(const T& value) {
            return count_leaf(value, root_.get());
        }

        // helper function that gets count of leaf subtree
        int count_leaf(const T& value, Node* leaf) {
            if(leaf == nullptr)
                return 0;
            
            int counter = (value == leaf->value_) ? 1 : 0;
            Node* direction = (value < leaf->value_) ? leaf->left_.get() : leaf->right_.get();
            return counter + count_leaf(value, direction);
        }

        bool contains(const T& value) {
            Node* leaf = root_.get();
            while(leaf != nullptr) {
                if(value == leaf->value_)
                    return true;
                else if(value < leaf->value_)
                    leaf = leaf->left_.get();
                else
                    leaf = leaf->right_.get();
            }
            return false;
        }
        
        int remove(const T& value) {
            int numRemoved = this->remove_helper(value, root_.get());
            this->size_ -= numRemoved;
            return numRemoved;
        }
        
        int remove_helper(const T& x, Node* p) {
            int numRemoved = 0;
            if(p && x < p->value_)
                numRemoved += remove_helper(x, p->left_.get());
            else if(p && x > p->value_)
                numRemoved += remove_helper(x, p->right_.get());
            else if(p && p->value_ == x) {
                if(!p->left_.get())
                    p = std::move(p->right_.get());
                else if(!p->right_.get()) p = p = std::move(p->left_.get());
                else {
                    Node* q = p->left_.get();
                    while(q->right_.get()) q=q->right_.get();
                    p = std::move(q);
                    remove_helper(x, p->left_.get());
                }
                numRemoved += 1;
            }
            return numRemoved;
        }

        int size() { return this->size_; }

        Node *root() { return root_.get(); }
        
        std::unique_ptr<Node> create_node(const T& value) {
            size_++;
            return std::unique_ptr<Node>(new Node(value));
        }
    };

} // namespace nonstd
