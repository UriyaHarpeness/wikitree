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
    tree.find_path("Finger food", "Pepper", 1);
    //tree.find_path("Pizza", "Pepper", 2);
    tree.save();

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