#pragma once

#include <concepts>
#include <iterator>

#include "book.hpp"

namespace bookdb {

template <typename T>
concept BookContainerLike = requires(T t) {
    { *std::begin(t) } -> std::convertible_to<Book>;
};

template <typename T>
concept BookIterator = std::contiguous_iterator<T>;

template <typename S, typename I>
concept BookSentinel = std::sentinel_for<S, I>;

template <typename P>
concept BookPredicate = requires(P pred, const Book &book) {
    { pred(book) } -> std::convertible_to<bool>;
};

template <typename C>
concept BookComparator = requires(C cmp, const Book &lhd, const Book &rhd) {
    { cmp(lhd, rhd) } -> std::convertible_to<bool>;
};

}  // namespace bookdb
