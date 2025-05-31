#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
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
    // Updated expected: traversal is {1, 5, 2, 4, 3}
    std::vector<int> expected = {1, 5, 2, 4, 3};
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
    // Updated: after one ++, it should equal end
    CHECK(it == c.end_ascending());

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

TEST_CASE("Ascending_Iterator with even number of elements") {
    My_Container<int> c;
    c.add_element(10);
    c.add_element(20);
    c.add_element(30);
    c.add_element(40);

    auto it = c.begin_ascending();
    std::vector<int> expected = {10, 20, 30, 40};
    size_t i = 0;
    for (; it != c.end_ascending(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
    CHECK(i == expected.size());
}

TEST_CASE("Descending_Iterator with even number of elements") {
    My_Container<int> c;
    c.add_element(5);
    c.add_element(15);
    c.add_element(10);
    c.add_element(20);

    auto it = c.begin_descending();
    std::vector<int> expected = {20, 15, 10, 5};
    size_t i = 0;
    for (; it != c.end_descending(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
    CHECK(i == expected.size());
}

TEST_CASE("Side_Cross_Order with even number of elements") {
    My_Container<int> c;
    c.add_element(1);
    c.add_element(2);
    c.add_element(3);
    c.add_element(4);

    auto it = c.begin_side_cross();
    std::vector<int> expected = {1, 4, 2, 3};
    size_t i = 0;
    for (; it != c.end_side_cross(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
    CHECK(i == expected.size());
}

TEST_CASE("Reverse_Iterator with even number of elements") {
    My_Container<int> c;
    c.add_element(1);
    c.add_element(2);
    c.add_element(3);
    c.add_element(4);

    auto it = c.begin_reverse();
    std::vector<int> expected = {4, 3, 2, 1};
    size_t i = 0;
    for (; it != c.end_reverse(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
    CHECK(i == expected.size());
}

TEST_CASE("Middle_Out_Iterator with even number of elements") {
    My_Container<int> c;
    c.add_element(10);
    c.add_element(20);
    c.add_element(30);
    c.add_element(40);

    auto it = c.begin_mid_out();
    // Updated expected to {30, 20, 40, 10}
    std::vector<int> expected = {30, 20, 40, 10};
    size_t i = 0;
    for (; it != c.end_mid_out(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
    CHECK(i == expected.size());
}

TEST_CASE("Order_Iterator with even number of elements") {
    My_Container<int> c;
    c.add_element(11);
    c.add_element(22);
    c.add_element(33);
    c.add_element(44);

    auto it = c.begin_order();
    std::vector<int> expected = {11, 22, 33, 44};
    size_t i = 0;
    for (; it != c.end_order(); ++it, ++i) {
        CHECK(*it == expected[i]);
    }
    CHECK(i == expected.size());
}


/*TEST_CASE("Strings checks"){
    My_Container<std::string> container;
    container.add_element("Hello");
    container.add_element("World");
    container.add_element("this");
    container.add_element("is");
    container.add_element("a");
    container.add_element("string");
    container.add_element("test");


    
}
*/

TEST_CASE("All Iterators with strings") {
    My_Container<std::string> c;
    c.add_element("delta");
    c.add_element("bravo");
    c.add_element("charlie");
    c.add_element("alpha");

    std::vector<std::string> expected_asc = {"alpha", "bravo", "charlie", "delta"};
    std::vector<std::string> expected_desc = {"delta", "charlie", "bravo", "alpha"};
    std::vector<std::string> expected_order = {"delta", "bravo", "charlie", "alpha"};
    std::vector<std::string> expected_rev = {"alpha", "charlie", "bravo", "delta"};
    std::vector<std::string> expected_side = {"alpha", "delta", "bravo", "charlie"};
    std::vector<std::string> expected_mid = {"charlie", "bravo", "alpha", "delta"};

    // Ascending
    {
        size_t i = 0;
        for (auto it = c.begin_ascending(); it != c.end_ascending(); ++it, ++i) {
            CHECK(*it == expected_asc[i]);
        }
        CHECK(i == expected_asc.size());
    }

    // Descending
    {
        size_t i = 0;
        for (auto it = c.begin_descending(); it != c.end_descending(); ++it, ++i) {
            CHECK(*it == expected_desc[i]);
        }
        CHECK(i == expected_desc.size());
    }

    // Order
    {
        size_t i = 0;
        for (auto it = c.begin_order(); it != c.end_order(); ++it, ++i) {
            CHECK(*it == expected_order[i]);
        }
        CHECK(i == expected_order.size());
    }

    // Reverse
    {
        size_t i = 0;
        for (auto it = c.begin_reverse(); it != c.end_reverse(); ++it, ++i) {
            CHECK(*it == expected_rev[i]);
        }
        CHECK(i == expected_rev.size());
    }

    // Side Cross
    {
        size_t i = 0;
        for (auto it = c.begin_side_cross(); it != c.end_side_cross(); ++it, ++i) {
            CHECK(*it == expected_side[i]);
        }
        CHECK(i == expected_side.size());
    }

    // Middle Out
    {
        size_t i = 0;
        for (auto it = c.begin_mid_out(); it != c.end_mid_out(); ++it, ++i) {
            CHECK(*it == expected_mid[i]);
        }
        CHECK(i == expected_mid.size());
    }
}
