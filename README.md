# My\_Container Project

### Author: Amit Nachum

**Institution**: Ariel University
**Mail**:nachum.amit@ariel.ac.il

---

## Overview

**My\_Container** is a custom C++ templated container that mimics standard container behavior while introducing advanced iterator patterns for educational and practical purposes. The goal of this project is to enhance understanding of C++ iterators, template programming, and custom container design.

This project includes:

* A generic container class: `My_Container<T>`
* Multiple custom iterator classes with unique traversal logic:

  * `Ascending_Iterator`
  * `Descending_Iterator`
  * `Side_Cross_Order`
  * `Reverse_Iterator`
  * `Order_Iterator`
  * `Middle_Out_Iterator`

---

## Iterator Behaviors

* **Ascending\_Iterator**: Iterates over the container elements in ascending order.
* **Descending\_Iterator**: Iterates in descending order.
* **Side\_Cross\_Order**: Alternates from the smallest to the largest side (e.g. left, right, left...).
* **Reverse\_Iterator**: Traverses in reverse insertion order.
* **Order\_Iterator**: Iterates in the same order elements were inserted.
* **Middle\_Out\_Iterator**: Starts from the middle and alternates moving outward (center → left → right → ...).

---

## Features

* Safe bounds checking with `.at()` accessors.
* Manual memory management and no STL dependency for internal implementation.
* Full unit test coverage using **doctest** framework.

---

## Build & Test

```bash
make           # Builds the main executable
make test      # Builds and runs all tests with doctest
make clean     # Cleans object files and binaries
```

To run valgrind on tests:

```bash
make test-valgrind
```

---

## File Structure

```
├── my_container.hpp     # Header file with all class/iterator declarations
├── main.cpp             # Demo program to showcase the container & iterators
├── tests/
│   └── test_container.cpp  # Full test suite using doctest
├── makefile             # Build system
└── README.md            # Project description
```

---

## Notes

* Special care is taken to handle both **even** and **odd** sized containers.
* `Middle_Out_Iterator` is NOT sorted intentionally (works on raw insertion order).
* Print utility (`print_iterator`) supports standard for-loops with comma formatting.

---

##
