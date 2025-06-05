#pragma once

#include <algorithm>
#include <iterator>
#include <random>
#include <stdexcept>
#include <string_view>

#include "book_database.hpp"

#include <print>

#include <boost/container/flat_map.hpp>

namespace bookdb {

template <BookContainerLike T, typename Comparator = TransparentStringLess>
auto buildAuthorHistogramFlat(BookDatabase<T> &db, Comparator comp = {}) {
    boost::container::flat_map<std::string_view, int> hist;
    for (const auto &book : db) {
        ++hist[book.GetAuthor()];
    }
    return hist;
}

}  // namespace bookdb

namespace std {

template <>
struct formatter<boost::container::flat_map<std::string_view, int>> {
    template <typename FormatContext>
    auto format(const boost::container::flat_map<std::string_view, int> &hist, FormatContext &fc) const {
        for (const auto &[author, val] : hist) {
            format_to(fc.out(), "{:20}\t{}\n", author, std::string(val, '='));
        }
        return fc.out();
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

}  // namespace std
