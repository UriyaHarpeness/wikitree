#pragma once

#include "../tree/Tree.h"
#include "../wikipedia_utils/WikipediaUtils.h"

#include <string>

using namespace std;

class Tree;

/**
 * Implementation of a node for use in an AVL tree.
 */
class Node {
public:

    /**
     * Constructor.
     *
     * @param page      The page that the node corresponds to.
     * @param parent    The parent of the node (which node is this node child of).
     * @param source    The page from which we got to this page.
     * @param depth     The resolving depth of the node.
     */
    Node(string page, Node *parent, const Node *source, const uint8_t depth);

    /**
     * Destructor.
     *
     * Needs implementation due to the dynamic allocation of the nodes, calls the destructor of its children.
     */
    ~Node();

    /**
     * Operator less than.
     *
     * Compares the member `m_page` of each of the nodes.
     *
     * @param other The node to compare with.
     * @return  Is the value of this node's page lower than the other's.
     */
    bool operator<(const Node &other);

    /**
     * Operator less than.
     *
     * Compares the member `m_page` this node's and the given string.
     *
     * @param other The string to compare with.
     * @return  Is the value of this node's page lower than `other`.
     */
    bool operator<(const string &other);

    /**
     * Operator greater than.
     *
     * Compares the member `m_page` of each of the nodes.
     *
     * @param other The node to compare with.
     * @return  Is the value of this node's page greater than the other's.
     */
    bool operator>(const Node &other);

    /**
     * Operator greater than.
     *
     * Compares the member `m_page` this node's and the given string.
     *
     * @param other The string to compare with.
     * @return  Is the value of this node's page higher than `other`.
     */
    bool operator>(const string &other);

    /**
     * Resolve the links that appear on the node's corresponding page.
     *
     * Gets the links that appear on the node's page and inserts them to the tree.
     */
    void resolve_links();

    /**
     * Resolve the links that appear on nodes with the given depth.
     *
     * Calls to `Node::resolve_links` of nodes which member's `m_depth` is equal to the given depth.
     *
     * @param depth The depth of nodes to resolve.
     */
    void resolve_links_by_depth(const uint8_t &depth);

    /**
     * Get the balance of the node.
     *
     * This equals to the difference in height of the node's children, right's height - left's height, so a positive
     * result is called "right heavy", and a negative result is "left heavy". 0 is a balanced node.
     * The result will be in the range of -2 <= result <= 2, since this is used in an AVL tree.
     *
     * @return  The balance of the node, will be in the range of -2 <= result <= 2.
     */
    int8_t get_balance();

    /**
     * Print a selection of the node's members, helps debugging.
     */
    void print();

    /**
     * Print the path of the nodes.
     *
     * This means printing the node's parent pages utils there is no parent, which creates an easy to understand
     * hierarchy of pages that lead from the source to this node.
     */
    void print_path();

    /// The tree which the nodes belongs to, needed for calling `Tree::insert` of new nodes for example.
    static Tree *m_tree;

    /// Class Tree accesses private members of the class Node, this is done in attempt to reduce latency in accessing
    /// these members in contrast for using getters.
    friend class Tree;


private:

    /// The source of this node, meaning the node from which page a link to this node's page was found.
    const Node *m_source;

    /// The node's corresponding page, this value is packed.
    string m_page;

    /// The node's left child.
    Node *m_left;

    /// The node's right child.
    Node *m_right;

    /// The node's parent, one level higher in the tree.
    Node *m_parent;

    /// The height of the node, this is a member of the class to avoid calling a recursion to iterate through the whole
    /// tree every time we check if a rebalance is needed. A small number, but in an AVL tree this should suffice.
    uint8_t m_height;

    /// The resolving depth of the node. Finding a page is done in levels, see `Tree::find_path`s documentation.
    /// @relatesalso Tree::find_path
    uint8_t m_depth;
};
