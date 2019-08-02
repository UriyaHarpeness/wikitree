#pragma once

#include <string>
#include <bzlib.h>
#include <fstream>
#include <sys/stat.h>
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * A namespace for all file system related utilities.
 */
namespace FileUtils {
    /// The folder prefix where the pages are saved.
    static const string saved_pages = "saved_pages/";

    /// The file suffix of saved pages.
    static const string bz2 = ".bz2";

    /**
     * Check if a file exists.
     *
     * Adds the saved_pages prefix and the .bz2 suffix to the given filename and checks its existence.
     *
     * @param filename  The base name of the file to check if exists.
     * @return  Does the file exist.
     */
    bool exists(const string &filename);

    /**
     * Write the given lines to a file in a compressed format.
     *
     * Adds the saved_pages prefix and the .bz2 suffix to `filename` and writes into it.
     *
     * @param filename  The base name of the file to write into.
     * @param lines     The lines to write to the file (will be in different line each).
     * @param lines_num The number of lines.
     */
    void write_and_compress(const string &filename, string *&lines, uint16_t lines_num);

    /**
     * Read and decompress the content of the given file.
     *
     * Adds the saved_pages prefix and the .bz2 suffix to `filename` and reads from it.
     *
     * @param filename          The base name of the file to read from.
     * @param[out] lines_num    The number of lines read from the file.
     * @return  The lines read from the file.
     */
    string *read_and_decompress(const string &filename, uint16_t &lines_num);
}
