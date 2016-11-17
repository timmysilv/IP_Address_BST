#include "TreeDB.h"

TreeDB::TreeDB(){
    root = NULL;
    probesCount = 0;
}

TreeDB::~TreeDB(){
    delete root;
    root = NULL;
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
        if(root->getLeft()==NULL){ //Right subtree is now the tree
            TreeNode *temp = root->getRight();
            root->setRight(NULL);
            delete root;
            root = temp;
        }
        else if(root->getRight()==NULL){ //Left subtree is now the tree
            TreeNode *temp = root->getLeft();
            root->setLeft(NULL);
            delete root;
            root = temp;
        }
        else //Has left and right subtrees, use the algorithm
            (root->getLeft())->max(root);
        return true;
    }
    //Will only get here if root is not the desired node
    bool leftBool,rightBool;
    if(root->getLeft()!=NULL) //Avoid dereferencing NULL pointer
        leftBool = root->getLeft()->remove(name,root,0);
    else leftBool = false;
    
    if(root->getRight()!=NULL) ////Avoid dereferencing NULL pointer
        rightBool = root->getRight()->remove(name,root,1);
    else rightBool = false;
    return (leftBool || rightBool);
}

void TreeDB::clear(){
    delete root;
    root = NULL; //Good practice
}
    
void TreeDB::printProbes() const{
    cout << probesCount << endl;;
}

void TreeDB::countActive() const{
    cout << root->countActive() << endl;
}

void TreeDB::print(){
    if(root!=NULL)
        root->print();
}