/* 
 * File:   Main.cpp
 * Author: Matthew
 *
 * Created on November 14, 2016, 5:23 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include "TreeDB.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string input,cmd,name,status;
    bool statusBool;
    unsigned int ip;
    TreeDB tree;
    DBentry* entry;
    
    do{
        cout << "> ";
        getline(cin,input);
        stringstream ss(input);
        ss >> cmd;
        
        if(cmd=="insert"){
            ss >> name;
            ss >> ip;
            ss >> status;
            
            if(status=="active") statusBool = true;
            else statusBool = false;
            entry = new DBentry(name,ip,statusBool);
            
            if(tree.insert(entry)) //It was inserted
                cout << "Success" << endl;
            else //It already exists
                cout << "Error: entry already exists" << endl;
        }
        else if(cmd=="find"){
            ss >> name;
            entry = tree.find(name);
            if(entry==NULL) //'name' was not found
                cout << "Error: entry does not exist" << endl;
            else //Determine its status, print
                entry->print();
        }
        else if(cmd=="remove"){
            ss >> name;
            if(tree.remove(name))
                cout << "Success" << endl;
            else
                cout << "Error: entry does not exist" << endl;
        }
        else if(cmd=="printall")
            tree.print();
        else if(cmd=="printprobes"){
            ss >> name;
            if(tree.find(name)!=NULL) //'name' exists
                tree.printProbes();
            else
                cout << "Error: entry does not exist" << endl;
        }
        else if(cmd=="removeall"){
            tree.clear();
            cout << "Success" << endl;
        }
        else if(cmd=="countactive")
            tree.countActive();
        else if(cmd=="updatestatus"){
            ss >> name;
            ss >> status;
            entry = tree.find(name);
            if(entry==NULL)
                cout << "Error: entry does not exist" << endl;
            else{
                if(status=="active")
                    entry->setActive(true);
                else if(status=="inactive")
                    entry->setActive(false);
                cout << "Success" << endl;
            }
        }
    }while(!cin.eof());
    tree.clear();
    return 0;
}

