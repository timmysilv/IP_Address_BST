#include "TreeDB.h"

TreeDB::TreeDB(){
    root = NULL;
    probesCount = 0;
}

TreeDB::~TreeDB(){
    delete root;
}

bool TreeDB::insert(DBentry* newEntry){
    if(root==NULL){
        root = new TreeNode(newEntry);
        return true;
    }
    return root->insert(newEntry);
}

DBentry* TreeDB::find(string name){
    probesCount = 0;
    if(root==NULL) return NULL;
    return root->find(name,probesCount);
        
}

bool TreeDB::remove(string name){
    if(root==NULL) return false;
    if(root->getEntry()->getName() == name){ //Removing the root
        if(root->getLeft()==NULL) //Right subtree is now the tree
            root = root->getRight();
        else if(root->getRight()==NULL) //Left subtree is now the tree
            root = root->getLeft();
        else{ //Has left and right subtrees, use the algorithm
            TreeNode *rTemp = root->getRight();
            root = root->leftMax();
            root->setRight(rTemp);
        }
    }
    else return root->remove(name,NULL,0);
}

void TreeDB::clear(){
    
}
    
void TreeDB::printProbes() const{
    
}

void TreeDB::countActive() const{
    
}

//friend??