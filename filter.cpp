#include "filter.h"

//#include <cassert>
//#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <fstream>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<int> split(const std::string &str, char d)
{
    std::vector<int> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(std::stoi(str.substr(start, stop - start)));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(std::stoi((str.substr(start))));

    return r;
}

void print_pool(const std::vector<std::vector<int>> &pool)
{
    for (auto ip = pool.cbegin(); ip != pool.cend(); ++ip)
    {
        for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

void process(const std::vector<std::vector<int>> &pool)
{
    try
    {
        // TODO reverse lexicographically sort
        auto ip_pool(pool);
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<std::vector<int>>());
        print_pool(ip_pool);
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        std::vector<std::vector<int>> ip_pool1;
        std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_pool1), [](std::vector<int> v){return v.at(0) == 1;});
        print_pool(ip_pool1);
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        std::vector<std::vector<int>> ip_pool2;
        std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_pool2), [](std::vector<int> v){return v.at(0) == 46 && v.at(1) == 70;});
        print_pool(ip_pool2);
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        std::vector<std::vector<int>> ip_pool3;
        std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_pool3), [](std::vector<int> v){return find(v.begin(), v.end(), 46) != v.end();});
        print_pool(ip_pool3);
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
