/*
Compute Levenshtein distance between 2 strings.
See https://en.wikipedia.org/wiki/Levenshtein_distance

Copyright 2021. Siwei Wang.
*/
#pragma once
#include <string>
#include <unordered_map>
#include "soundex.h"
using edit_t = std::unordered_map<std::string, size_t>;

/**
 * See https://en.wikipedia.org/wiki/Levenshtein_distance
 * @param lhs The 1st string to compare.
 * @param rhs The 2nd string to compare.
 * @returns The Levenshtein distance between lhs and rhs.
 */
size_t levenshtein(const std::string& lhs, const std::string& rhs);

/**
 * Compute Levenshtein distances from word.
 * @param begin The start of the index.
 * @param end The end of the index.
 * @returns Distance from word mapped over [begin, end) values.
 */
edit_t edit_distances(sound_t::const_iterator begin,
                      sound_t::const_iterator end, const std::string& word);
