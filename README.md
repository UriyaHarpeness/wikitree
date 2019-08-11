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

### Building

After installing all the requirements, building the project is as straight-forward as it can be.

```
cmake .
make
```

That's it!

### Test Run

Now try using Wikitree, take it for a test run, for example:

```
./wikitree Korn "Slipknot (band)" 3
```

Wikitree takes 3 arguments: `source`, `dest` and `max depth`.
* `source` is where to start the search from,
* `dest` is what we search for.
* `max depth` is the maximum search depth.
* If you have any questions please review the code's comments, these should suffice.

## Contributing

Feel free to contact me if you have any comments, questions, ideas, and anything else you think I should be aware of.
Also, tell me what crazy connections you have found using Wikitree, I'd love to know.

## Authors

* [**Uriya Harpeness**](https://github.com/UriyaHarpeness)

## Acknowledgments

* I would like to thank my wife - Tohar Harpeness, my parents, my computer, and my free time, for enabling me to work on
this small project, it has been fun.
