#pragma once

#include "../file_utils/FileUtils.h"
#include "../web_utils/WebUtils.h"

#include <string>
#include <tgmath.h>

using namespace std;

namespace WikipediaUtils {
    string *get_page_links(const string &page, uint16_t &links_num);

    bool is_link_valid(string link);

    string encode_link(string link);

    string decode_link(string link);
}
