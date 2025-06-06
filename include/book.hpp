#pragma once

#include <algorithm>
#include <array>
#include <format>
#include <stdexcept>
#include <string>

namespace bookdb {

enum class Genre { Fiction, NonFiction, SciFi, Biography, Mystery, Unknown };
constexpr std::array<std::string_view, 6> GenreStr{"Fiction", "NonFiction", "SciFi", "Biography", "Mystery", "Unknown"};

constexpr Genre GenreFromString(std::string_view sv) {
    const auto it = std::find(GenreStr.begin(), GenreStr.end(), sv);
    if (it == GenreStr.end()) {
        return Genre::Unknown;
    } else {
        return static_cast<Genre>(std::distance(GenreStr.begin(), it));
    }
}

constexpr std::string_view GenreToString(Genre g) { return GenreStr[static_cast<std::size_t>(g)]; }

constexpr double CheckRating(const double rating) {
    constexpr double low = 0.0, high = 5.0;
    if (low <= rating && rating <= high) {
        return rating;
    } else {
        throw std::invalid_argument{"Invalid rating value"};
    }
}

struct Book {
    std::string title;
    std::string_view author;

    unsigned int year = 0;
    Genre genre = Genre::Unknown;
    double rating = 0.0;
    unsigned int read_count = 0;

    // clang-format off
    constexpr Book(
        const std::string &book_title,
        std::string_view   book_author,
        unsigned int       book_year,
        Genre              book_genre, // Genre as enum
        double             book_rating,
        unsigned int       book_read_count
    ) :
        title(book_title),
        author(book_author),
        year(book_year),
        genre(book_genre),
        rating(CheckRating(book_rating)),
        read_count(book_read_count)
    {}
    // clang-format on

    // clang-format off
    constexpr Book(
        const std::string &book_title,
        std::string_view   book_author,
        unsigned int       book_year,
        std::string_view   book_genre, // Genre as str
        double             book_rating,
        unsigned int       book_read_count
    ) :
        title(book_title),
        author(book_author),
        year(book_year),
        genre(GenreFromString(book_genre)),
        rating(CheckRating(book_rating)),
        read_count(book_read_count)
    {}
    // clang-format on

    const std::string &GetTitle() const { return title; }
    const std::string_view GetAuthor() const { return author; }
    const unsigned int GetYear() const { return year; }
    const Genre GetGenre() const { return genre; }
    const double GetRating() const { return rating; }
    const unsigned int GetReadCount() const { return read_count; }
};

}  // namespace bookdb

namespace std {

template <>
struct formatter<bookdb::Genre, char> {
    template <typename FormatContext>
    auto format(const bookdb::Genre g, FormatContext &fc) const {
        return format_to(fc.out(), "{}", GenreToString(g));
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

template <>
struct formatter<bookdb::Book, char> {
    template <typename FormatContext>
    auto format(const bookdb::Book book, FormatContext &fc) const {
        constexpr std::array<std::string_view, 6> rates{{"☆☆☆☆☆", "★☆☆☆☆", "★★☆☆☆", "★★★☆☆", "★★★★☆", "★★★★★"}};
        // clang-format off
        return format_to(
            fc.out(),
            "{} / {} / {} / {} / {:.3} {}",
            book.GetTitle(), book.GetAuthor(), book.GetYear(), book.GetGenre(), book.GetRating(),
            rates[static_cast<std::size_t>(book.GetRating())]
        );
        // clang-format on
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

}  // namespace std
