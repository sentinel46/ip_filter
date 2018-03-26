#include "filter.h"

#include <cassert>
#include <iostream>
#include <algorithm>
#include <functional>
#include <fstream>

ipvec split(const std::string &str, char d)
{
    ipvec out;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        auto num = 0;
        try
        {
            num = std::stoi(str.substr(start, stop - start));
        }
        catch (...)
        {
            num = 0;
        }
        out.push_back(num);

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    auto num = 0;
    try
    {
        num = std::stoi((str.substr(start)));
    }
    catch (...)
    {
        num = 0;
    }
    out.push_back(num);

    return out;
}

void print_pool(const std::vector<ipvec> &pool)
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

std::vector<ipvec> filter(const std::vector<ipvec> &in, int n1)
{
    std::vector<ipvec> out;
    if (n1 >= 0 && n1 < 256)
        std::copy_if(in.cbegin(), in.cend(), std::back_inserter(out), [n1](ipvec v){return v.at(0) == n1;});
    return out;
}

std::vector<ipvec> filter(const std::vector<ipvec> &in, int n1, int n2)
{
    std::vector<ipvec> out;
    if (n1 >= 0 && n1 < 256 && n2 >= 0 && n2 < 256)
        std::copy_if(in.cbegin(), in.cend(), std::back_inserter(out), [n1, n2](ipvec v){return v.at(0) == n1 && v.at(1) == n2;});
    return out;
}

std::vector<ipvec> filter_any(const std::vector<ipvec> &in, int n)
{
    std::vector<ipvec> out;
    if (n >= 0 && n < 256)
        std::copy_if(in.cbegin(), in.cend(), std::back_inserter(out), [n](ipvec v){return find(v.cbegin(), v.cend(), n) != v.end();});
    return out;
}

void process(const std::vector<ipvec> &pool)
{
    try
    {
        auto ip_pool(pool);
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<ipvec>());
        print_pool(ip_pool);

        auto ip = filter(ip_pool, 1);
        print_pool(ip);

        ip = filter(ip_pool, 46, 70);
        print_pool(ip);

        ip = filter_any(ip_pool, 46);
        print_pool(ip);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
