cmake_minimum_required(VERSION 3.13.4)
project(wikitree)

set(CMAKE_CXX_STANDARD 14)


add_executable(wikitree
        main.cpp
        node/Node.cpp
        node/Node.h
        tree/Tree.cpp
        tree/Tree.h
        web_utils/WebUtils.cpp
        web_utils/WebUtils.h
        file_utils/FileUtils.cpp
        file_utils/FileUtils.h
        wikipedia_utils/WikipediaUtils.cpp
        wikipedia_utils/WikipediaUtils.h
        links_resolver/LinksResolver.cpp
        links_resolver/LinksResolver.h
        config.h
        debug.h)

add_custom_target(create-saved-pages-folder
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/saved_pages)

add_dependencies(wikitree create-saved-pages-folder)

target_link_libraries(wikitree curl)
target_link_libraries(wikitree jsoncpp)
target_link_libraries(wikitree curlpp)
target_link_libraries(wikitree bz2)
target_link_libraries(wikitree pthread)
