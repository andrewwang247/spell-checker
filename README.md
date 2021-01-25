# Spell Checker

A program that suggests spelling corrections based on homophones and edit distance. Compile with the provided `Makefile` and run with `./spell [word_1] [word_2] ... [word_n]`. Provided words must be fully alphabetic. The default max number of suggestions for each word is 5. The provided dictionary of correctly spelled words is `dict.txt`.

## Algorithm

Let *w* be a user-provided alphabetic word after transforming to all lowercase. Moreover, suppose that *w* is incorrectly spelled (by definition: not contained in `dict.txt`). Compute the [Soundex](https://en.wikipedia.org/wiki/Soundex) encoding *S(w)* and find all words *w_1*, ..., *w_n* from `dict.txt` such that *S(w) = S(w_i)*. Reorder *w_1*, ..., *w_n* by [Levenshtein distance](https://en.wikipedia.org/wiki/Levenshtein_distance) such that *L(w_i, w) <= L(w_j, w)* whenever *i <= j*. Provide the user with the first *m = min(n, k)* ordered suggestions *w_1*, ..., *w_m* for some pre-determined threshold value *k*.
