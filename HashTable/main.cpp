#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename V>
class HashTable {
    static const size_t n_buckets = 1 << (sizeof(char) * 8);
    vector<pair<string, V>> buckets[n_buckets];
    
public:
    V &operator[](const string &k) {
        int bucket = hash(k);
        
        for (auto &i: buckets[bucket])
            if (i.first == k)
                return i.second;
        
        buckets[bucket].emplace_back();
        buckets[bucket].back().first = k;
        return buckets[bucket].back().second;
    }
    
private:
    static int hash(const string &k) {
        char c = '\0';
        for (size_t i = 0; i < k.size(); ++i)
            c ^= k[i];
        return (int) c % n_buckets;
    }
};

int main() {
    HashTable<double> ht;
    
    ht[string("hello")] = 1.1;
    cout << ht[string("hello")] << endl;
}
