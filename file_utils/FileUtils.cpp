#include "FileUtils.h"

bool FileUtils::exists(string filename) {
    struct stat buf;
    return (stat((saved_pages + filename + bz2).c_str(), &buf) != -1);
}

void FileUtils::write_and_compress(string filename, string *&content, uint16_t lines) {
    //todo: maybe more error checking, throughout even maybe
    ifstream infile;
    FILE *bz2File;
    int bzerror;
    string changeable;
    const int BLOCK_MULTIPLIER = 9;
    BZFILE *bzfile;

    cout << "writing values for: " << filename << ", number: " << lines << endl;

    //todo: this is only for linux, perhaps make this whole code work on windows as well, like if curl would compile there
    bz2File = fopen((saved_pages + filename + bz2).c_str(), "wb");
    bzfile = BZ2_bzWriteOpen(&bzerror, bz2File, BLOCK_MULTIPLIER, 0, 0);

    changeable = to_string(lines) + '\n';
    BZ2_bzWrite(&bzerror, bzfile, const_cast<char *>(changeable.c_str()), changeable.length());

    for (uint16_t i = 0; i < lines; i++) {
        changeable = content[i] + '\n';
        // this is dangerous, we only use const_cast because we will no longer use the content and assume it's the same
        BZ2_bzWrite(&bzerror, bzfile, const_cast<char *>(changeable.c_str()), changeable.length());
    }

    BZ2_bzWriteClose(&bzerror, bzfile, 0, nullptr, nullptr);
}

string *FileUtils::read_and_decompress(const string &filename, uint16_t &lines) {
    int bzError;
    BZFILE *bzfile;
    char buffer[4096];
    FILE *bz2file;
    string content;
    string::iterator it, newline_pos;
    string *str_links;

    bz2file = fopen((saved_pages + filename + bz2).c_str(), "rb");

    bzfile = BZ2_bzReadOpen(&bzError, bz2file, 0, 0, NULL, 0);

    while (bzError == BZ_OK) {
        int nread = BZ2_bzRead(&bzError, bzfile, buffer, 4096);
        if (bzError == BZ_OK || bzError == BZ_STREAM_END) {
            content.append(buffer, nread);
        }
    }

    newline_pos = find(content.begin(), content.end(), '\n');
    lines = atoi(string(content.begin(), newline_pos).c_str());

    cout << "reading values for: " << filename << ", number: " << lines << endl;

    str_links = new string[lines];
    for (uint16_t i = 0; i < lines; i++) {
        it = newline_pos + 1;
        newline_pos = find(it, content.end(), '\n');
        str_links[i] = string(it, newline_pos);
    }

    BZ2_bzReadClose(&bzError, bzfile);
    return move(str_links);
}
