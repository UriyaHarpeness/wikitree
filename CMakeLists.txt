cmake_minimum_required(VERSION 3.14)
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
        wikipedia_utils/WikipediaUtils.h)

target_link_libraries(wikitree curl)
target_link_libraries(wikitree jsoncpp)
target_link_libraries(wikitree curlpp)
target_link_libraries(wikitree bz2)
