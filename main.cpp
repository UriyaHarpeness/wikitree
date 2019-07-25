#include "node/Node.h"
#include "tree/Tree.h"

#include <string>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;


int main() {
    //think about one thread requests get from wikipedia, other arranges and mines more

    /*string s = encode_link("abcdefghijklmnopqrstuvwxyz");
    cout << s << " " << s.length() << endl;
    s = decode_link(s);
    cout << s << " " << s.length() << endl;

    return 0;*/

    Tree tree;
<<<<<<< HEAD
    // Israel -> Jerusalem -> Muslim_Quarter
    // Israel -> Jerusalem -> Muslim_Quarter -> Via_Dolorosa
    // Via Dolorosa <- Crucifixion darkness <- Historicity of the Bible <- Israel
    // it found another path!!
    //Node *solution = tree.find_path("Israel", "Via Dolorosa", 3);
    //Node *solution = tree.find_path("Magic", "Meat", 4);
    //Node *solution = tree.find_path("Rabbit", "Dichotomy", 4);
    Node *solution = tree.find_path("Desk", "Crow", 4);
    //todo: increase depth when not found, until given limit
    //todo: one thread to resolve links (maybe even read files) and another for managment
    tree.print_solution();
    //tree.save();
=======
    tree.find_path("Finger food", "Pepper", 1);
    //tree.find_path("Pizza", "Pepper", 2);
    tree.save();
>>>>>>> 1df8cad... Working WIP, first commit after a considerebly long development, will improve.

    /*FileUtils::write_and_compress("a.txt", "even more??!?");
    system("cat saved_pages/a.txt");
    cout << FileUtils::read_and_decompress("a.txt") << endl;*/

    /*string *a = new string[2];
    a[0] = "some";
    a[1] = "stuff";
    FileUtils::write_and_compress("a.txt", a, 2);
    system("cat saved_pages/a.txt.bz2");
    cout << FileUtils::read_and_decompress("a.txt") << endl;

    cout << FileUtils::exists("a.txt") << endl;

    delete[] a;*/

    return 0;
}