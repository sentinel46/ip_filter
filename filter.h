#include <string>
#include <vector>
#include <iostream>

using ipvec = std::vector<int>;

ipvec split(const std::string &str, char d);
std::vector<ipvec> filter(const std::vector<ipvec> &in, int n1);
std::vector<ipvec> filter(const std::vector<ipvec> &in, int n1, int n2);
std::vector<ipvec> filter_any(const std::vector<ipvec> &in, int n);
void process(const std::vector<ipvec> &pool);
