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

ifstream a("ptrace.txt");

int plist[10];
/*
int Clock(int p){
    string word;
    int temp=0;
    int pageVar=(512/10)/p;
    int fifoCount=0;
    int memPlace;
    bool flag=false;
    int a1 = 0;
    bool testing = true;
    vector<int> list[10];
    while(a >> word){
        if(flag == false) {
            temp = stoi(word);
            flag = true;
        } else {
            memPlace = stoi(word);
            memPlace = memPlace/p;
            if (find(list[temp].begin(), list[temp].end(),memPlace) == list[temp].end() && find(list[temp].begin(), list[temp].end(),(memPlace + plist[temp] + 1)) == list[temp].end()) {
                fifoCount++;
                while (testing == true) {
                    if(list[temp].size() <= pageVar){
                        list[temp].push_back(memPlace + plist[temp] + 1);
                        testing = false;
                    } else {
                        if(list[temp].front() > plist[temp]){
                            a1 = list[temp].front();
                            list[temp].erase(list[temp].begin());
                            list[temp].push_back(a1 - (plist[temp] + 1));
                        } else {
                            list[temp].erase(list[temp].begin());
                            list[temp].push_back(memPlace + plist[temp] + 1);
                            testing = false;
                        }
                    }
                }
            }
            flag = false;
            testing = true;
        }
    }
    return fifoCount;
}
*/

struct clockData{
    int memData;
    bool valueBit;
};

struct find_clockData{
    int memData;
    find_clockData(int memData) : memData(memData) {}
    bool operator () ( const clockData& m ) const{
        return m.memData == memData;
    }
};

int Clock(int p){
    string word;
    int temp=0;
    int pageVar=(512/10)/p;
    int fifoCount=0;
    int memPlace;
    bool flag=false;
    clockData a1;
    bool testing = true;
    vector<clockData> list[10];
    while(a >> word){
        if(flag == false) {
            temp = stoi(word);
            flag = true;
        } else {
            memPlace = stoi(word);
            memPlace = memPlace/p;
            clockData t;
            t.memData = memPlace;
            t.valueBit = true;
            if (find_if(list[temp].begin(), list[temp].end(),find_clockData(memPlace)) == list[temp].end()) {
                fifoCount++;
                while (testing == true) {
                    if(list[temp].size() <= pageVar){
                        list[temp].push_back(t);
                        testing = false;
                    } else {
                        if(list[temp].front().valueBit == true){
                            a1 = list[temp].front();
                            list[temp].erase(list[temp].begin());
                            a1.valueBit = false;
                            list[temp].push_back(a1);
                        } else {
                            list[temp].erase(list[temp].begin());
                            list[temp].push_back(t);
                            testing = false;
                        }
                    }
                }
            }
            flag = false;
            testing = true;
        }
    }
    return fifoCount;
}
//Not Implemented yet for prepaging
int Clock2(int p){
  string word;
    int temp=0;
    int pageVar=(512/10)/p;
    int fifoCount=0;
    int memPlace;
    bool flag=false;
    clockData a1;
    bool testing = true;
    vector<clockData> list[10];
    while(a >> word){
        if(flag == false) {
            temp = stoi(word);
            flag = true;
        } else {
            memPlace = stoi(word);
            memPlace = memPlace/p;
            clockData t;
            t.memData = memPlace;
            t.valueBit = true;
            if (find_if(list[temp].begin(), list[temp].end(),find_clockData(memPlace)) == list[temp].end()) {
                fifoCount++;
                while (testing == true) {
                    if(list[temp].size() <= pageVar){
                        list[temp].push_back(t);
                        testing = false;
                    } else {
                        if(list[temp].front().valueBit == true){
                            a1 = list[temp].front();
                            list[temp].erase(list[temp].begin());
                            a1.valueBit = false;
                            list[temp].push_back(a1);
                        } else {
                            list[temp].erase(list[temp].begin());
                            list[temp].push_back(t);
                            testing = false;
                        }
                    }
                }
            }
            flag = false;
            testing = true;
        }
    }
    return fifoCount;
}
int LRU(int p){
    string word;
    int temp=0;
    int pageVar=(512/10)/p;
    int fifoCount=0;
    int memPlace;
    bool flag=false;
    vector<int> list[10];
    while(a >> word){
        if(flag == false) {
            temp = stoi(word);
            flag = true;
        } else {
            memPlace = stoi(word);
            memPlace = memPlace/p;
            if (find(list[temp].begin(), list[temp].end(), memPlace) == list[temp].end()) {
                list[temp].insert(list[temp].begin(),memPlace);
                fifoCount++;
                if(list[temp].size() > pageVar){
                    list[temp].pop_back();
                }
            } else {
                list[temp].erase(find(list[temp].begin(), list[temp].end(), memPlace));
                list[temp].insert(list[temp].begin(),memPlace);
            }
            flag = false;
        }
    }
    return fifoCount;
}
//not yet implemented for prepaging
int LRU2(int p){
    string word;
    int temp=0;
    int pageVar=(512/10)/p;
    int fifoCount=0;
    int memPlace;
    bool flag=false;
    vector<int> list[10];
    while(a >> word){
        if(flag == false) {
            temp = stoi(word);
            flag = true;
        } else {
            memPlace = stoi(word);
            memPlace = memPlace/p;
            if (find(list[temp].begin(), list[temp].end(), memPlace) == list[temp].end()) {
                list[temp].insert(list[temp].begin(),memPlace);
                fifoCount++;
                if(list[temp].size() > pageVar){
                    list[temp].pop_back();
                }
            } else {
                list[temp].erase(find(list[temp].begin(), list[temp].end(), memPlace));
                list[temp].insert(list[temp].begin(),memPlace);
            }
            flag = false;
        }
    }
    return fifoCount;
}


