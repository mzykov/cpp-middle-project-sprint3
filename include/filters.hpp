#pragma once

#include <algorithm>
#include <functional>

#include "book.hpp"
#include "concepts.hpp"

namespace bookdb {

template <class InputIt, class UnaryPred>
auto filterBooks(InputIt first, InputIt last, UnaryPred pred) {
    std::vector<std::reference_wrapper<const Book>> res;
    std::copy_if(first, last, std::back_inserter(res), pred);
    return res;
}

auto GenreIs = [](const Genre genre) { return [genre](const Book &book) { return book.GetGenre() == genre; }; };

auto RatingAbove = [](const double above) { return [above](const Book &book) { return book.GetRating() > above; }; };

auto YearBetween = [](const unsigned int l, const unsigned int r) {
    return [l, r](const Book &book) { return l <= book.GetYear() && book.GetYear() <= r; };
};

template <class... UnaryPred>
auto all_of = [](UnaryPred... pred) { return [&](const Book &book) { return (pred(book) && ...); }; };

}  // namespace bookdb
