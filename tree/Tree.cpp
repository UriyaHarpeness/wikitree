#include "Tree.h"

Tree::Tree() : m_root(NULL), m_nodes(0), m_path(NULL) {}

Tree::~Tree() {}

Node *Tree::find_path(string source, string dest, int depth) {
    //todo: enable reuse, destruct all and check null, this is a one timer,
    //todo: also input can't be trusted, not to be invalid or same dest and source...
    m_found = false;
    m_dest = dest;
    Node::m_tree = this;
    m_start = time(NULL);
    m_depth = depth;

    if (!this->m_root) {
        m_root = new Node(source, NULL, NULL, depth);
        m_nodes++;
    }
    m_root->resolve_links();

    if (!m_found) m_finish = time(NULL);

    return m_path;
}

void Tree::insert(string page, Node *source) {
    if (m_found) return;

    //cout << page << endl;

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

    if (page == m_dest) {
        m_found = true;
        m_path = page_node;
        m_finish = time(NULL);
    }

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

void Tree::print_path(Node *page) {
    while (page) {
        cout << page->m_page;
        page = page->m_source;
        if (page) cout << " <- ";
    }
    cout << endl;
}

void Tree::print_solution() {
    if (m_found) {
        cout << "after going through " << m_nodes <<
             " pages, which took " << m_finish - m_start <<
             " seconds, the path is:" << endl;
        this->print_path(m_path);
    } else {
        cout << "after going through " << m_nodes <<
             " pages, which took " << m_finish - m_start <<
             " seconds, the path between " << m_root->m_page <<
             " and " << m_dest <<
             " was not found with given depth " << m_depth << endl;
    }
}
