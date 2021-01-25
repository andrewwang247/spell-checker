/*
Compute Levenshtein distance between 2 strings.
See https://en.wikipedia.org/wiki/Levenshtein_distance

Copyright 2021. Siwei Wang.
*/
#include "levenshtein.h"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>
using std::distance;
using std::iota;
using std::min;
using std::string;
using std::swap;
using std::vector;

size_t levenshtein(const string& lhs, const string& rhs) {
  vector<size_t> vec_0(rhs.length() + 1);
  vector<size_t> vec_1(rhs.length() + 1);
  iota(vec_0.begin(), vec_0.end(), 0);
  for (size_t i = 0; i < lhs.size(); ++i) {
    vec_1.front() = i + 1;
    for (size_t j = 0; j < rhs.size(); ++j) {
      const auto del_cost = vec_0[j + 1] + 1;
      const auto ins_cost = vec_1[j] + 1;
      const auto sub_cost = (lhs[i] == rhs[j] ? vec_0[j] : vec_0[j] + 1);
      vec_1[j + 1] = min({del_cost, ins_cost, sub_cost});
    }
    swap(vec_0, vec_1);
  }
  return vec_0.back();
}

edit_t edit_distances(sound_t::const_iterator begin,
                      sound_t::const_iterator end, const string& word) {
  edit_t lev;
  lev.reserve(distance(begin, end));
  for (auto it = begin; it != end; ++it) {
    lev.emplace(it->second, levenshtein(word, it->second));
  }
  return lev;
}
