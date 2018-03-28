#include "filter.h"

#include <cassert>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
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
        catch (const std::invalid_argument &e)
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
    catch (const std::invalid_argument &e)
    {
        num = 0;
    }
    out.push_back(num);

    return out;
}

std::ostream& operator<<(std::ostream &os, ipvec &vec)
{
    for (auto v = vec.cbegin(); v != vec.cend(); ++v)
    {
        if (v != vec.cbegin())
            os << ".";
        os << *v;
    }
    os << std::endl;
}

void print_pool(const std::vector<ipvec> &pool)
{
    for (auto ip: pool)
        std::cout << ip;
}

std::vector<ipvec> filter(const std::vector<ipvec> &in, int n1)
{
    std::vector<ipvec> out;
    std::copy_if(std::cbegin(in), std::cend(in), std::back_inserter(out), [n1](ipvec v){return v.at(0) == n1;});
    return out;
}

std::vector<ipvec> filter(const std::vector<ipvec> &in, int n1, int n2)
{
    std::vector<ipvec> out;
    std::copy_if(std::cbegin(in), std::cend(in), std::back_inserter(out), [n1, n2](ipvec v){return v.at(0) == n1 && v.at(1) == n2;});
    return out;
}

std::vector<ipvec> filter_any(const std::vector<ipvec> &in, int n)
{
    std::vector<ipvec> out;
    std::copy_if(std::cbegin(in), std::cend(in), std::back_inserter(out), [n](ipvec v){return find(std::cbegin(v), std::cend(v), n) != std::cend(v);});
    return out;
}

void process(const std::vector<ipvec> &pool)
{
    auto ip_pool(pool);
    std::sort(std::begin(ip_pool), std::end(ip_pool), std::greater<ipvec>());
    print_pool(ip_pool);

    print_pool(filter(ip_pool, 1));
    print_pool(filter(ip_pool, 46, 70));
    print_pool(filter_any(ip_pool, 46));
}

std::vector<ipvec> process2(const std::vector<ipvec> &pool)
{
    auto ip_pool(pool);
    std::sort(std::begin(ip_pool), std::end(ip_pool), std::greater<ipvec>());
    auto out(ip_pool);
    std::copy_if(std::cbegin(ip_pool), std::cend(ip_pool), std::back_inserter(out), [](ipvec v){return v.at(0) == 1;});
    std::copy_if(std::cbegin(ip_pool), std::cend(ip_pool), std::back_inserter(out), [](ipvec v){return v.at(0) == 46 && v.at(1) == 70;});
    std::copy_if(std::cbegin(ip_pool), std::cend(ip_pool), std::back_inserter(out), [](ipvec v){return find(std::cbegin(v), std::cend(v), 46) != std::cend(v);});
    return out;
}

std::vector<ipvec> process3(const std::vector<ipvec> &pool)
{
    auto out1(pool);
    std::sort(std::begin(out1), std::end(out1), std::greater<ipvec>());
    std::vector<ipvec> out2;
    std::vector<ipvec> out3;
    std::vector<ipvec> out4;
    for (auto vec: out1)
    {
        if (vec.at(0) == 1)
            out2.push_back(vec);
        if (vec.at(0) == 46 && vec.at(1) == 70)
            out3.push_back(vec);
        if (find(std::cbegin(vec), std::cend(vec), 46) != std::cend(vec))
            out4.push_back(vec);
    }
    out1.insert(std::end(out1), std::begin(out2), std::end(out2));
    out1.insert(std::end(out1), std::begin(out3), std::end(out3));
    out1.insert(std::end(out1), std::begin(out4), std::end(out4));
    return out1;
}
