#pragma once

#include "../wikipedia_utils/WikipediaUtils.h"

#include <jsoncpp/json/json.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

/**
 * A namespace for all web related utilities.
 */
namespace WebUtils {
    /// The URL prefix to get the page's links from.
    static const string wikipedia_url = "https://en.wikipedia.org/w/api.php?action=parse&prop=links&format=json&page=";

    /**
     * Get the links from a given page.
     *
     * Uses Wikipedia's API to get the links in Json format from the page's name.
     *
     * @param page              The page to get links for.
     * @param[out] links_num    The number of links found in the page.
     * @return  The links found in the page.
     */
    string *get_page_links(string page, uint16_t &links_num);
}
