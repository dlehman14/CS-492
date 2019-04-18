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
using namespace std;

int main() {
    //Declare the two inputs from the files, and read the files into the data
    int plist[10];
    
    ifstream f("plist.txt");
    ifstream a("ptrace.txt");
    string word;
    int count = 0;
    int temp;
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
  
    //Read the ptrace
  //  count = 0;
 /*   while(a >> word){
        if(flag == false){
            temp = stoi(word);
            ptrace[count][0] = temp;
            flag = true;
        } else {
            temp = stoi(word);
            ptrace[count][1] = temp;
            flag = false;
            count++;
        }
    }
    */
    
    
    return 0;
}
