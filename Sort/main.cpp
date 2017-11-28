//
//  main.cpp
//  Sort
//
//  Created by phi on 11/27/17.
//  Copyright © 2017 phi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "sort.h"

using namespace std;

int RandomNumber () { return (std::rand()%100); }

int main(int argc, const char * argv[]) {
    const int NUM_ITEMS = 1000;
    
    vector<int> a( NUM_ITEMS );
    std::generate (a.begin(), a.end(), RandomNumber);
    
    cout << "Unsorted: ";
    for (auto i = a.begin(); i != a.end(); ++i)
        std::cout << *i << ' ';
    std::cout << "\n \n \n";
    
    nonstd::sort(a);
    
    cout << "Sorted: ";
    for (auto i = a.begin(); i != a.end(); ++i)
        std::cout << *i << ' ';
    
    return 0;
}
