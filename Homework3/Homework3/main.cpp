//
//  main.cpp
//  Homework3
//
//  Created by David Lehman on 4/17/19.
//  Copyright © 2019 David Lehman. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

void FIFOAddToList(vector<bool> n, int size){
}

int main() {
    //Declare the two inputs from the files, and read the files into the data
    int plist[10];
    ifstream f("plist.txt");
    ifstream a("ptrace.txt");
    string word;
    int count = 0;
    int temp = 0;
    bool flag = false;
    //Read the plist
    while(f >> word){
        temp = stoi(word);
        if(temp != count){
            plist[count] = temp;
            cout << plist[count] << endl;
            count++;
        }
    }
    
    count = 0;
    //Go through the ptrace for the FIFO
    cout << "Going throug to find how many page faults for FIFO : ";
    int memPlace;
    vector<int> list[10];
    while(a >> word){
        if(flag == false) {
            temp = stoi(word);
            flag = true;
        } else {
            memPlace = stoi(word);
            if (find(list[temp].begin(), list[temp].end(), memPlace) == list[temp].end()) {
                count++;
                list[temp].insert(list[temp].begin(),memPlace);
                if(list[temp].size() >= 4)
                    list[temp].pop_back();
            
            }
            
        }
    }
    
    a.close();
    cout << count << endl;
    
    
    return 0;
}
