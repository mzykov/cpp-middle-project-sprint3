#pragma once

#include <algorithm>
#include <format>
#include <stdexcept>
#include <string_view>
#include <variant>

namespace bookdb {

enum class Genre { Fiction, NonFiction, SciFi, Biography, Mystery, Unknown };

constexpr Genre GenreFromString(std::string_view sv) {
    const std::vector<std::string_view> m{"Fiction", "NonFiction", "SciFi", "Biography", "Mystery", "Unknown"};
    const auto it = std::find(m.begin(), m.end(), sv);

    if (it == m.end()) {
        return Genre::Unknown;
    } else {
        return static_cast<Genre>(std::distance(m.begin(), it));
    }
}

constexpr std::string_view GenreToString(Genre g) {
    const std::vector<std::string_view> m{"Fiction", "NonFiction", "SciFi", "Biography", "Mystery", "Unknown"};
    return m.at(static_cast<int>(g));
}

struct Book {
    std::string title;
    std::string_view author;

    unsigned int year = 0;
    Genre genre = Genre::Unknown;
    double rating = 0.0;
    unsigned int read_count = 0;

    constexpr Book(
        const std::string& book_title,
        std::string_view book_author,
        unsigned int book_year,
        Genre book_genre,
        double book_rating,
        unsigned int book_read_count
        )
    : title(book_title), author(book_author), year(book_year), genre(book_genre), rating(book_rating), read_count(book_read_count) {}
    //constexpr Book(std::string_view genre_sv) : genre(GenreFromString(genre_sv)) {}

    const std::string_view GetAuthor() const { return author; }
    const Genre GetGenre() const { return genre; }
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
        return format_to(fc.out(), "{} / {} / {} / {}", book.title, book.author, book.year, book.genre);
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

}  // namespace std
