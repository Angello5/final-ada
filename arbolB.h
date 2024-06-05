#ifndef ARBOLB_H
#define ARBOLB_H
#include "userData.h"
#include <vector>
#include <string>
#include <memory>

using namespace std;

class BTreeNode
{
    private:

        vector <string> keys;
        vector <shared_ptr<UserData>> userData;
        vector <BTreeNode*> children;
        bool leaf;
        int t;

    public:
        BTreeNode(int t, bool leaf);
        ~BTreeNode();
        void traverse();
        void insertNonFull(string& k, shared_ptr<UserData>& data);
        void splitChild(int i, BTreeNode* y);
        shared_ptr<UserData> search(string& k);
        friend class Btree;
};

class Btree
{
    public:
        BTreeNode* root;
        int t;
        Btree(int t);
        ~Btree();
        void traverse();
        void insert(string& k, shared_ptr<UserData>& data);
        shared_ptr<UserData> search(string& k); 
};

#endif