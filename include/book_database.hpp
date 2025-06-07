#pragma once

#include <print>
#include <set>
#include <string>
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

    using AuthorContainer = std::set<std::string_view>;

    constexpr BookDatabase() = default;
    constexpr BookDatabase(std::initializer_list<const Book> lst) : books_(lst) {
        for (const auto &book : books_) {
            if (const auto author = book.GetAuthor(); author.length() > 0) {
                authors_.insert(author);
            }
        }
    }

    void clear() {
        books_.clear();
        authors_.clear();
    }

    bool empty() const { return books_.empty() && authors_.empty(); }
    std::size_t size() const { return books_.size(); }
    auto begin() { return books_.begin(); }
    auto cbegin() { return books_.cbegin(); }
    auto end() { return books_.end(); }
    auto cend() { return books_.cend(); }
    auto rbegin() { return books_.rbegin(); }
    auto crbegin() { return books_.crbegin(); }
    auto rend() { return books_.rend(); }
    auto crend() { return books_.rcend(); }

    const BookContainer &GetBooks() const { return books_; }
    const AuthorContainer &GetAuthors() const { return authors_; }

    void EmplaceBack(auto &&...args) {
        books_.emplace_back(std::forward<decltype(args)>(args)...);
        if (auto author = books_.back().GetAuthor(); author.length() > 0) {
            authors_.insert(author);
        }
    }

    void PushBack(auto &&...args) {
        books_.push_back(std::forward<decltype(args)>(args)...);
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
