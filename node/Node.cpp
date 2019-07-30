#include "Node.h"

Tree *Node::m_tree = NULL;

Node::Node(string page, Node *parent, Node *source, uint8_t depth) {
    //todo: still not AVL tree...
    m_page = move(page);
    m_parent = parent;
    m_source = source;
    m_right = NULL;
    m_left = NULL;
    m_depth = depth;
    m_balance = 0;
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
    for (uint16_t i = 0; i < links_num; i++) {
        Node::m_tree->insert(links[i], this);
    }
    delete[] links;
}

void Node::resolve_links_by_depth(uint8_t depth) {
    if (m_left) m_left->resolve_links_by_depth(depth);
    if (m_depth == depth) this->resolve_links();
    if (m_right) m_right->resolve_links_by_depth(depth);
}

void Node::get_pages(map<string, vector<string>> &pages) {
    if (m_left) m_left->get_pages(pages);
    pages[m_source->m_page].push_back(m_page);
    if (m_right) m_right->get_pages(pages);
}
