#include "WebUtils.h"


string *WebUtils::get_page_links(string page, uint16_t &links_num) {
    Json::Reader reader;
    Json::Value obj;
    uint8_t current_retry_count = retry_count;
    replace(page.begin(), page.end(), ' ', '_');
    for (size_t index = page.find('&', 0); index != string::npos; index = page.find('&', index)) {
        page.replace(index, 1, "%26");
    }
    {
        curlpp::Cleanup clean;
        curlpp::Easy r;
        r.setOpt(new curlpp::options::Url(wikipedia_url + page));

        ostringstream response;
        r.setOpt(new curlpp::options::WriteStream(&response));

        while (current_retry_count--) {
            try {
                r.perform();
                break;
            } catch (const curlpp::LibcurlRuntimeError &e) {
                // May occur when using multiple threads, or when the network is disconnected, so there's a retry count.
                if (!current_retry_count) {
                    throw e;
                }
            }
        }

        reader.parse(response.str(), obj);
    }

    Json::Value &links = obj["parse"]["links"];

    auto *str_links = new string[links.end() - links.begin()];

#if DEBUG_PAGES_RESOLVE
    cout << "requesting value for: " << page << ", number: " << links.end() - links.begin() << endl;
#endif // DEBUG_PAGES_RESOLVE

    links_num = 0;
    for (auto &link : links) {
        str_links[links_num] = link["*"].asString();
        if (!WikipediaUtils::is_link_valid(str_links[links_num])) {
            continue;
        }
        links_num++;
    }

    return str_links;
}
