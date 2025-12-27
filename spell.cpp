/*
Spell check words provided to stdin.

Copyright 2026. Andrew Wang.
*/
#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "levenshtein.h"
#include "soundex.h"
using std::any_of;
using std::cout;
using std::find_if;
using std::invalid_argument;
using std::ios_base;
using std::isalpha;
using std::sort;
using std::string;
using std::tolower;
using std::transform;
using std::vector;

// Name of the dictionary file.
static constexpr auto dict_name = "dict.txt";
// Number of entries in the dictionary.
static constexpr size_t dict_size = 370102;
// Max number of suggestions to show.
static constexpr size_t cutoff = 5;

/**
 * Validate and transform raw input.
 * @throws If raw is not fully alphabetic.
 * @param raw The raw user input.
 * @returns A lower-cased version of raw.
 */
string validate(string raw);

/**
 * Sort keys by value.
 * @param lev The Levenshtein map.
 * @param returns Words sorted by closest distance.
 */
vector<string> suggestions(const edit_t& lev);

int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false);
  const auto sdx = homophones(dict_name, dict_size);
  for (decltype(argc) i = 1; i < argc; ++i) {
    const auto word = validate(argv[i]);
    cout << word << " is spelled ";
    const auto rng = sdx.equal_range(soundex(word));
    const auto exists =
        find_if(rng.first, rng.second,
                [&word](const auto& iter) { return word == iter.second; });
    if (exists != rng.second) {
      cout << "correctly!\n";
      continue;
    }
    const auto lev = edit_distances(rng.first, rng.second, word);
    const auto suggest = suggestions(lev);
    cout << "incorrectly! Suggestions:\n";
    size_t counter = 0;
    for (const auto& diff : suggest) {
      cout << '\t' << diff << '\n';
      if (++counter == cutoff) break;
    }
  }
}

vector<string> suggestions(const edit_t& lev) {
  vector<string> words;
  words.reserve(lev.size());
  for (const auto& pr : lev) {
    words.emplace_back(pr.first);
  }
  sort(words.begin(), words.end(), [&lev](const auto& lhs, const auto& rhs) {
    return lev.at(lhs) < lev.at(rhs);
  });
  return words;
}

string validate(string raw) {
  if (any_of(raw.begin(), raw.end(), [](char ch) {
        return !isalpha(static_cast<unsigned char>(ch));
      })) {
    throw invalid_argument(raw + " is not fully alphabetic.");
  }
  transform(raw.begin(), raw.end(), raw.begin(), [](char ch) {
    return static_cast<char>(tolower(static_cast<unsigned char>(ch)));
  });
  return raw;
}
