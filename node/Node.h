#pragma once

#include "../tree/Tree.h"
#include "../wikipedia_utils/WikipediaUtils.h"

#include <string>
<<<<<<< HEAD
=======
#include <mutex>
>>>>>>> 1df8cad... Working WIP, first commit after a considerebly long development, will improve.

using namespace std;

class Tree;

class Node {
public:
    Node(string page, Node *parent, Node *source, uint8_t depth);

    ~Node();

    bool operator<(const Node &other);

    bool operator<(const string &other);

    bool operator>(const Node &other);

    bool operator>(const string &other);

    void resolve_links();

    void get_pages(map <string, vector<string>> &pages);

    static Tree *m_tree;

    friend class Tree;


private:
    Node *m_source;
    string m_page;
    Node *m_left;
    Node *m_right;
    Node *m_parent;
    uint8_t m_balance;
<<<<<<< HEAD
    uint8_t m_depth;
};
=======
    mutex m_lock;
    uint8_t m_depth;
};

//was 65 KB Pizza depth 2
>>>>>>> 1df8cad... Working WIP, first commit after a considerebly long development, will improve.
