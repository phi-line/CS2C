//
//  main.cpp
//  StacksAndQueues
//
//  Created by phi on 10/4/17.
//  Copyright © 2017 phi. All rights reserved.
//

using namespace std;
#include <iostream>
#include <stack>
#include <queue>

int main ()
{
    queue<int> elevatorQueue;
    cout << "Please enter the floors that you would like to go to (enter 0 to end):\n";
    int floor;
    do {
        cin >> floor;
        if (floor > 0) elevatorQueue.push (floor);
    } while (floor);
    
    stack<string> boxStack;
    cout << "Please enter the shipping numbers of the boxes to deliver (enter done to end)\n";
    string box;
    do {
        cin >> box;
        if (!box.empty() && box != "done") boxStack.push (box);
    } while (box != "done");
    
    while (!elevatorQueue.empty())
    {
        if (!boxStack.empty()) {
            cout << "Delivered box [" << boxStack.top() << "] to floor ";
            boxStack.pop();
        }
        cout << elevatorQueue.front();
        elevatorQueue.pop();
        cout << "\n";
        
    }
    if (!boxStack.empty()) {
        cout << "Box(es) remaining: ";
        while (!boxStack.empty()) {
            cout << "[" << boxStack.top() << "] ";
            boxStack.pop();
        }
    }
    
    cout << '\n';
    
    return 0;
}
