#include "filters.hpp"
#include <gtest/gtest.h>

const auto GetTestBook() { return bookdb::Book("Title", "A.U. Thor", 1985, bookdb::Genre::Biography, 5.0, 1000); }

TEST(TestFilters, TestFilterBooks) {
    // given
    // when
    // then
    // EXPECT_EQ(givenStr, decryptedStr);
    // EXPECT_EQ(checksumOfGivenStr, checksumOfDecryptedStr);
}

TEST(TestFilters, TestGenreIs) {
    // given
    auto book = GetTestBook();
    auto filter = bookdb::GenreIs("Biography");

    // when
    bool ok = filter(book);

    // then
    EXPECT_EQ(ok, true);
}

TEST(TestFilters, TestRatingAbove) {
    // given
    auto book = GetTestBook();
    auto filter = bookdb::RatingAbove(5.0);

    // when
    bool ok = filter(book);

    // then
    EXPECT_EQ(ok, true);
}

TEST(TestFilters, TestYearBetween) {
    // given
    auto book = GetTestBook();
    auto filter = bookdb::YearBetween(1985, 2000);

    // when
    bool ok = filter(book);

    // then
    EXPECT_EQ(ok, true);
}
