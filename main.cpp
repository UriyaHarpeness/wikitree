#include "node/Node.h"
#include "tree/Tree.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Usage: ./wikitree [source] [dest] [max depth]" << endl;
        return 0;
    }
    Tree tree;
    /*
     * Path search working examples:
     * "Israel" "Via Dolorosa", 4
     * "Magic", "Meat", 4
     * "Rabbit", "Dichotomy", 4
     * "Desk", "Crow", 4
     * "Misophonia", "Synesthesia", 4
     * "Cannabis", "France", 4
     * "Simba", "Rap", 4
     * "Korn", "Slipknot (band)", 3
     * "Pillow", "Cyan", 4
     * "Ukulele", "Professor", 3
     */
    tree.find_path(argv[1], argv[2], atoi(argv[3]));
    //todo: one thread to resolve links (maybe even read files) and another for managment
    //todo: compare performance with AVL tree, regular tree, and vector
    //todo: allocate nodes in advance in multiplies of 1000 and increase when needed
    //todo: improve types, like using const, references and stuff to prevent unnecessary copies
    //todo: consider using one thread requests get from wikipedia, other arranges and mines more
    tree.print_solution();
    tree.find_path("Misophonia", "Synesthesia", 4);
    tree.print_solution();
    //tree.save();

    return 0;
}
