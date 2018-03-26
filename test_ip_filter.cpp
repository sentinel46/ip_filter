#define BOOST_TEST_MODULE test_ip_filter

#include "filter.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_ip_filter)

BOOST_AUTO_TEST_CASE(test_split_function)
{
    ipvec result = {0};
    BOOST_CHECK(split("", '.') == result);

    result = {11};
    BOOST_CHECK(split("11", '.') == result);

    result = {0, 0, 0};
    BOOST_CHECK(split("..", '.') == result);

    result = {11, 0};
    BOOST_CHECK(split("11.", '.') == result);

    result = {0, 11};
    BOOST_CHECK(split(".11", '.') == result);

    result = {11, 22};
    BOOST_CHECK(split("11.22", '.') == result);
}

BOOST_AUTO_TEST_CASE(test_filter_function)
{
    std::vector<ipvec> test;
    BOOST_CHECK(filter(test, 1).empty());

    test.push_back(split("1.231.69.33", '.'));
    auto result = test;
    BOOST_CHECK(filter(test, -5).empty());
    BOOST_CHECK(filter(test, 300).empty());
    BOOST_CHECK(filter(test, 1) == result);
    BOOST_CHECK(filter(test, 5).empty());

    test.clear();
    test.push_back(split("1.231.69.33", '.'));
    test.push_back(split("1.87.203.225", '.'));
    test.push_back(split("1.70.44.170", '.'));
    test.push_back(split("1.29.168.152", '.'));
    test.push_back(split("1.1.234.8", '.'));
    test.push_back(split("46.70.225.39", '.'));
    test.push_back(split("46.70.147.26", '.'));
    test.push_back(split("46.70.113.73", '.'));
    test.push_back(split("46.70.29.76", '.'));
    result.clear();
    result.push_back(split("1.231.69.33", '.'));
    result.push_back(split("1.87.203.225", '.'));
    result.push_back(split("1.70.44.170", '.'));
    result.push_back(split("1.29.168.152", '.'));
    result.push_back(split("1.1.234.8", '.'));
    BOOST_CHECK(filter(test, 1) == result);
}

BOOST_AUTO_TEST_CASE(test_filter2_function)
{
    std::vector<ipvec> test;
    BOOST_CHECK(filter(test, 1, 1).empty());

    test.push_back(split("1.231.69.33", '.'));
    auto result = test;
    BOOST_CHECK(filter(test, -5, 300).empty());
    BOOST_CHECK(filter(test, 1, 231) == result);
    BOOST_CHECK(filter(test, 5, 231).empty());
    BOOST_CHECK(filter(test, 1, 300).empty());

    test.clear();
    test.push_back(split("1.231.69.33", '.'));
    test.push_back(split("1.87.203.225", '.'));
    test.push_back(split("1.70.44.170", '.'));
    test.push_back(split("1.29.168.152", '.'));
    test.push_back(split("1.1.234.8", '.'));
    test.push_back(split("46.70.225.39", '.'));
    test.push_back(split("46.70.147.26", '.'));
    test.push_back(split("46.70.113.73", '.'));
    test.push_back(split("46.70.29.76", '.'));
    result.clear();
    result.push_back(split("46.70.225.39", '.'));
    result.push_back(split("46.70.147.26", '.'));
    result.push_back(split("46.70.113.73", '.'));
    result.push_back(split("46.70.29.76", '.'));
    BOOST_CHECK(filter(test, 46, 70) == result);
}

BOOST_AUTO_TEST_CASE(test_filter_any_function)
{
    std::vector<ipvec> test;
    BOOST_CHECK(filter_any(test, 1).empty());

    test.push_back(split("1.231.69.33", '.'));
    auto result = test;
    BOOST_CHECK(filter_any(test, -5).empty());
    BOOST_CHECK(filter_any(test, 69) == result);
    BOOST_CHECK(filter_any(test, 70).empty());

    test.clear();
    test.push_back(split("186.204.34.46", '.'));
    test.push_back(split("186.46.222.194", '.'));
    test.push_back(split("1.70.44.170", '.'));
    test.push_back(split("1.29.168.152", '.'));
    test.push_back(split("1.1.234.8", '.'));
    test.push_back(split("46.70.225.39", '.'));
    test.push_back(split("58.161.46.202", '.'));
    result.clear();
    result.push_back(split("186.204.34.46", '.'));
    result.push_back(split("186.46.222.194", '.'));
    result.push_back(split("46.70.225.39", '.'));
    result.push_back(split("58.161.46.202", '.'));
    BOOST_CHECK(filter_any(test, 46) == result);
}

BOOST_AUTO_TEST_SUITE_END()
