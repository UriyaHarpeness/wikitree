#include "Tree.h"

Tree::Tree() : m_root(NULL), m_nodes(0), m_path(NULL) {}

Tree::~Tree() {}

Node *Tree::find_path(string source, string dest, int depth) {
    //todo: enable reuse, destruct all and check null, this is a one timer,
    //todo: also input can't be trusted, not to be invalid or same dest and source...
    m_found = false;
    m_dest = move(dest);
    Node::m_tree = this;
    m_start = time(NULL);
    m_depth = depth;

    if (!this->m_root) {
        m_root = new Node(move(source), NULL, NULL, depth);
        m_nodes++;
    }

    while (depth && (!m_found)) {
        cout << "current node count at: " << m_nodes <<
             ", resolving depth: " << depth <<
             ", seconds count so far: " << time(NULL) - m_start << endl;
        m_root->resolve_links_by_depth(depth--);
    }

    if (!m_found) m_finish = time(NULL);

    return m_path;
}

void Tree::insert(const string &page, Node *source) {
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

    //the warnings about "prev" being null are irrelevant, since its value is
    //set if root has a value, which he does, when a call to "find_path" is invoked.
    Node *page_node = new Node(page, prev, source, source->m_depth - 1);
    if ((prev != m_root) && (!(prev->m_left || prev->m_right))) {
        prev->m_parent->m_balance += (prev->m_parent->m_right == prev) ? 1 : -1;
    }
    if (*prev > page) {
        prev->m_left = page_node;
        prev->m_balance--;
    } else if (*prev < page) {
        prev->m_right = page_node;
        prev->m_balance++;
    }
    m_nodes++;

    this->rebalance(prev);

    if (page == m_dest) {
        m_found = true;
        m_path = page_node;
        m_finish = time(NULL);
    }
}

void Tree::rebalance(Node *node) {
    if (node == m_root) return;
    Node *tmp;

    if (node->m_parent->m_balance == 2) {
        if (node->m_balance == 1) {
            cout << 21 << endl;
            //seems good
            if (node->m_parent == m_root) {
                m_root = node;
            } else {
                if (node->m_parent->m_parent->m_right == node->m_parent) {
                    node->m_parent->m_parent->m_right = node;
                } else {
                    node->m_parent->m_parent->m_left = node;
                }
            }
            node->m_left = node->m_parent;
            node->m_parent = node->m_parent->m_parent;
            node->m_left->m_parent = node;
            node->m_balance = 0;
            node->m_left->m_balance = 0;
            node->m_left->m_right = nullptr;
        } else if (node->m_balance == -1) {
            cout << 2 << -1 << endl;
            //seems good, needs check
            if (node->m_parent == m_root) {
                m_root = node->m_left;
            } else {
                if (node->m_parent->m_parent->m_right == node->m_parent) {
                    node->m_parent->m_parent->m_right = node->m_right;
                } else {
                    node->m_parent->m_parent->m_left = node->m_right;
                }
            }
            node->m_left->m_parent = node->m_parent->m_parent;
            node->m_left->m_right = node;
            node->m_left->m_left = node->m_parent;
            node->m_left->m_left->m_parent = node->m_left;
            node->m_parent = node->m_left;
            node->m_balance = 0;
            node->m_left = nullptr;
            node->m_parent->m_left->m_right = nullptr;
            node->m_parent->m_left->m_balance = 0;
        }
    } else if (node->m_parent->m_balance == -2) {
        if (node->m_balance == 1) {
            cout << -21 << endl;
            //seems good, needs check
            if (node->m_parent == m_root) {
                m_root = node->m_right;
            } else {
                if (node->m_parent->m_parent->m_right == node->m_parent) {
                    node->m_parent->m_parent->m_right = node->m_right;
                } else {
                    node->m_parent->m_parent->m_left = node->m_right;
                }
            }
            node->m_right->m_parent = node->m_parent->m_parent;
            node->m_right->m_left = node;
            node->m_right->m_right = node->m_parent;
            node->m_right->m_right->m_parent = node->m_right;
            node->m_parent = node->m_right;
            node->m_balance = 0;
            node->m_right = nullptr;
            node->m_parent->m_right->m_left = nullptr;
            node->m_parent->m_right->m_balance = 0;
        } else if (node->m_balance == -1) {
            cout << -2 << -1 << endl;
            //seems good
            if (node->m_parent == m_root) {
                m_root = node;
            } else {
                if (node->m_parent->m_parent->m_right == node->m_parent) {
                    node->m_parent->m_parent->m_right = node;
                } else {
                    node->m_parent->m_parent->m_left = node;
                }
            }
            node->m_right = node->m_parent;
            node->m_parent = node->m_parent->m_parent;
            node->m_right->m_parent = node;
            node->m_balance = 0;
            node->m_right->m_balance = 0;
            node->m_right->m_left = nullptr;
        }
    }

    //balance calculated correctly, now do balancing

    //check what if the root needs rebalancing, that it's not acting funny
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
