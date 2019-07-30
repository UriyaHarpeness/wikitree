#include "WikipediaUtils.h"


string *WikipediaUtils::get_page_links(const string &page, uint16_t &links_num) {
    //todo: improve types, like using const, references and stuff to prevent unnecessary copies
    string *l = new string[4];
    l[0] = "B";
    l[1] = "C";
    l[2] = "D";
    l[3] = "E";
    links_num = 4;
    return l;
    ////////////////
    if (FileUtils::exists(page)) {
        return FileUtils::read_and_decompress(page, links_num);
    } else {
        string *links = WebUtils::get_page_links(page, links_num);
        FileUtils::write_and_compress(page, links, links_num);
        return links;
    }
}

string WikipediaUtils::encode_link(string link) {
    string encoded_link(ceil(link.length() * 5.0 / 8.0), 0);
    uint16_t bits_offset;
    uint16_t char_offset;
    uint16_t encoded_char;

    //todo: when in use, check the comparision of values, does not have to be by ABC, but just working

    for (int i = 0; i < link.length(); i++) {
        bits_offset = (i * 5) % 8;
        char_offset = (i * 5) / 8;
        if (isalpha(link[i])) {
            encoded_char = tolower(link[i]) & 0b00011111;
        } else if (link[i] == ' ') {
            encoded_char = 27;
        } else if ((link[i] == '(') or (link[i] == ')')) {
            encoded_char = 28 + link[i] - '(';
        } else if (link[i] == '-') {
            encoded_char = 30;
        }
        //cout << link[i] << ": " << encoded_char << " " << char_offset << " " << bits_offset << endl;
        encoded_link[char_offset] |= encoded_char << bits_offset;
        encoded_link[char_offset + 1] |= encoded_char >> 8 - bits_offset;
    }

    uint8_t t;
    cout << encoded_link.length() * 8 << " bits: ";
    for (int j = 0; j < encoded_link.length() * 8; j++) {
        t = (encoded_link[j / 8] >> (j % 8));
        cout << t % 2;
    }
    cout << endl;

    return encoded_link;
}

string WikipediaUtils::decode_link(string link) {
    uint16_t link_size = floor((link.length()) * 8.0 / 5.0);
    string decoded_link(link_size, 0);
    uint16_t bits_offset;
    uint16_t char_offset;
    uint16_t encoded_char;

    for (int i = 0; i < link_size; i++) {
        encoded_char = 0;
        bits_offset = (i * 5) % 8;
        char_offset = (i * 5) / 8;
        encoded_char |= ((uint8_t) (link[char_offset] & 0b00011111 << bits_offset)) >> bits_offset;
        encoded_char |= (link[char_offset + 1] & 0b00011111 >> 8 - bits_offset) << (8 - bits_offset);
        if ((encoded_char >= 1) && (encoded_char <= 26)) {
            decoded_link[i] = encoded_char | 0b01100000;
        } else if (encoded_char == 27) {
            decoded_link[i] = ' ';
        } else if ((encoded_char == 28) or (encoded_char == 29)) {
            decoded_link[i] = encoded_char - 28 + '(';
        } else if (encoded_char == 30) {
            decoded_link[i] = '-';
        }
        //cout << link[i] << ": " << encoded_char << " " << char_offset << " " << bits_offset << endl;
    }

    return decoded_link;
}

bool WikipediaUtils::is_link_valid(string link) {
    for (string::iterator it = link.begin(); it != link.end(); it++) {
        //todo: support more characters
        if (!(isalpha(*it) || (*it) == ' ' || (*it) == '(' || (*it) == ')' || (*it) == '-')) return false;
    }
    return true;
}
