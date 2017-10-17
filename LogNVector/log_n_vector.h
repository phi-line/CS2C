#ifndef log_n_vector_h
#define log_n_vector_h

#include <cmath>
#include <memory>
#include <vector>

template <typename T>
class LogNVector {
    std::vector<std::unique_ptr<T[]> > arrays_;
    int size_, capacity_;
public:
    LogNVector() {
        size_ = 0;
        capacity_ = 0;
    }
    LogNVector(const LogNVector& other) : LogNVector() {
        for(T data : other.arrays_)
            push_back(data);
    }
    LogNVector(std::initializer_list<T> ilist) : LogNVector() {
        for(T data : ilist)
            push_back(data);
    }
    ~LogNVector() {
        // TODO
    }
    
    int size() const noexcept {
        return size_;
    }
    int capacity() const noexcept {
        return capacity_;
    }
    void push_back(const T& value) {
        if(size_ == capacity_)
            this->createNextArray();
        int vectorIndex = arrays_.size() == 0 ? 0 : getVectorIndex();
        int arrayIndex = size_ - sll(vectorIndex) + 1;
        arrays_[vectorIndex][arrayIndex] = value;
        size_ += 1;
    }
    
    const T& operator[](int index) const {
        int vectorIndex = log2(++index);
        int arrayIndex = index - sll(vectorIndex);
        return arrays_[vectorIndex][arrayIndex];
        
    }
    T& operator[](int index) {
        int vectorIndex = log2(++index);
        int arrayIndex = index - sll(vectorIndex);
        return arrays_[vectorIndex][arrayIndex];
    }
    
private:
    void createNextArray() {
        int newCapacity = sll(arrays_.size());
        this->arrays_.emplace_back(new T[newCapacity]);
        capacity_ = sll(arrays_.size()) - 1;
    }
    
    int getVectorIndex() const {
        return arrays_.size() - 1;
    }
    
    int sll(int num) const {
        return 1 << num;
    }
};

#endif /* log_n_vector_h */
