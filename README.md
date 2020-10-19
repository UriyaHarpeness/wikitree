# Wikitree

Welcome to Wikitree!

Have you ever wondered what's the link between Magic and Meat? Between Rabbit and Dichotomy, Ukulele and Professor,
Simba and Rap? - Well now you can find out.

## Getting Started

First off clone this project, after that you'll need to install a couple of requirements, and than you'll only need to
build it and enjoy the ride.

### Prerequisites

The packages required for building the project are:
gcc, cmake, libcurl4-openssl-dev, libcurlpp-dev, libjsoncpp-dev, libbz2-dev.
```
apt install gcc cmake libcurl4-openssl-dev libcurlpp-dev libjsoncpp-dev libbz2-dev
```

### Configuring
* Number of threads used for resolving and retry limit for [Wikipedia's API](https://en.wikipedia.org/w/api.php) and be
configured [here](config.h).
* Logging can be configured [here](debug.h).

### Building

After installing all the requirements, building the project is as straight-forward as it can be.

```
cmake .
make
```

That's it!

### Usage

Wikitree takes 3 positional arguments: `source`, `dest` and `max depth`.
* `source` is where to start the search from.
* `dest` is what we search for.
* `max depth` is the maximum search depth.

### Test Run

Now try using Wikitree, take it for a test run, for example:

```text
>>> ./wikitree Ukulele Professor 3

wikitree's find_path started, searching the path between Ukulele and Professor with given depth 3
current node count at: 1, resolving depth: 3, seconds count so far: 0
current node count at: 150, resolving depth: 2, seconds count so far: 1
current node count at: 30637, resolving depth: 1, seconds count so far: 17
current node count at 32768 and counting
current node count at 65536 and counting
current node count at 98304 and counting
current node count at 131072 and counting
after going through 131796 pages, which took 87 seconds, the path is:
Professor <- Charles William Eliot <- Phonofilm <- Ukulele
```

Second run:

```text
>>> ./wikitree Ukulele Professor 3

current node count at: 150, resolving depth: 2, seconds count so far: 0
current node count at: 23738, resolving depth: 1, seconds count so far: 0
current node count at 32768 and counting
current node count at 65536 and counting
current node count at 98304 and counting
after going through 109046 pages, which took 2 seconds, the path is:
Professor <- Charles William Eliot <- Phonofilm <- Ukulele
```

## Technologies and Capabilities

* Wikitree is written in [C++](https://en.wikipedia.org/wiki/CPP). 
* Uses [Wikipedia's API](https://en.wikipedia.org/w/api.php) to retrieve the links of a page.
* Implements an AVL tree to keep the pages and their links, for fast searching.
* Implements a packing and unpacking logic for strings for smaller storage.
* Implements zipped caching of pages links, making similar pages resolving much faster.
* Supports run with multiple threads for resolving links from Wikipedia faster.
* Guarantees shortest path between the pages, by using relative depth.
* Supports multiple levels of logging.

## Documentation

The code is thoroughly documented, using
[LSST DM Developer Guide](https://developer.lsst.io/cpp/api-docs.html#documenting-c-code) format.

I hope that it can answer whichever questions that may arise.

## Contributing

Feel free to contact me if you have any comments, questions, ideas, and anything else you think I should be aware of.
Also, tell me what crazy connections you have found using Wikitree, I'd love to know.

## Authors

* [**Uriya Harpeness**](https://github.com/UriyaHarpeness)

## Acknowledgments

* I would like to thank my wife - Tohar Harpeness, my parents, my computer, and my free time, for enabling me to work on
this small project, it has been fun.
