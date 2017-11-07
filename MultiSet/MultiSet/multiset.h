#pragma once

#include <memory>

namespace nonstd {
    
    template <typename T>
    class MultiSet {
    public:
        class Node {
        private:
            T value_;
            std::shared_ptr<Node> left_, right_;
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
        std::shared_ptr<Node> root_;
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
            int count = 0;
            while (contains(value)) //remove all instances of node
                count += remove(value, root_);
            size_ -= count;
            return count;
        }
        

        int size() { return this->size_; }

        Node *root() { return root_.get(); }
        
        std::shared_ptr<Node> create_node(const T& value) {
            size_++;
            return std::shared_ptr<Node>(new Node(value));
        }
        
    private:
        int remove(const T& t, std::shared_ptr<Node>& l) {
            int count = 0;
            if (l != nullptr) {
                if(t < l->value_) //recurse on left leaf
                    count += remove(t, l->left_);
                else if(t > l->value_)
                    count += remove(t, l->right_);
                else { // found value!
                    if(!l->left_)
                        l = l->right_;
                    else if(!l->right_)
                        l = l->left_;
                    else {
                        std::shared_ptr<Node> min = l->left_;
                        while(min->right_) //recursively find candidate replacement
                            min = min->right_;
                        l->value_ = min->value_; //replace original with candiate
                        remove(min->value_, l->left_); //remove candidate
                    }
                    count += 1;
                }
            }
            return count;
        }
    };

} // namespace nonstd
