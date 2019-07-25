#pragma once

#include "../node/Node.h"

#include <string>

using namespace std;

class Node;

class Tree {
public:
    Tree();

    ~Tree();

    Node *find_path(string source, string dest, int depth);

    void insert(string page, Node *source);

    void save();


private:
    Node *m_root;
    uint64_t m_nodes;
};
