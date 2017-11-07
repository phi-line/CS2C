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
            
            Node* l = root_.get();
            while(true) {
                if(value < l->value_) {
                    if(l->left_)
                        l = l->left();
                    else {
                        l->left_ = create_node(value);
                        return;
                    }
                }
                else { // default behaviour if value is >= leaf value
                    if(l->right_)
                        l = l->right();
                    else
                    {
                        l->right_= create_node(value);
                        return;
                    }
                }
            }
        }

        int count(const T& value) {
            return count(value, root_.get());
        }

        bool contains(const T& value) {
            Node* l = root_.get();
            while(l != nullptr) {
                if(value == l->value_)
                    return true;
                else if(value < l->value_)
                    l = l->left();
                else
                    l = l->right();
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
        
        int count(const T& value, Node* l) {
            if(l == nullptr)
                return 0;
            
            int counter = (value == l->value_) ? 1 : 0;
            return counter + count(value, l->left()) + count(value, l->right());
        }
    };
}
