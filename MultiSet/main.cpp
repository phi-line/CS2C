//
//  main.cpp
//  MultiSet
//
//  Created by phi on 10/25/17.
//  Copyright © 2017 phi. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "multiset.h"

using nonstd::MultiSet;
int main(const int argc, char ** argv){
    srand(time(NULL));
    MultiSet<int> test;
    
    const int BIGGEST_NUMBER = 200;
    const int NUM_INSERTIONS = 300;
    int myCounter = 0;
    int toCountFor = rand() % BIGGEST_NUMBER;
    
    
    for(int k = 0; k < NUM_INSERTIONS; k++)
    {
        int temp = rand() % BIGGEST_NUMBER;
        test.insert(temp);
        if(toCountFor == temp)
            myCounter++;
    }
    
    std::cout << "Size: " << test.size() << std::endl;
    std::cout << "Count for: " << toCountFor << std::endl;
    std::cout << "Counted: " << test.count(toCountFor) << std::endl;
    std::cout << "Removed: " << test.remove(toCountFor) << std::endl;
    std::cout << "Removed again: " << test.remove(toCountFor) << std::endl;
    std::cout << "New Size: " << test.size() << std::endl;
    return 0;
}
