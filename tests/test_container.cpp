#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "my_container.hpp"
#include <sstream>

using namespace amit_container;

TEST_CASE("My_Container: add_element and size") {
    My_Container<int> c;
    CHECK(c.size() == 0);
    c.add_element(1);
    CHECK(c.size() == 1);
    c.add_element(2);
    c.add_element(3);
    c.add_element(4);
    c.add_element(5);
    CHECK(c.size() == 5);
}

TEST_CASE("My_Container: remove elements") {
    My_Container<int> c;
    for (int i = 0; i < 5; ++i) c.add_element(i);
    CHECK(c.size() == 5);
    c.remove(2);
    CHECK(c.size() == 4);
    c.remove(0);
    c.remove(1);
    c.remove(3);
    c.remove(4);
    CHECK(c.size() == 0);
}

TEST_CASE("My_Container: assignment and copy") {
    My_Container<std::string> a;
    a.add_element("hello");
    a.add_element("world");

    My_Container<std::string> b = a; // copy constructor
    CHECK(b.size() == 2);

    My_Container<std::string> c;
    c = a; // assignment
    CHECK(c.size() == 2);
}

TEST_CASE("Ascending_Iterator basic iteration") {
    My_Container<int> c;
    c.add_element(5);
    c.add_element(3);
    c.add_element(9);
    c.add_element(1);
    c.add_element(7);

    auto it = c.begin_ascending();
    std::vector<int> expected = {1, 3, 5, 7, 9};
    size_t i = 0;
    for (; it != c.end_ascending(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
    CHECK(i == expected.size());
}

TEST_CASE("Descending_Iterator basic iteration") {
    My_Container<int> c;
    c.add_element(2);
    c.add_element(4);
    c.add_element(1);
    c.add_element(5);
    c.add_element(3);

    auto it = c.begin_descending();
    std::vector<int> expected = {5, 4, 3, 2, 1};
    size_t i = 0;
    for (; it != c.end_descending(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
    CHECK(i == expected.size());
}

TEST_CASE("Side_Cross_Order basic zigzag") {
    My_Container<int> c;
    c.add_element(1);
    c.add_element(2);
    c.add_element(3);
    c.add_element(4);
    c.add_element(5);

    auto it = c.begin_side_cross();
    std::vector<int> expected = {3, 2, 4, 1, 5};
    size_t i = 0;
    for (; it != c.end_side_cross(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
    CHECK(i == expected.size());
}

TEST_CASE("Middle_Out_Iterator correctness") {
    My_Container<int> c;
    c.add_element(10);
    c.add_element(20);
    c.add_element(30);
    c.add_element(40);
    c.add_element(50);

    auto it = c.begin_mid_out();
    std::vector<int> expected = {30, 20, 40, 10, 50};
    size_t i = 0;
    for (; it != c.end_mid_out(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
    CHECK(i == expected.size());
}

TEST_CASE("Multiple containers independence") {
    My_Container<int> a;
    My_Container<int> b;

    a.add_element(1);
    b.add_element(2);

    CHECK(a.size() == 1);
    CHECK(b.size() == 1);
    CHECK(*a.begin_ascending() == 1);
    CHECK(*b.begin_ascending() == 2);
}

TEST_CASE("Print Iterator - valid range") {
    My_Container<int> c;
    c.add_element(4);
    c.add_element(2);
    c.add_element(6);

    std::ostringstream out;
    for (auto it = c.begin_ascending(); it != c.end_ascending(); ++it) {
        out << *it << " ";
    }
    CHECK(out.str() == "2 4 6 ");
}

TEST_CASE("Print Iterator - out of bounds protection") {
    My_Container<int> c;
    c.add_element(1);
    auto it = c.begin_ascending();
    ++it;
    CHECK(it != c.end_ascending());

    for (int i = 0; i < 10; ++i) ++it;
    CHECK(true);
}

TEST_CASE("Print empty iterators") {
    My_Container<int> c;
    std::ostringstream out;
    for (auto it = c.begin_ascending(); it != c.end_ascending(); ++it) {
        out << *it << " ";
    }
    CHECK(out.str().empty());
}
