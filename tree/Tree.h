#pragma once

#include "../node/Node.h"
#include "../links_resolver/LinksResolver.h"

#include <string>
#include <ctime>
#include <mutex>

using namespace std;

class Node;

class LinksResolver;

/**
 * This class is an implementation of an AVL tree, this data type for storing the links was chosen due to its small
 * complexity in searching for a value, which happens the most in this project. the AVL tree's height in the worst case
 * is 1.44*lg(n), in contrast to an unbalanced binary search tree.
 */
class Tree {
public:

    /**
     * Constructor.
     */
    Tree();

    /**
     * Destructor/
     */
    ~Tree();

    /**
     * Find a path of links between two given pages.
     *
     * Resolving the path is done in layers, the parameter `depth` defines the maximum number of layers, the first layer
     * is finding all the links in the page `source` (layer here is `depth`), the second layer is finding all the links
     * in the links we found earlier in the page `source` (layer here is `depth - 1`), this is node until the maximum
     * depth is reached or if the page `dest` was found in the process, in which case the `dest` page node is returned,
     * if the page was not found, a `nullptr` is returned.
     *
     * @param source    The page to start the search from.
     * @param dest      The page to be seeked.
     * @param depth     The maximum depth of the search, depth of 1 means getting the links in `source`, 2 means those
     *                  links' links, and so on.
     * @return  The `dest` page's node if such was found, `nullptr` otherwise.
     */
    Node *find_path(string source, string dest, uint8_t depth);

    /**
     * Insert a page to the tree.
     *
     * A corresponding node is created if `page` didn't already exists in the tree, later on calls to `update_height`
     * and `rebalance` are invoked, in order to balance the tree if an insertion has been made.
     * This function runs once at a time, this simplifies using threads, and drastically lowers the size in memory.
     *
     * @param page      The page to insert a corresponding node of to the tree.
     * @param source    The node from whose page this `page` was found.
     */
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
     * Calls the different rotation functions according the node's and its children's balance.
     *
     * @warning It is strongly recommended not to try and change any code in the rotation functions, the work with
     *          several layers of pointers is a source of terribly-hard-to-fix bugs which will may appear later on.
     * @param   node    The unbalanced node that needs rotation.
     */
    void rebalance(Node *node);

    /**
     * Perform a right rotation on the given node.
     *
     * For example:
     *       A             B
     *        \          /  \
     *         B   =>   A    C
     *          \
     *           C
     *
     * @param node  The node to rotate, in the example, `node` is `A`.
     */
    void rotate_rr(Node *node);

    /**
     * Perform a right-left rotation on the given node.
     *
     * For example:
     *       A             B
     *        \          /  \
     *         C   =>   A    C
     *        /
     *       B
     *
     * @param node  The node to rotate, in the example, `node` is `B`.
     */
    void rotate_rl(Node *node);

    /**
     * Perform a left-right rotation on the given node.
     *
     * For example:
     *       C             B
     *     /             /  \
     *    A        =>   A    C
     *     \
     *      B
     *
     * @param node  The node to rotate, in the example, `node` is `C`.
     */
    void rotate_lr(Node *node);

    /**
     * Perform a left rotation on the given node.
     *
     * For example:
     *       C            B
     *     /            /  \
     *    B       =>   A    C
     *  /
     * A
     *
     * @param node  The node to rotate, in the example, `node` is `C`.
     */
    void rotate_ll(Node *node);

    /**
     * Print the solution as a result of `find_path`.
     *
     * Prints various data like how much time it took to find the path, the path that was found and if it really has
     * been found, the number of nodes in the tree etc.
     */
    void print_solution();

    /// Was `m_dest` found, denotes if `find_path` was successful, used for stopping the search.
    bool m_found{};

    /// The LinksResolver for Nodes to use, enables using multi-threading for resolving pages' links.
    LinksResolver *m_links_resolver;


private:

    /// The page from which the search begins, this value is packed.
    string m_source;

    /// The page that needs to be found, this value is packed.
    string m_dest;

    /// The root of the AVL tree, may change at run time because of rotations.
    Node *m_root{};

    /// The number of nodes in the tree.
    uint64_t m_nodes{};

    /// The node that corresponds to `m_dest`, meaning that from it you can trace the path between `m_source` and
    /// `m_dest`.
    Node *m_path{};

    /// The maximum depth to search for the page.
    uint8_t m_depth{};

    /// The start time of the search, in seconds, since epoch.
    time_t m_start{};

    /// The finish time of the search, in seconds, since epoch.
    time_t m_finish{};

    /// A mutex to insure only one node is inserted at a time.
    mutex m_insertion_lock{};
};
