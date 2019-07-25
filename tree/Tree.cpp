#include "Tree.h"

Tree::Tree() : m_root(NULL), m_nodes(0) {}

Tree::~Tree() {}

Node *Tree::find_path(string source, string dest, int depth) {
    //todo: enable reuse, destruct all and check null, this is a one timer
    Node::m_tree = this;
    if (!this->m_root) {
        m_root = new Node(source, NULL, NULL, depth);
        m_nodes++;
    }
    m_root->resolve_links();
}

void Tree::insert(string page, Node *source) {
    Node *current = m_root;
    Node *prev;

    while (current) {
        prev = current;
        if (*current > page) {
            current = current->m_left;
        } else if (*current < page) {
            current = current->m_right;
        } else {
            return;
        }
    }

    Node *page_node = new Node(page, prev, source, source->m_depth - 1);
    if (*prev > page) {
        prev->m_left = page_node;
    } else if (*prev < page) {
        prev->m_right = page_node;
    }
    m_nodes++;
    page_node->resolve_links();
}

void Tree::save() {
    if (!m_root) return;
    map<string, vector<string>> pages;
    if (m_root->m_right) m_root->m_right->get_pages(pages);
    if (m_root->m_left) m_root->m_left->get_pages(pages);
    for (map<string, vector<string>>::iterator it = pages.begin(); it != pages.end(); it++) {
        cout << it->first << ": " << it->second.size() << endl;
    }
}