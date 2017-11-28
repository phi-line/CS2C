#pragma once

#include <algorithm>
#include <vector>

using namespace std;

namespace nonstd {
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
    void sort( vector<Comparable>& a ) {
        for( int i = a.size() / 2 - 1; i >= 0; --i )
            percolate<Comparable>( a, i, a.size() );
        for( int j = a.size() - 1; j > 0; --j ) {
            std::swap( a[0], a[j] );
            percolate<Comparable>( a, 0, j );
        }
    }
} // namespace nonstd
