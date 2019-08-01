#pragma once

#include "../node/Node.h"

#include <string>
#include <ctime>

using namespace std;

class Node;

/**
 * This call is an implementation of an AVL tree, this data type for storing the links was chosen due to its small
 * complexity in searching for a value, which happens the most in this project. the AVL tree's height in the worst case
 * is 1.44*lg(n), in contrast to an unbalanced binary search tree.
 */
class Tree {
public:
    Tree();

    ~Tree();

    Node *find_path(string source, string dest, uint8_t depth);

    void insert(const string &page, Node *source);

    /**
     * Update the height of nodes that require updating above node.
     *
     * node is a new node that inserted to the tree, so the height of some nodes higher than it change, this updates
     * those nodes' height.
     *
     * @param   node    The new node that was inserted to the tree.
     * @return  An unbalanced node, as a result of the new node's insertion, returns nullptr if the tree is still
     *          balanced.
     */
    static Node *update_height(Node *node);

    /**
     * Rebalance the node by rotation.
     *
     * @warning It is strongly recommended not to try and change any code in the rotation functions, the work with
     *          several layers of pointers is a source of terribly-hard-to-fix bugs which will may appear later on.
     * @param   node    The unbalanced node that needs to rotate them accordingly.
     */
    void rebalance(Node *node);

    void rotate_rr(Node *node);

    void rotate_rl(Node *node);

    void rotate_lr(Node *node);

    void rotate_ll(Node *node);

    void save();

    void print_solution();


private:
    string m_source;
    string m_dest;
    Node *m_root;
    uint64_t m_nodes;
    bool m_found{};
    Node *m_path;
    uint8_t m_depth{};
    time_t m_start{};
    time_t m_finish{};
};
