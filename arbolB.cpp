#include "arbolB.h"
#include <iostream>
#include <algorithm>

using namespace std;

BTreeNode::BTreeNode(int _t, bool _leaf) : t(_t),leaf(_leaf) {}

BTreeNode::~BTreeNode(){
    for(auto child : children){
        delete child;
    }
}

void BTreeNode::traverse(){
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!leaf)
            children[i]->traverse();
        std::cout << " " << keys[i];
    }
    if (!leaf)
        children[i]->traverse();
}

void BTreeNode::insertNonFull(string& k,shared_ptr<UserData>& data){
    int i = keys.size() -1;
    if(leaf){
        while (i >= 0 && keys[i]>k){
            keys[i+1] = keys[i];
            userData[i+1]= userData[i];
            i--;
        }
        keys[i+1] = k;
        userData[i+1] = data;
    }else{
        while(i>=0 && keys[i]>k) i--;
        if(children[i+1]->keys.size()==2*t-1){
            splitChild(i+1, children[i+1]);
            if(keys[i+1]< k) i++;
        }
        children[i+1]->insertNonFull(k,data);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y){
    BTreeNode* z= new BTreeNode(y->t, y->leaf);
    z->keys.assign(y->keys.begin()+ t, y->keys.end());
    z->userData.assign(y->userData.begin() + t, y->userData.end());
    if (!y->leaf) {
        z->children.assign(y->children.begin() + t, y->children.end());
    }
    y->keys.resize(t - 1);
    y->userData.resize(t - 1);
    y->children.resize(t);
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t-1]);
    userData.insert(userData.begin() + i, y->userData[t-1]);
}

shared_ptr<UserData> BTreeNode::search(string& k){
    int i = 0;
    while (i < keys.size() && k > keys[i])++i;
    if(i < keys.size() && keys[i] == k) return userData[i];
    if(leaf) return nullptr;
    return children[i]->search(k);
}


BTree::BTree(int _t) : t(_t) {
    root = nullptr;
}

BTree::~BTree() {
    delete root;
}

void Btree::traverse(){
    if(root != nullptr) root->traverse();
}

void BTree::insert(string& k, shared_ptr<UserData>& data) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys.push_back(k);
        root->userData.push_back(data);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k) i++;
            s->children[i]->insertNonFull(k, data);
            root = s;
        } else {
            root->insertNonFull(k, data);
        }
    }
}