#pragma once

#include <algorithm>
#include <iterator>
#include <random>
#include <stdexcept>
#include <string_view>
#include <utility>
#include <vector>

#include "book_database.hpp"

#include <print>

#include <boost/container/flat_map.hpp>

namespace bookdb {

template <BookContainerLike T, typename Comparator = TransparentStringLess>
auto buildAuthorHistogramFlat(BookDatabase<T> &db, Comparator cmp = {}) {
    boost::container::flat_map<std::string_view, std::size_t> hist;

    for (const auto &book : db) {
        ++hist[book.GetAuthor()];
    }

    return hist;
}

template <BookContainerLike T, typename Comparator = TransparentStringLess>
auto calculateGenreRatings(BookDatabase<T> &db, Comparator cmp = {}) {
    boost::container::flat_map<Genre, std::pair<std::size_t, double>> stats;

    for (const auto &book : db) {
        auto g = book.GetGenre();
        ++std::get<std::size_t>(stats[g]);
        std::get<double>(stats[g]) += book.GetRating();
    }

    boost::container::flat_map<std::string_view, double> hist;

    for (const auto &[genre, stat] : stats) {
        hist[GenreToString(genre)] = static_cast<double>(std::get<double>(stat) / std::get<std::size_t>(stat));
    }

    return hist;
}

template <BookContainerLike T, typename Aggregator = TransparentRatingPlus>
auto calculateAverageRating(BookDatabase<T> &db, Aggregator aggr = {}) {
    double res = 0.0;
    for (const auto &book : db) {
        res += book.GetRating();
    }
    return static_cast<double>(res / db.size());
}

template <BookContainerLike T, typename Comparator>
auto getTopNBy(BookDatabase<T> &db, std::size_t top, Comparator cmp) {
    {
        auto mid = std::next(db.begin(), top);
        std::partial_sort(db.begin(), mid, db.end(), cmp);
    }

    auto mid = std::next(db.begin(), top);
    std::vector<std::reference_wrapper<const Book>> res(db.begin(), mid);

    return res;
}

template <BookContainerLike T>
auto sampleRandomBooks(BookDatabase<T> &db, std::size_t top) {
    std::vector<std::reference_wrapper<const Book>> res;
    std::sample(db.cbegin(), db.cend(), std::back_inserter(res), top, std::mt19937{std::random_device{}()});
    return res;
}

}  // namespace bookdb

namespace std {

template <>
struct formatter<boost::container::flat_map<std::string_view, std::size_t>> {
    template <typename FormatContext>
    auto format(const boost::container::flat_map<std::string_view, std::size_t> &hist, FormatContext &fc) const {
        for (const auto &[key, val] : hist) {
            format_to(fc.out(), "{:30} |{}\n", key, std::string(val, '='));
        }
        return fc.out();
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

template <>
struct formatter<boost::container::flat_map<std::string_view, double>> {
    template <typename FormatContext>
    auto format(const boost::container::flat_map<std::string_view, double> &hist, FormatContext &fc) const {
        for (const auto &[key, val] : hist) {
            format_to(fc.out(), "{}: {:.3}\n", key, val);
        }
        return fc.out();
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

}  // namespace std
