#pragma once

#include "book.hpp"

namespace bookdb::comp {

struct LessByAuthor {
    bool operator()(const Book &lhd, const Book &rhd) { return lhd.author < rhd.author; }
};

struct LessByRating {
    bool operator()(const Book &lhd, const Book &rhd) { return lhd.rating < rhd.rating; }
};

}  // namespace bookdb::comp
