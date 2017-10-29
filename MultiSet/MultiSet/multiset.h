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
                // TODO
            }
            Node *right() {
                // TODO
            }
            const T& value() const {
                //
            }
            
            friend class MultiSet<T>;
        };
        
    private:
        std::unique_ptr<Node> root_;
        int size_;
        
    public:
        MultiSet() {
            // TODO
        }
        
        ~MultiSet() {
            // TODO
        }
        
        void insert(const T& value) {
            // TODO
        }
        
        int count(const T& value) {
            // TODO
        }
        
        bool contains(const T& value) {
            // TODO
        }
        
        int size() {
            // TODO
        }
        
        Node *root() {
            // TODO
        }
    };
    
} // namespace nonstd
