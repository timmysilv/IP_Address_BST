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
    if(newEntry->getName() < entryPtr->getName()){ //Go down left tree
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
    DBentry* entry;
    if(entryPtr->getName() == name) //This is the desired node
        return entryPtr;
    
    if(left==NULL && right==NULL) //no children, 'name' doesn't exist
        return NULL;
    
    if(name < entryPtr->getName()){ //Belongs to the left subtree
        if(left!=NULL) //subtree exists
            return left->find(name,probes);
        else //End of the subtree, 'name' doesn't exist
            return NULL;
    }
    
    else{ //Belongs to the right subtree
        if(right!=NULL) //subtree exists
            return right->find(name,probes);
        else //End of subtree, 'name' doesn't exist
            return NULL;
    }
}

//if dir==0, 'this' is parent.left, otherwise, 'this' is parent.right
bool TreeNode::remove(string name, TreeNode* parent, int dir){
    if(entryPtr->getName() != name){
        if(left!=NULL) //Search the left subtree first
            if(left->remove(name,this,0)) return true; //Only return if true
        if(right!=NULL) //If 'name' wasn't in the left subtree
            return right->remove(name,this,1);
        else //no more nodes, domain name does not exist
            return false;
    }
    else{ //Delete this node
        if(left==NULL && right==NULL){
            delete this; //Delete first, otherwise memory leak
            if(dir==0)
                parent->setLeft(NULL);
            else
                parent->setRight(NULL);
        }
        else if(left==NULL){ //Right is not NULL
            if(dir==0)
                parent->setLeft(right);
            else
                parent->setRight(right);
            right = NULL;
            delete this;
        }
        else if(right==NULL){ //left is not NULL
            if(dir==0)
                parent->setLeft(left);
            else
                parent->setRight(left);
            left = NULL;
            delete this;
        }
        else //Two children. max(this) will do the work
            left->max(this);
        return true;
    }
}

void TreeNode::max(TreeNode* parent){
    TreeNode *cur,*biggest;
    delete (parent->entryPtr);
    
    if(right==NULL){ //avoid dereferencing NULL pointer (corner case)
        parent->left = left;
        parent->entryPtr = entryPtr;
        left = NULL;
        entryPtr = NULL;
        delete this;
        return;
    }
    //This loop will set cur to be the parent of the node to be deleted    
    for(cur = this; (cur->right)->right != NULL; cur = cur->right){}
    biggest = cur->right;
    parent->entryPtr = biggest->entryPtr;
    biggest->entryPtr = NULL;
    cur->right = biggest->left;
    biggest->left = NULL;
    delete biggest;
}

int TreeNode::countActive(){
    int here;
    if(entryPtr->getActive()) here = 1;
    else here = 0;
    
    if(left==NULL && right == NULL) //base case, no more children
        return here;
    else if(left==NULL) //Only left child
        return here + right->countActive();
    else if(right==NULL) //Only right child
        return here + left->countActive();
    else //Two children
        return here + left->countActive() + right->countActive();
}

void TreeNode::print(){
    if(left!=NULL) left->print();
    if(entryPtr!=NULL) entryPtr->print(); //Shouldn't be NULL
    if(right!=NULL) right->print();
}