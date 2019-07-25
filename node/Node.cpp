#include "Node.h"

Tree *Node::m_tree = NULL;

Node::Node(string page, Node *parent, Node *source, uint8_t depth) {
<<<<<<< HEAD
    //todo: still not AVL tree...
    m_page = page;
    m_parent = parent;
    m_source = source;
    m_right = NULL;
    m_left = NULL;
    m_depth = depth;
    m_balance = 0;
=======
    this->m_page = page;
    this->m_parent = parent;
    this->m_source = source;
    this->m_right = NULL;
    this->m_left = NULL;
    this->m_depth = depth;
>>>>>>> 1df8cad... Working WIP, first commit after a considerebly long development, will improve.
}

Node::~Node() {
    if (m_right) delete m_right;
    if (m_left) delete m_left;
}

bool Node::operator<(const Node &other) {
    return this->m_page < other.m_page;
}

bool Node::operator<(const string &other) {
    return this->m_page < other;
}

bool Node::operator>(const Node &other) {
    return this->m_page > other.m_page;
}

bool Node::operator>(const string &other) {
    return this->m_page > other;
}

void Node::resolve_links() {
    if (!m_depth) return;
    uint16_t links_num;
    string *links = WikipediaUtils::get_page_links(m_page, links_num);
<<<<<<< HEAD
    for (uint16_t i = 0; i < links_num; i++) {
=======
    for (int i = 0; i < links_num; i++) {
>>>>>>> 1df8cad... Working WIP, first commit after a considerebly long development, will improve.
        Node::m_tree->insert(links[i], this);
    }
    delete[] links;
}

void Node::get_pages(map<string, vector<string>> &pages) {
    pages[m_source->m_page].push_back(m_page);
    if (m_right) m_right->get_pages(pages);
    if (m_left) m_left->get_pages(pages);
}
