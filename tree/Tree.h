#pragma once

#include "../node/Node.h"

#include <string>
#include <time.h>

using namespace std;

class Node;

class Tree {
public:
    Tree();

    ~Tree();

    Node *find_path(string source, string dest, int depth);

    void insert(string page, Node *source);

    void save();

    void print_path(Node *page);

    void print_solution();


private:
    string m_dest;
    Node *m_root;
    uint64_t m_nodes;
    bool m_found;
    Node *m_path;
    int m_depth;
    time_t m_start;
    time_t m_finish;
};
