#pragma once

#include <string>

namespace bookdb {

struct TransparentStringLess {
    using is_transparent = void;
    bool operator()(const std::string &str, const Book &book) { return str < book.title; }
    bool operator()(const Book &book, const std::string &str) { return book.title < str; }
    bool operator()(const Book &lhd, const Book &rhd) { return lhd.title < rhd.title; }
};

struct TransparentStringEqual {};

struct TransparentStringHash {};

struct TransparentRatingPlus {
    using is_transparent = void;
    double operator()(const double l, const Book &book) { return l + book.GetRating(); }
    double operator()(const Book &book, const double r) { return book.GetRating() + r; }
    double operator()(const Book &lhd, const Book &rhd) { return lhd.GetRating() + rhd.GetRating(); }
};

}  // namespace bookdb
