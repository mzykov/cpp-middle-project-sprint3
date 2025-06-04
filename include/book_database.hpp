#pragma once

#include <print>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_set>

#include "book.hpp"
#include "concepts.hpp"
#include "heterogeneous_lookup.hpp"

namespace bookdb {

template <BookContainerLike BookContainer = std::vector<Book>>
class BookDatabase {
public:
    using value_type = Book;
    using allocator_type = BookContainer::allocator_type;
    using size_type = BookContainer::size_type;
    using difference_type = BookContainer::difference_type;
    using reference = value_type&;
    using const_reference = const reference;
    using pointer = BookContainer::pointer;
    using const_pointer = const pointer;
    using iterator = BookContainer::iterator;
    using const_iterator = const iterator;
    using reverse_iterator = BookContainer::reverse_iterator;
    using const_reverse_iterator = const reverse_iterator;

    using AuthorContainer = std::unordered_set<std::string_view>;

    BookDatabase() = default;

    void Clear() {
        books_.clear();
        authors_.clear();
    }

    std::size_t size() const { return books_.size(); }
    auto begin() { return books_.begin(); }
    auto cbegin() { return books_.cbegin(); }
    auto end() { return books_.end(); }
    auto cend() { return books_.cend(); }

    const BookContainer &GetBooks() const { return books_; }
    const AuthorContainer &GetAuthors() const { return authors_; }

    template <typename... Args>
    void EmplaceBack(Args... args) {
        books_.emplace_back(args...);
        if (auto author = books_.back().GetAuthor(); author.length() > 0) {
            authors_.insert(author);
        }
    }

private:
    BookContainer books_;
    AuthorContainer authors_;
};

}  // namespace bookdb

namespace std {

template <>
struct formatter<bookdb::BookDatabase<std::vector<bookdb::Book>>> {
    template <typename FormatContext>
    auto format(const bookdb::BookDatabase<std::vector<bookdb::Book>> &db, FormatContext &fc) const {
        format_to(fc.out(), "BookDatabase (size = {}): ", db.size());

        format_to(fc.out(), "Books:\n");
        for (const auto &book : db.GetBooks()) {
            format_to(fc.out(), "- {}\n", book);
        }

        format_to(fc.out(), "Authors:\n");
        for (const auto &author : db.GetAuthors()) {
            format_to(fc.out(), "- {}\n", author);
        }

        return fc.out();
    }

    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();  // Просто игнорируем пользовательский формат
    }
};

}  // namespace std
