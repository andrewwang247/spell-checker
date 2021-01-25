/*
Compute soundex of given strings.
See https://en.wikipedia.org/wiki/Soundex

Copyright 2021. Siwei Wang.
*/
#include "soundex.h"
#include <algorithm>
#include <fstream>
using std::ifstream;
using std::remove;
using std::string;
using std::transform;
using std::unique;

/**
 * @param c The character to transform.
 * @returns The soundex mapping of c.
 */
char soundex_mapping(char c) {
  switch (c) {
    case 'b':
    case 'f':
    case 'p':
    case 'v':
      return '1';
    case 'c':
    case 'g':
    case 'j':
    case 'k':
    case 'q':
    case 's':
    case 'x':
    case 'z':
      return '2';
    case 'd':
    case 't':
      return '3';
    case 'l':
      return '4';
    case 'm':
    case 'n':
      return '5';
    case 'r':
      return '6';
    default:
      return '0';
  }
}

string soundex(string word) {
  transform(word.begin() + 1, word.end(), word.begin() + 1, soundex_mapping);
  auto iter = unique(word.begin() + 1, word.end());
  iter = remove(word.begin() + 1, iter, '0');
  const auto buffered = string(word.begin(), iter) + "0000";
  return buffered.substr(0, 4);
}

sound_t homophones(const char* name, size_t size) {
  sound_t sdx;
  sdx.reserve(size);
  ifstream ifp(name);
  for (string word; ifp >> word;) {
    sdx.emplace(soundex(word), word);
  }
  return sdx;
}
