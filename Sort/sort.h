#pragma once

#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

namespace nonstd {
    template <typename Comparable>
    bool is_sorted(vector<Comparable>& a) {
        int n = a.size();
        if (n == 1 || n == 0)
            return true;
        
        for (int i = 1; i < a.size(); i++)
            if (a[i - 1] > a[i])
                return false;
        
        return true;
    }
    
    template <typename Comparable>
    bool is_reverse_sorted(vector<Comparable>& a) {
        int n = a.size();
        if (n == 1 || n == 0)
            return true;
        
        for (int i = 1; i < a.size(); i++)
            if (a[i - 1] < a[i])
                return false;
        
        return true;
    }
    
    template <typename Comparable>
    void percolate( vector<Comparable>& a, int i, int n ) {
        int child;
        Comparable tmp = std::move( a[i] );
        
        for(; 2*i + 1 < n; i = child ) {
            child = 2*i + 1;
            if( child != n - 1 && a[child] < a[child + 1] )
                ++child;
            if( tmp < a[child] )
                a[i] = std::move( a[child] );
            else
                break;
        }
        a[i] = std::move( tmp );
    }
    
    template <typename Comparable>
    void heapSort( vector<Comparable>& a ) {
        for( int i = a.size() / 2 - 1; i >= 0; --i )
            percolate<Comparable>( a, i, a.size() );
        for( int j = a.size() - 1; j > 0; --j ) {
            std::swap( a[0], a[j] );
            percolate<Comparable>( a, 0, j );
        }
    }
    
    template <typename Comparable>
    void sort( vector<Comparable>& a) {
        if (is_sorted(a))
            return;
        else if (is_reverse_sorted(a))
            std::reverse(a.begin(), a.end());
        else
            heapSort(a);
    }
} // namespace nonstd
