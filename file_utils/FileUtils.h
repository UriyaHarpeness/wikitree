#pragma once

#include <string>
#include <bzlib.h>
#include <fstream>
#include <sys/stat.h>
#include <algorithm>
#include <iostream>

using namespace std;

namespace FileUtils {
    static const string saved_pages = "saved_pages/";
    static string bz2 = ".bz2";

    bool exists(string filename);

    void write_and_compress(string filename, string *&content, uint16_t lines);

    string *read_and_decompress(const string &filename, uint16_t &lines);
}
