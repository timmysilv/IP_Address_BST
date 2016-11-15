#include "TreeNode.h"

TreeNode::TreeNode(DBentry* _entryPtr){
    entryPtr = _entryPtr;
    left = NULL;
    right = NULL;
}

TreeNode::~TreeNode(){
    delete entryPtr;
    delete left;
    delete right;
}

void TreeNode::setLeft(TreeNode* newLeft){
    left = newLeft;
}

void TreeNode::setRight(TreeNode* newRight){
    right = newRight;
}

TreeNode* TreeNode::getLeft() const{
    return left;
}

TreeNode* TreeNode::getRight() const{
    return right;
}

DBentry* TreeNode::getEntry() const{
    return entryPtr;
}

bool TreeNode::insert(DBentry* newEntry){
    if(entryPtr->getName() == newEntry->getName()) //domain name is taken
        return false;
    if(newEntry->getIPaddress() < entryPtr->getIPaddress()){ //Go down left tree
        if(left == NULL) //Found its place
            setLeft(new TreeNode(newEntry));
        else
            return left->insert(newEntry);            
    }
    
    else{ //Go down right subtree (greater or equal IP address)
        if(right == NULL) //Found its place
            setRight(new TreeNode(newEntry));
        else
            return right->insert(newEntry);
    }
    
    return true;
}

DBentry* TreeNode::find(string name, int& probes){
    probes++;
    if(entryPtr->getName() == name) //This is the desired node
        return entryPtr;
    else{ //This is not the desired node
        if(left!=NULL) //Search the left subtree first
            return left->find(name, probes);
        else if(right!=NULL) //If left==NULL, but right!=NULL
            return right->find(name,probes);
        else //If this node has no children, 'name' doesn't exist
            return NULL;
    }
}

bool TreeNode::remove(string name, TreeNode* parent, int dir){
    if(entryPtr->getName()!=name){
        if(left!=NULL) //Search the left subtree first
            return left->remove(name,this);
        else if(right!=NULL) //If 
            return right->remove(name,this);
        else //domain name does not exist
            return false;
    }
    else{ //Delete this node, find highest node in left subtree
        if(left==NULL){
            if(right==NULL){
                if(parent==NULL)
            }
        }
    }
}

TreeNode* TreeNode::leftMax(){
    
}