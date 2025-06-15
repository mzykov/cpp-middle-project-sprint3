#pragma once

#include <print>
#include <string>
#include <unordered_set>
#include <vector>

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
    using reference = value_type &;
    using const_reference = const reference;
    using pointer = BookContainer::pointer;
    using const_pointer = const pointer;
    using iterator = BookContainer::iterator;
    using const_iterator = const iterator;
    using reverse_iterator = BookContainer::reverse_iterator;
    using const_reverse_iterator = const reverse_iterator;

    using AuthorContainer = std::unordered_set<std::string>;

    constexpr BookDatabase() = default;
    constexpr BookDatabase(std::initializer_list<const Book> lst) : books_(lst) {
        for (auto &book : books_) {
            moveAuthorOwnership(book);
        }
    }

    void clear() {
        books_.clear();
        authors_.clear();
    }

    bool empty() const { return books_.empty() && authors_.empty(); }
    std::size_t size() const { return books_.size(); }
    auto begin() { return books_.begin(); }
    auto end() { return books_.end(); }
    const auto cbegin() const { return books_.cbegin(); }
    const auto cend() const { return books_.cend(); }
    auto rbegin() { return books_.rbegin(); }
    auto rend() { return books_.rend(); }
    const auto crbegin() const { return books_.crbegin(); }
    const auto crend() const { return books_.crend(); }

    const BookContainer &GetBooks() const { return books_; }
    const AuthorContainer &GetAuthors() const { return authors_; }

    void EmplaceBack(auto &&...args) {
        books_.emplace_back(std::forward<decltype(args)>(args)...);
        moveAuthorOwnership(books_.back());
    }

    constexpr void PushBack(const Book &book) {
        books_.push_back(book);
        moveAuthorOwnership(books_.back());
    }

    constexpr void PushBack(Book &&book) {
        books_.push_back(book);
        moveAuthorOwnership(books_.back());
    }

private:
    BookContainer books_;
    AuthorContainer authors_;

    constexpr void moveAuthorOwnership(Book &book) {
        if (book.author.length() > 0) {
            auto [it, _] = authors_.emplace(book.author.data());
            book.author = *it;
        }
    }
};

}  // namespace bookdb

namespace std {

template <bookdb::BookContainerLike T>
struct formatter<bookdb::BookDatabase<T>> {
    template <typename FormatContext>
    auto format(const bookdb::BookDatabase<T> &db, FormatContext &fc) const {
        format_to(fc.out(), "BookDatabase (size = {}):\n", db.size());

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
