#include "arbolB.h"
#include <iostream>
#include <algorithm>

using namespace std;

BTreeNode::BTreeNode(int t1, int leaf1) {
    t = t1;
    leaf = leaf1;
}

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
        cout << " " << keys[i];
    }
    if (!leaf)
        children[i]->traverse();
}

void BTreeNode::insertNonFull(uint64_t k,const shared_ptr<UserData>& data){
    int i = keys.size() - 1;
    if (leaf) {
        keys.push_back(0);
        userData.push_back(nullptr);
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            userData[i + 1] = userData[i];
            i--;
        }
        keys[i + 1] = k;
        userData[i + 1] = data;
    } else {
        while (i >= 0 && keys[i] > k) {
            i--;
        }
        if (children[i + 1]->keys.size() == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < k) {
                i++;
            }
        }
        children[i + 1]->insertNonFull(k, data);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y){
   BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->keys.resize(t - 1);
    z->userData.resize(t - 1);
    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
        z->userData[j] = y->userData[j + t];
    }
    if (!y->leaf) {
        z->children.resize(t);
        for (int j = 0; j < t; j++) {
            z->children[j] = y->children[j + t];
        }
    }
    y->keys.resize(t - 1);
    y->userData.resize(t - 1);
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
    userData.insert(userData.begin() + i, y->userData[t - 1]);
}

shared_ptr<UserData> BTreeNode::search(uint64_t k){
   int i = 0;
    while (i < keys.size() && k > keys[i]) {
        i++;
    }
    if (i < keys.size() && keys[i] == k) {
        return userData[i];
    }
    if (leaf) {
        return nullptr;
    }
    return children[i]->search(k);
}

Btree::Btree(int t1){
    root = new BTreeNode(t1, true);
    t = t1;
}

Btree::~Btree() {
    delete root;
}

void Btree::traverse(){
    if(root != nullptr) root->traverse();
}

void Btree::insert(uint64_t k, const shared_ptr<UserData>& data) {
    if (root->keys.size() == 2 * t - 1) {
        BTreeNode* s = new BTreeNode(t, false);
        s->children.push_back(root);
        s->splitChild(0, root);
        int i = 0;
        if (s->keys[0] < k) {
            i++;
        }
        s->children[i]->insertNonFull(k, data);
        root = s;
    } else {
        root->insertNonFull(k, data);
    }
}