#include "node/Node.h"
#include "tree/Tree.h"

#include <string>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;


int main() {
    //think about one thread requests get from wikipedia, other arranges and mines more

    string enc = "(A-Za-z )";
    cout << enc << " " << enc.length() << " " << WikipediaUtils::is_link_valid(enc) << endl;
    string s = WikipediaUtils::encode_link(enc);
    cout << s << " " << s.length() << endl;
    s = WikipediaUtils::decode_link(s);
    cout << s << " " << s.length() << endl;
    cout << (enc == s) << endl;

    //return 0;

    Tree tree;
    // Israel -> Jerusalem -> Muslim_Quarter
    // Israel -> Jerusalem -> Muslim_Quarter -> Via_Dolorosa
    // Via Dolorosa <- Crucifixion darkness <- Historicity of the Bible <- Israel
    // it found another path!!
    //Node *solution = tree.find_path("Israel", "Via Dolorosa", 3);
    //Node *solution = tree.find_path("Magic", "Meat", 4);
    //Node *solution = tree.find_path("Rabbit", "Dichotomy", 4);
    //Node *solution = tree.find_path("Desk", "Crow", 4);
    //Node *solution = tree.find_path("Misophonia", "Synesthesia", 4);
    //Node *solution = tree.find_path("Cannabis", "France", 4);
    //Node *solution = tree.find_path("Simba", "Rap", 4);
    //Node *solution = tree.find_path("Korn", "Slipknot", 4); // for sped test use values that doesn't exist
    Node *solution = tree.find_path("A", "Crow", 1);
    //before:
    // after going through 16876 pages, which took 1 seconds, the path is:
    // Synesthesia <- Somnolence <- Hepatitis <- Addiction medicine <- Misophonia
    //now:
    // after going through 128 pages, which took 0 seconds, the path is:
    // Synesthesia <- Misophonia
    //todo: increase depth when not found, until given limit
    //todo: one thread to resolve links (maybe even read files) and another for managment
    //todo: case insensitivity and space/underscore handling
    //todo: delete last depth leafs, because no longer processing
    //todo: when more characters are supported, update the saved_pages
    //todo: compare performance with AVL tree, regular tree, and vector
    //todo: allocate nodes in advance in multiplies of 1000 and increase when needed
    //todo: make sure im not overriding some string stuff when packing, and all bits are where they're supposed to be
    tree.print_solution();
    //tree.save();

    //getchar();

    return 0;
}