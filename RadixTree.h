//
//  RadixTree.hpp
//  RadixTree
//
//  Created by Nick Johnson on 3/15/22.
//

#ifndef RadixTree_hpp
#define RadixTree_hpp

#include <stdio.h>
#include <map>
#include <iostream>

template <typename ValueType>
class RadixTree {
public:

 RadixTree()
{
     root = new Node;
     root->s = "";
     root->end = false;
     root->parent = nullptr;

 }
 ~RadixTree()
{
     delete root;
 }
    
void insert(std::string key, const ValueType& value)
{
    bool cont;
    Node* n = root;

    while(1)
    {
        cont = true;
    int cur_char = key[0] - 33;
        
        if(key.empty())
        {
            n->end = true;
            return;
        }
        
    if(n->children[cur_char] == nullptr)
    {
        n->children[cur_char] = new Node;
        n->children[cur_char]->s = key;
        n->children[cur_char]->end = true;
        n->children[cur_char]->v1 = value;
        return;
    }

    int match = 0;
        std::string t = n->children[cur_char]->s;
    while(match < std::min(t.length(), key.length()) && t[match] == key[match])
    {
        match++;
    }
        
    if(match == t.length())
    {
        n = n->children[cur_char];
        key = key.substr(match);
        cont = false;
    }
   else if(cont && match == key.length())
    {
        Node* newnode = new Node;
        newnode->children[t[match] - 33] = n->children[cur_char];
        newnode->children[t[match] - 33]->s = t.substr(match);
        
        n->children[cur_char] = newnode;
        n->children[cur_char]->s = key;
        n->children[cur_char]->end = true;
        n->children[cur_char]->v1 = value;
        return;
    }
    else
    {
        Node* newnode = new Node;
        newnode->children[t[match] - 33] = n->children[cur_char];
        newnode->children[t[match] - 33]->s = t.substr(match);
        n->children[cur_char] = newnode;
        n->children[cur_char]->s = key.substr(0, match);
        n = n->children[cur_char];
        key = key.substr(match);
    }
    }
 }
 ValueType* search(std::string key) const
{
    Node* t = find(root, key);
    if(t == nullptr)
        return nullptr;
    return &(t->v1);
    //std::map<std::string,const ValueType&>::iterator it;
    //it = m1.find(key);
}
    
private:
//std::map<std::string, const ValueType&> m1;
    struct Node
    {

        Node* parent;
        std::string s;
        ValueType v1;
        bool end;
        Node* children[128];
        
        Node()
        {
            for(int i = 0; i < 128; i++)
                children[i] = nullptr;
        }
        ~Node()
        {
            for(int i = 0; i < 128; i++)
            {
                delete children[i];
            }
        }

    };
    Node* root;
    
    Node* find(Node* root, std::string k) const
    {
        if(k.empty())
        {
            return root;
        }
        
        int cur_char = k[0] - 33;
        
        if(root->children[cur_char] == nullptr)
            return nullptr;
        std::string t = root->children[cur_char]->s;
        int len = std::min(t.length(), k.length());
        if(t.substr(0, len) != k.substr(0, len))
            return nullptr;
        if(t.length() == len)
            return find(root->children[cur_char], k.substr(t.length()));
        else
            return nullptr;
    }

};



#endif /* RadixTree_hpp */