//Not working yet
int FIFOPload(int p){
    string word;
    int word2[10];
    int size=0;
    //int size2=0;
    int counter=0;
    int temp=0;
    int pageVar=(512/10)/p;
    int fifoCount=0;
    int memPlace;
    bool searching = false;
    bool flag=false;
    bool checker=false;
    vector<int> list[10];
    while(a >> word){
        printf("stoi(word)=%i\n",stoi(word) );
        checker=false;
        for(int i=0;i<counter;i++){
            if(stoi(word)==word2[i]){
                checker=true;
            }
        }
        if (checker==false){
            word2[size]=stoi(word);
            printf("The first word is %i\n",word2[0] );
            size++;
        }
        counter++;
        if(counter==10){
        
            for(int j=0; j<size;j++){
                printf("it gets in here\n");
                printf("%i\n",word2[size-1] );
                if(flag == false) {
                    printf("seg fault not in if\n");
                    temp = word2[j];
                    flag = true;
                } else {
                    printf("seg fault not in else\n");
                    memPlace = word2[j];
                    memPlace = memPlace/p;
                    printf("memPlace is %i and temp is %i\n",memPlace,temp);
                    if (find(list[temp].begin(), list[temp].end(), memPlace) == list[temp].end()) {
                        fifoCount++;
                        //printf("seg fault before 2nd if\n");
                        list[temp].insert(list[temp].begin(),memPlace);
                        //printf("seg fault in 2nd if\n");
                        if(list[temp].size() > pageVar)
                            list[temp].pop_back();
                
                    }
                
                    flag = false;
                }
            }
            counter=0;
            size=0;
        }
    }
    return fifoCount;
}

int FIFO2(int p){
    string word;
    int temp=0;
    int pageVar=(512/10)/p;
    int fifoCount=0;
    int memPlace;
    bool flag=false;
    int counter1 = 0;
    int counter2 = 0;
    clockData t;
    vector<int> list[10];
    vector<int> list2[10];
    while(a >> word){
        if(flag == false) {
            temp = stoi(word);
            flag = true;
        } else {
            memPlace = stoi(word);
            memPlace = memPlace/p;
            counter1++;
            if (find(list2[temp].begin(), list2[temp].end(), memPlace) == list2[temp].end()){
                list2[temp].push_back(memPlace);
            }
            if(counter1 == 10){
                for(int i = 0; i < 10; i++){
                    while(!list2[i].empty()){
                        if (find(list[i].begin(), list[i].end(), list2[i].front()) == list[i].end()) {
                            fifoCount++;
                            list[i].insert(list[i].begin(),list2[i].front());
                            if(list[i].size() > pageVar)
                                list[i].pop_back();
                        }
                        list2[i].erase(list2[i].begin());
                    }
                }
            }
         /*   if (find_if(list[temp].begin(), list[temp].end(),find_clockData(memPlace)) == list[temp].end()) {
                fifoCount++;
                list[temp].insert(list[temp].begin(),memPlace);
                if(list[temp].size() > pageVar)
                    list[temp].pop_back();
            }
            */
            flag = false;
        }
    }
    return fifoCount;
    
}


