/*
Compute soundex of given strings.
See https://en.wikipedia.org/wiki/Soundex

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <string>
#include <unordered_map>
using sound_t = std::unordered_multimap<std::string, std::string>;

/**
 * See https://en.wikipedia.org/wiki/Soundex
 * @param word The input word to compute soundex for.
 * @returns The soundex of word.
 */
std::string soundex(std::string word);

/**
 * Import a dictionary from a file.
 * @param name The file name of the dictionary.
 * @param size The number of entries in the dictionary.
 * @returns A map from soundex to dictionary entries.
 */
sound_t homophones(const char* name, size_t size);
