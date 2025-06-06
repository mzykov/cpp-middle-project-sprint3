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
    bool operator()(const double l, const Book &book) { return l + book.rating; }
    bool operator()(const Book &book, const double r) { return book.rating + r; }
    bool operator()(const Book &lhd, const Book &rhd) { return lhd.rating + rhd.rating; }
};

}  // namespace bookdb
