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

namespace WebUtils {
    const string wikipedia_url = "https://en.wikipedia.org/w/api.php?action=parse&prop=links&format=json&page=";

    string *get_page_links(string page, uint16_t &links_num);
}
