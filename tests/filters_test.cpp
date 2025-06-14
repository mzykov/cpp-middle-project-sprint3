#include "filters.hpp"
#include <gtest/gtest.h>

#include "test.hpp"

TEST(TestFilters, TestGenreIs) {
    // given
    auto book = bookdb::test::GetTestBook();
    auto filter = bookdb::GenreIs("Biography");
    // when
    bool ok = filter(book);
    // then
    EXPECT_TRUE(ok);
}

TEST(TestFilters, TestRatingAbove) {
    // given
    auto book = bookdb::test::GetTestBook();
    auto filter = bookdb::RatingAbove(5.0);
    // when
    bool ok = filter(book);
    // then
    EXPECT_TRUE(ok);
}

TEST(TestFilters, TestYearBetween) {
    // given
    auto book = bookdb::test::GetTestBook();
    auto filter = bookdb::YearBetween(1985, 2000);
    // when
    bool ok = filter(book);
    // then
    EXPECT_TRUE(ok);
}

TEST(TestFilters, TestAllOfTrue) {
    // given
    auto book = bookdb::test::GetTestBook();
    auto filter = bookdb::all_of(bookdb::YearBetween(1985, 2000), bookdb::GenreIs("Biography"));
    // when
    bool ok = filter(book);
    // then
    EXPECT_TRUE(ok);
}

TEST(TestFilters, TestAllOfFalse) {
    // given
    auto book = bookdb::test::GetTestBook();
    auto filter = bookdb::all_of(bookdb::GenreIs("Biography"), bookdb::YearBetween(1900, 1920));
    // when
    bool ok = filter(book);
    // then
    EXPECT_FALSE(ok);
}

TEST(TestFilters, TestAnyOfTrue) {
    // given
    auto book = bookdb::test::GetTestBook();
    auto filter = bookdb::any_of(bookdb::YearBetween(1900, 1920), bookdb::GenreIs("Biography"));
    // when
    bool ok = filter(book);
    // then
    EXPECT_TRUE(ok);
}

TEST(TestFilters, TestAnyOfFalse) {
    // given
    auto book = bookdb::test::GetTestBook();
    auto filter = bookdb::any_of(bookdb::YearBetween(1900, 1920), bookdb::GenreIs("Mistery"));
    // when
    bool ok = filter(book);
    // then
    EXPECT_FALSE(ok);
}
