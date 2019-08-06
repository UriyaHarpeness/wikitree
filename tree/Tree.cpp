#include "Tree.h"

Tree::Tree() = default;

Tree::~Tree() {
    delete m_root;
}

Node *Tree::find_path(string source, string dest, uint8_t depth) {
    // Cleanup if this isn't the first run, this function is reusable.
    delete m_root;

    m_found = false;
    m_source = WikipediaUtils::pack_link(move(source));
    m_dest = WikipediaUtils::pack_link(move(dest));
    Node::m_tree = this;
    m_start = time(nullptr);
    m_depth = depth;
    m_nodes = 1;

    cout << "wikitree's find_path started, searching the path between " << WikipediaUtils::unpack_link(m_source) <<
         " and " << WikipediaUtils::unpack_link(m_dest) <<
         " with given depth " << (int) m_depth << endl;

    m_root = new Node(m_source, nullptr, nullptr, depth);

    while (depth && (!m_found)) {
        cout << "current node count at: " << m_nodes <<
             ", resolving depth: " << (int) depth <<
             ", seconds count so far: " << time(nullptr) - m_start << endl;
        m_root->resolve_links_by_depth(depth--);
    }

    if (!m_found) m_finish = time(nullptr);

    return m_path;
}

void Tree::insert(const string &page, Node *source) {
    if (m_found) return;

    Node *current = m_root;
    Node *prev = nullptr;

    while (current) {
        prev = current;
        if (*current > page) {
            current = current->m_left;
        } else if (*current < page) {
            current = current->m_right;
        } else { // Value already exists.
            return;
        }
    }

    // The warnings about `prev` being null are irrelevant, since its value is set if root has a value, which he does,
    // when a call to `find_path` is invoked.
    Node *page_node = new Node(page, prev, source, source->m_depth - 1);
    if (*prev > page) {
        prev->m_left = page_node;
    } else {
        prev->m_right = page_node;
    }
    m_nodes++;

    if (page == m_dest) {
        m_found = true;
        m_path = page_node;
        m_finish = time(nullptr);
    }

    page_node = Tree::update_height(page_node);
    if (page_node) {
        this->rebalance(page_node);
    }
}

Node *Tree::update_height(Node *node) {
    uint8_t height = 1;
    node = node->m_parent;
    while (node) {
        height++;
        if (node->m_height < height) {
            if (abs(node->get_balance()) == 2) {
                return node;
            }
            node->m_height = height;
            node = node->m_parent;
        } else {
            break;
        }
    }
    return nullptr;
}

void Tree::rebalance(Node *node) {
    if (node->get_balance() == 2) {
        if (node->m_right->get_balance() == 1) {
            this->rotate_rr(node);
        } else { // Balance is -1.
            this->rotate_rl(node);
        }
    } else { // Balance is -2.
        if (node->m_left->get_balance() == 1) {
            this->rotate_lr(node);
        } else { // Balance is -1.
            this->rotate_ll(node);
        }
    }
}

void Tree::rotate_rr(Node *node) {
    Node *new_head = node->m_right;

    // Rotation start.
    if (node == m_root) {
        m_root = new_head;
    } else {
        if (node->m_parent->m_right == node) {
            node->m_parent->m_right = new_head;
        } else {
            node->m_parent->m_left = new_head;
        }
    }

    new_head->m_parent = node->m_parent;
    node->m_right = new_head->m_left;
    if (node->m_right) node->m_right->m_parent = node;
    new_head->m_left = node;
    new_head->m_left->m_parent = new_head;
    // Rotation end.

    // Height updating.
    node->m_height -= 1;
}

void Tree::rotate_rl(Node *node) {
    Node *new_head = node->m_right->m_left;

    // Rotation start.
    if (node == m_root) {
        m_root = new_head;
    } else {
        if (node->m_parent->m_right == node) {
            node->m_parent->m_right = new_head;
        } else {
            node->m_parent->m_left = new_head;
        }
    }

    new_head->m_parent = node->m_parent;
    node->m_right->m_left = new_head->m_right;
    if (node->m_right->m_left) node->m_right->m_left->m_parent = node->m_right;
    new_head->m_right = node->m_right;
    new_head->m_right->m_parent = new_head;
    node->m_right = new_head->m_left;
    if (node->m_right) node->m_right->m_parent = node;
    new_head->m_left = node;
    node->m_parent = new_head;
    // Rotation end.

    // Height updating.
    node->m_height -= 1;
    new_head->m_right->m_height -= 1;
    new_head->m_height += 1;
}

void Tree::rotate_lr(Node *node) {
    Node *new_head = node->m_left->m_right;

    // Rotation start.
    if (node == m_root) {
        m_root = new_head;
    } else {
        if (node->m_parent->m_right == node) {
            node->m_parent->m_right = new_head;
        } else {
            node->m_parent->m_left = new_head;
        }
    }

    new_head->m_parent = node->m_parent;
    node->m_left->m_right = new_head->m_left;
    if (node->m_left->m_right) node->m_left->m_right->m_parent = node->m_left;
    new_head->m_left = node->m_left;
    new_head->m_left->m_parent = new_head;
    node->m_left = new_head->m_right;
    if (node->m_left) node->m_left->m_parent = node;
    new_head->m_right = node;
    node->m_parent = new_head;
    // Rotation end.

    // Height updating.
    node->m_height -= 1;
    new_head->m_left->m_height -= 1;
    new_head->m_height += 1;
}

void Tree::rotate_ll(Node *node) {
    Node *new_head = node->m_left;

    // Rotation start.
    if (node == m_root) {
        m_root = new_head;
    } else {
        if (node->m_parent->m_right == node) {
            node->m_parent->m_right = new_head;
        } else {
            node->m_parent->m_left = new_head;
        }
    }

    new_head->m_parent = node->m_parent;
    node->m_left = new_head->m_right;
    if (node->m_left) node->m_left->m_parent = node;
    new_head->m_right = node;
    new_head->m_right->m_parent = new_head;
    // Rotation end.

    // Height updating.
    node->m_height -= 1;
}

void Tree::print_solution() {
    if (m_found) {
        cout << "after going through " << m_nodes <<
             " pages, which took " << m_finish - m_start <<
             " seconds, the path is:" << endl;
        m_path->print_path();
    } else {
        cout << "after going through " << m_nodes <<
             " pages, which took " << m_finish - m_start <<
             " seconds, the path between " << WikipediaUtils::unpack_link(m_source) <<
             " and " << WikipediaUtils::unpack_link(m_dest) <<
             " was not found with given depth " << (int) m_depth << endl;
    }
}
