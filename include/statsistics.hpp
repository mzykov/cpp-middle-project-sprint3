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
auto buildAuthorHistogramFlat(const BookDatabase<T> &db, Comparator cmp = {}) {
    boost::container::flat_map<std::string_view, std::size_t> hist;
    std::for_each(db.cbegin(), db.cend(), [&](const auto &book) { ++hist[book.GetAuthor()]; });
    return hist;
}

template <BookContainerLike T, typename Comparator = TransparentStringLess>
auto calculateGenreRatings(const BookDatabase<T> &db, Comparator cmp = {}) {
    boost::container::flat_map<Genre, std::pair<std::size_t, double>> stats;

    std::for_each(db.cbegin(), db.cend(), [&](const auto &book) {
        auto g = book.GetGenre();
        ++std::get<std::size_t>(stats[g]);
        std::get<double>(stats[g]) += book.GetRating();
    });

    boost::container::flat_map<std::string_view, double> hist;

    std::for_each(stats.cbegin(), stats.cend(), [&hist](const auto &p) {
        const auto &[genre, stat] = p;
        hist[GenreToString(genre)] = std::get<double>(stat) / std::get<std::size_t>(stat);
    });

    return hist;
}

template <BookContainerLike T, typename Aggregator = TransparentRatingPlus>
double calculateAverageRating(const BookDatabase<T> &db, Aggregator aggr = {}) {
    return std::accumulate(db.cbegin(), db.cend(), 0.0, aggr) / db.size();
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
