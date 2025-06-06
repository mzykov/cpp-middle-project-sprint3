#pragma once

#include "book.hpp"

namespace bookdb::comp {

struct LessByAuthor {
    bool operator()(const Book &lhd, const Book &rhd) { return lhd.author < rhd.author; }
};

struct LessByRating {
    bool operator()(const Book &lhd, const Book &rhd) { return lhd.rating < rhd.rating; }
};

struct GreaterByRating {
    bool operator()(const Book &lhd, const Book &rhd) { return lhd.rating >= rhd.rating; }
};

struct GreaterByReadCount {
    bool operator()(const Book &lhd, const Book &rhd) { return lhd.read_count >= rhd.read_count; }
};

}  // namespace bookdb::comp
