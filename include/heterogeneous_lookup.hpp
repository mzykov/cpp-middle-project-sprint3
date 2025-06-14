#pragma once

#include <string>

namespace bookdb {

struct TransparentStringLess {
    using is_transparent = void;
    bool operator()(const std::string_view str, const Book &book) { return str < book.title; }
    bool operator()(const Book &book, const std::string_view str) { return book.title < str; }
    bool operator()(const Book &lhd, const Book &rhd) { return lhd.title < rhd.title; }
};

struct TransparentStringEqual {
    using is_transparent = void;
    bool operator()(const std::string_view str, const Book &book) { return str == book.title; }
    bool operator()(const Book &book, const std::string_view str) { return book.title == str; }
    bool operator()(const Book &lhd, const Book &rhd) { return lhd.title == rhd.title; }
};

struct TransparentStringHash {
    using is_transparent = void;
    auto operator()(const Book &book) const { return std::hash<std::string>{}(book.title); }
    auto operator()(const std::string &title) const { return std::hash<std::string>{}(title); }
};

struct TransparentRatingPlus {
    using is_transparent = void;
    double operator()(const double l, const Book &book) { return l + book.GetRating(); }
    double operator()(const Book &book, const double r) { return book.GetRating() + r; }
    double operator()(const Book &lhd, const Book &rhd) { return lhd.GetRating() + rhd.GetRating(); }
    double operator()(const double l, const double r) { return l + r; }
};

}  // namespace bookdb
