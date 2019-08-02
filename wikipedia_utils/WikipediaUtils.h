#pragma once

#include "../file_utils/FileUtils.h"
#include "../web_utils/WebUtils.h"

#include <string>
#include <ctgmath>

using namespace std;

/**
 * A namespace for interacting with Wikipedia (uses `FileUtils` and `WebUtils`).
 */
namespace WikipediaUtils {
    /**
     * Get the links for a given page.
     *
     * First checks if a file that corresponds to `page` exists, if so, reads its content with `FileUtils`, otherwise,
     * gets them using `WebUtils` and saves them with `FileUtils`. The slowest part in this project is requesting the
     * links from Wikipedia, so caching pages that are encountered saves later runs a lot of time.
     *
     * @param page              The page to get links for.
     * @param[out] links_num    The number of links in the page.
     * @return  The links in the page.
     */
    string *get_page_links(const string &page, uint16_t &links_num);

    /**
     * Check if the given link is valid.
     *
     * The characters that are currently supported are: 'A'-'Z', 'a'-'z', '-', ' ', '(', and ')'.
     *
     * @relatesalso pack_link
     * @param link  The link to check if all of its characters are valid, which means it can be packed.
     * @return  Is the link valid and therefore can be packed.
     */
    bool is_link_valid(const string &link);

    /**
     * Pack a given link.
     *
     * Wikipedia pages names do not contain all of the 2^8 characters in ascii, so packing is possible, in order to
     * reduce memory consumption. This currently saves space of 0.25 from the given link, for example: a link with
     * length of 12 will be reduced to a string of length 9, when saving many pages, the packing can make major
     * difference.
     *
     * @param link  The link to pack (assumed to be valid).
     * @return  The packed link.
     */
    string pack_link(string link);

    /**
     * Unpack a given link.
     *
     * @relatesalso pack_link
     * @param link  The link to unpack.
     * @return  The unpacked link.
     */
    string unpack_link(string link);
}
