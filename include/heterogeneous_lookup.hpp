#pragma once

#include <string>
#include <string_view>

namespace bookdb {

struct TransparentStringLess {
    using is_transparent = void;
    bool operator()(const std::string &str, const Book &book) { return str < book.title; }
    bool operator()(const Book &book, const std::string &str) { return book.title < str; }
    bool operator()(const Book &lhd, const Book &rhd) { return lhd.title < rhd.title; }
};

struct TransparentStringEqual {};

struct TransparentStringHash {};

}  // namespace bookdb
