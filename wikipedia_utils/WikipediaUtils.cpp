#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
// This disables a warning about bitwise operations and signed values, the code's well aware that these values are
// signed, but in the output format this does not matter.

#include "WikipediaUtils.h"


string *WikipediaUtils::get_page_links(const string &page, uint16_t &links_num) {
    string *links;

    if (FileUtils::exists(page)) {
        links = FileUtils::read_and_decompress(page, links_num);
    } else {
        links = WebUtils::get_page_links(page, links_num);
        FileUtils::write_and_compress(page, links, links_num);
    }
    for (uint16_t i = 0; i < links_num; i++) {
        links[i] = pack_link(move(links[i]));
    }
    return links;
}

bool WikipediaUtils::is_link_valid(const string &link) {
    for (const char &it : link) {
        if (!(isalpha(it) || it == ' ' || it == '(' || it == ')' || it == '-' || it == ',' || it == '&' ||
              it == '\''))
            return false;
    }
    return true;
}

string WikipediaUtils::pack_link(const string &link) {
    string encoded_link(ceil(link.length() * 6.0 / 8.0), 0);
    uint16_t bits_offset = 0;
    uint16_t char_offset;
    uint16_t encoded_char = 0;
    size_t i = 0;

    for (; i < link.length(); i++) {
        bits_offset = (i * 6) & 0b111u;
        char_offset = (i * 6) >> 3;
        if (islower(link[i])) {
            encoded_char = link[i] & 0b00011111u;
        } else if (isupper(link[i])) {
            encoded_char = 0b00100000u | (link[i] & 0b00011111u);
        } else if (link[i] == ' ') {
            encoded_char = 27;
        } else if ((link[i] == '(') or (link[i] == ')')) {
            encoded_char = 28 + link[i] - '(';
        } else if (link[i] == '-') {
            encoded_char = 30;
        } else if (link[i] == ',') {
            encoded_char = 31;
        } else if (link[i] == '&') {
            encoded_char = 32;
        } else if (link[i] == '\'') {
            encoded_char = 59;
        }
        encoded_link[char_offset] |= encoded_char << bits_offset;
        encoded_link[char_offset + 1] |= encoded_char >> (8 - bits_offset);
    }

    if (((i * 6) & 0b111u) == 2) {
        encoded_link[(i * 6) >> 3] |= 0b11111100u;
    }

    return encoded_link;
}

string WikipediaUtils::unpack_link(const string &link) {
    uint16_t link_size = floor((link.length()) * 8.0 / 6.0);
    if ((link[link.length() - 1] & 0b11111100u) == 0b11111100u) {
        link_size--;
    }
    string decoded_link(link_size, 0);
    uint16_t bits_offset;
    uint16_t char_offset;
    uint16_t encoded_char;

    for (size_t i = 0; i < link_size; i++) {
        encoded_char = 0;
        bits_offset = (i * 6) & 0b111u;
        char_offset = (i * 6) >> 3;
        encoded_char |= ((uint8_t)(link[char_offset] & 0b00111111u << bits_offset)) >> bits_offset;
        encoded_char |= (link[char_offset + 1] & 0b00111111u >> (8 - bits_offset)) << (8 - bits_offset);
        if ((encoded_char >= 1) && (encoded_char <= 26)) {
            decoded_link[i] = encoded_char | 0b01100000u;
        } else if ((encoded_char >= 33) && (encoded_char <= 58)) {
            decoded_link[i] = encoded_char ^ 0b01100000u;
        } else if (encoded_char == 27) {
            decoded_link[i] = ' ';
        } else if ((encoded_char == 28) or (encoded_char == 29)) {
            decoded_link[i] = encoded_char - 28 + '(';
        } else if (encoded_char == 30) {
            decoded_link[i] = '-';
        } else if (encoded_char == 31) {
            decoded_link[i] = ',';
        } else if (encoded_char == 32) {
            decoded_link[i] = '&';
        } else if (encoded_char == 59) {
            decoded_link[i] = '\'';
        }
    }

    return decoded_link;
}

#pragma clang diagnostic pop
