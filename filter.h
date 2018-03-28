#ifndef FILTER_H
#define FILTER_H

#include <string>
#include <vector>
#include <tuple>
#include <iostream>

using ipvec = std::vector<int>;

ipvec split(const std::string &str, char d);
void print_pool(const std::vector<ipvec> &pool);
std::vector<ipvec> filter(const std::vector<ipvec> &in, int n1);
std::vector<ipvec> filter(const std::vector<ipvec> &in, int n1, int n2);
std::vector<ipvec> filter_any(const std::vector<ipvec> &in, int n);
void process(const std::vector<ipvec> &pool);
std::vector<ipvec> process2(const std::vector<ipvec> &pool);
std::vector<ipvec> process3(const std::vector<ipvec> &pool);

#endif // FILTER_H
