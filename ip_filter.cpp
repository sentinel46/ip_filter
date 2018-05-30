#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "filter.h"

int main(int argc, char const *argv[])
{
    try {
        std::vector<ipvec> ip_pool;

        for(std::string line; std::getline(std::cin, line);) {
            auto v = line.substr(0, line.find_first_of('\t'));
            ip_pool.push_back(split(v, '.'));
        }

        process(ip_pool);
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
