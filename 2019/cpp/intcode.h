#ifndef intcode_h
#include <vector>

namespace intcode{
int run(std::vector<int> n, std::vector<int> inputs);
int run(std::vector<int> n, int input = 1);
}
#endif