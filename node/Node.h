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

    void resolve_links_by_depth(uint8_t depth);

    void get_pages(map<string, vector<string>> &pages);

    int8_t get_balance();

    void print();

    void print_path();

    static Tree *m_tree;

    friend class Tree;


private:
    Node *m_source;
    string m_page;
    Node *m_left;
    Node *m_right;
    Node *m_parent;
    int8_t m_height; //a small number, but in an AVL tree this should suffice
    uint8_t m_depth;
};
