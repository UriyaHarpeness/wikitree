#pragma once

#include "../node/Node.h"

#include <string>
<<<<<<< HEAD
#include <time.h>
=======
>>>>>>> 1df8cad... Working WIP, first commit after a considerebly long development, will improve.

using namespace std;

class Node;

class Tree {
public:
    Tree();

    ~Tree();

    Node *find_path(string source, string dest, int depth);

    void insert(string page, Node *source);

    void save();

<<<<<<< HEAD
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
=======

private:
    Node *m_root;
    uint64_t m_nodes;
>>>>>>> 1df8cad... Working WIP, first commit after a considerebly long development, will improve.
};