int FIFO(int p){
    string word;
    int temp=0;
    int pageVar=(512/10)/p;
    int fifoCount=0;
    int memPlace;
    bool flag=false;
    vector<int> list[10];
    while(a >> word){
        if(flag == false) {
            temp = stoi(word);
            flag = true;
        } else {
            memPlace = stoi(word);
            memPlace = memPlace/p;
            if (find(list[temp].begin(), list[temp].end(), memPlace) == list[temp].end()) {
                fifoCount++;
                list[temp].insert(list[temp].begin(),memPlace);
                if(list[temp].size() > pageVar)
                    list[temp].pop_back();
            
            }
         
            flag = false;
        }
    }
    return fifoCount;

}


int main(int argc, char *argv[]) {
    if(argc!=6){
        cout << "Error, must have 6 arguments." << endl;
        return 0;
    }
    //Declare the two inputs from the files, and read the files into the data
    ifstream f("plist.txt");

    string word;
    int count = 0;
    int temp = 0;
    bool flag = false;
    //Read the plist
    while(f >> word){
        temp = stoi(word);
        if(temp != count){
            plist[count] = temp;
            count++;
        }
    }
    count=0;
    int pages=stoi(argv[3]);
    string algo=argv[4];
    string load=argv[5];
    transform(algo.begin(), algo.end(), algo.begin(), ::tolower);
    if(load.compare("-")==0){
        cout << "No prepaging: " << endl;
        if(algo.compare("fifo")==0){
            count=FIFO(pages);
            a.close();
            cout << "FIFO for size "<< pages <<": " << count << endl;
            return 0;
        }
        if(algo.compare("lru")==0){
            count=LRU(pages);
            a.close();
            cout << "LRU for size "<< pages <<": " << count << endl;
            return 0;
        }
        if(algo.compare("clock")==0){
            count=Clock(pages);
            a.close();
            cout << "Clock for size "<< pages <<": " << count << endl;
            return 0;
        }
    }
    if(load.compare("+")==0){
        cout << "Prepaging:" << endl;
        if(algo.compare("fifo")==0){
            count=FIFO2(pages);
            a.close();
            cout << "For size "<< pages <<": " << count << endl;
            return 0;
        }
        if(algo.compare("lru")==0){
            count=LRU2(pages);
            a.close();
            cout << "For size "<< pages <<": " << count << endl;
            return 0;
        }
        if(algo.compare("clock")==0){
            count=Clock2(pages);
            a.close();
            cout << "For size "<< pages <<": " << count << endl;
            return 0;
        }
    }
    /*
    count = 0;
    //Go through the ptrace for the FIFO
    cout << "--------------------------------------------------" << endl;
    cout << "Going throug to find how many page faults for FIFO" << endl;
    int memPlace2;
    count=FIFO2(1);
    a.close();
    cout << "For size 1: " << count << endl;
    a.open("ptrace.txt");
    count=FIFO2(2);
    cout << "For size 2: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count=FIFO2(4);
    cout << "For size 4: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count=FIFO2(8);
    cout << "For size 8: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count=FIFO(16);
    cout << "For size 16: " << count << endl;
    a.close();
    cout << "---------------------------------------------------" << endl;
    cout << "Going throug to find how many page faults for LRU" << endl;
/*    a.open("ptrace.txt");
    count = LRU(1);
    cout << "For size 1: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count = LRU(2);
    cout << "For size 2: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count = LRU(4);
    cout << "For size 4: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count = LRU(8);
    cout << "For size 8: " << count << endl;
    a.close();
    a.open("ptrace.txt");
    count = LRU(16);
    cout << "For size 16: " << count << endl;
    a.close(); 
    cout << "---------------------------------------------------" << endl;
    cout << "Going throug to find how many page faults for FIFOPload" << endl;
*/
    cout << "Error: Invalid arguments given" << endl;
    return 0;
}
