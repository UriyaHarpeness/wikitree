#include "Node.h"

Tree *Node::m_tree = nullptr;

Node::Node(string page, Node *parent, Node *source, uint8_t depth) {
    m_page = move(page);
    m_parent = parent;
    m_source = source;
    m_right = nullptr;
    m_left = nullptr;
    m_depth = depth;
    m_height = 1;
}

Node::~Node() {
    delete m_right;
    delete m_left;
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
    if (m_tree->m_found) return;
    uint16_t links_num;
    string *links = WikipediaUtils::get_page_links(WikipediaUtils::unpack_link(m_page), links_num);
    for (uint16_t i = 0; i < links_num; i++) {
        Node::m_tree->insert(links[i], this);
    }
    delete[] links;
}

void Node::resolve_links_by_depth(const uint8_t &depth) {
    Node *current_right = m_right; // this is required, since `m_right` may change if the node rotates.
    if (m_left) m_left->resolve_links_by_depth(depth);
    if (m_depth == depth) this->resolve_links();
    if (current_right) current_right->resolve_links_by_depth(depth);
}

void Node::get_pages(map<string, vector<string>> &pages) {
    if (m_left) m_left->get_pages(pages);
    pages[m_source->m_page].push_back(m_page);
    if (m_right) m_right->get_pages(pages);
}

int8_t Node::get_balance() {
    return ((m_right) ? m_right->m_height : 0) - ((m_left) ? m_left->m_height : 0);
}

void Node::print() {
    cout << "value: " << WikipediaUtils::unpack_link(m_page)
         << ", left: " << ((m_left) ? WikipediaUtils::unpack_link(m_left->m_page) : "nullptr")
         << ", right: " << ((m_right) ? WikipediaUtils::unpack_link(m_right->m_page) : "nullptr")
         << ", parent: " << ((m_parent) ? WikipediaUtils::unpack_link(m_parent->m_page) : "nullptr")
         << ", height: " << (int) m_height
         << ", balance: " << (int) this->get_balance() << endl;
}

void Node::print_path() {
    Node *node = this;
    do {
        cout << WikipediaUtils::unpack_link(node->m_page);
        node = node->m_source;
        if (node) cout << " <- ";
    } while (node);
    cout << endl;
}
