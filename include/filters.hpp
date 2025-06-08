#pragma once

#include <algorithm>
#include <functional>

#include "book.hpp"
#include "concepts.hpp"

namespace bookdb {

auto filterBooks(BookIterator auto first, BookIterator auto last, BookPredicate auto pred) {
    std::vector<std::reference_wrapper<const Book>> res;
    std::copy_if(first, last, std::back_inserter(res), pred);
    return res;
}

auto GenreIs = [](std::string_view genre) {
    return [genre](const Book &book) { return book.GetGenre() == GenreFromString(genre); };
};

auto RatingAbove = [](const double above) { return [above](const Book &book) { return book.GetRating() >= above; }; };

auto YearBetween = [](const unsigned int l, const unsigned int r) {
    return [l, r](const Book &book) { return l <= book.GetYear() && book.GetYear() <= r; };
};

auto all_of = [](auto &&...pred) { return [&](const Book &book) { return (pred(book) && ...); }; };

auto any_of = [](auto &&...pred) { return [&](const Book &book) { return (pred(book) || ...); }; };

}  // namespace bookdb
