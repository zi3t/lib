# Header-only Data Structures Library

This repository contains a collection of C++ data structure implementations.
All components are provided as header files so they can be used without
building separate libraries.  The project includes lists, stacks, queues,
heaps, trees, graphs and various utility classes intended for teaching or
experimentation.

## Building and running the tests

The unit tests are driven by `tests.cpp`.  Compile them with g++ and then run
the resulting executable:

```bash
g++ -std=c++20 -I. tests.cpp -o tests && ./tests
```

## Continuous integration

A GitHub Actions workflow in `.github/workflows/test.yml` automatically builds
and runs the tests on every push and pull request to the `main` branch.
