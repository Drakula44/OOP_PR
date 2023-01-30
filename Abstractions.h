#ifndef abstractions_h
#define abstractions_h
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

using std::pair;
using std::string;
using std::variant;
using std::vector;

typedef vector<pair<string, vector<int>>> Route;

const vector<int> a;

using iter = std::variant<decltype(a.begin()), decltype(a.rbegin())>;

#endif