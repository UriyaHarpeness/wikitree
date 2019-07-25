#pragma once

#include "../tree/Tree.h"
#include "../wikipedia_utils/WikipediaUtils.h"

#include <string>

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
    uint8_t m_depth;
};
