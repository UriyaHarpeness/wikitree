#include "tree/Tree.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Usage: ./wikitree [source] [dest] [max depth]" << endl;
        return 1;
    }
    string source(argv[1]), dest(argv[2]);
    int max_depth = atoi(argv[3]);
    if (source == dest) {
        cout << "[source] and [dest] can't be the same." << endl;
        return 1;
    }
    if (max_depth < 1) {
        cout << "[max depth] needs to be a number above 0." << endl;
        return 1;
    }

    //todo: compare performance with AVL tree, regular tree, and vector
    //todo: allocate nodes in advance in multiplies of 1000 and increase when needed
    //todo: improve types, like using const, references and stuff to prevent unnecessary copies
    //todo: maybe make that when packed links are compared it's the same result as unpacked

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
     * "Earth, Wind & Fire", "Coraline (film)", 4
     * This won't finish: Hair "Whiplash (2014 film)" 4
     */
    tree.find_path(source, dest, max_depth);
    tree.print_solution();

    return 0;
}
