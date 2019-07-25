#include "WebUtils.h"


string *WebUtils::get_page_links(string page, uint16_t &links_num) {
    Json::Reader reader;
    Json::Value obj;
    replace(page.begin(), page.end(), ' ', '_');

    {
        curlpp::Cleanup clean;
        curlpp::Easy r;
        r.setOpt(new curlpp::options::Url(wikipedia_url + page));

        std::ostringstream response;
        r.setOpt(new curlpp::options::WriteStream(&response));
        r.perform();

        reader.parse(response.str(), obj);
    }

    Json::Value &links = obj["parse"]["links"];

    string *str_links = new string[links.end() - links.begin()];

    cout << "requesting value for: " << page << ", number: " << links.end() - links.begin() << endl;

    links_num = 0;
    for (Json::ValueIterator i = links.begin(); i != links.end(); i++) {
        str_links[links_num] = (*i)["*"].asString();
        if (!WikipediaUtils::is_link_valid(str_links[links_num])) {
            continue;
        }
        links_num++;
    }

    return str_links;
}
