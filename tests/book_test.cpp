#include "book.hpp"
#include <gtest/gtest.h>
#include <print>

#include "test.hpp"

TEST(TestBook, TestGenreFromStringExisting) {
    // given
    const std::string_view givenGenre = "Mystery";
    const auto expectedGenre = bookdb::Genre::Mystery;
    // when
    const auto gotGenre = bookdb::GenreFromString(givenGenre);
    // then
    EXPECT_EQ(gotGenre, expectedGenre);
}

TEST(TestBook, TestGenreFromStringNonExisting) {
    // given
    const std::string_view givenGenre = "...Bla-bla-bla-fake-genre...";
    const auto expectedGenre = bookdb::Genre::Unknown;
    // when
    const auto gotGenre = bookdb::GenreFromString(givenGenre);
    // then
    EXPECT_EQ(gotGenre, expectedGenre);
}

TEST(TestBook, TestGenreToString) {
    // given
    const auto givenGenre = bookdb::Genre::Mystery;
    const std::string_view expectedGenre = "Mystery";
    // when
    const auto gotGenre = bookdb::GenreToString(givenGenre);
    // then
    EXPECT_EQ(gotGenre, expectedGenre);
}

TEST(TestBook, TestCheckRatingBoundaries) {
    // given
    const double givenLo = 0.0, givenHi = 5.0;
    // when
    const double gotLo = bookdb::CheckRating(givenLo);
    const double gotHi = bookdb::CheckRating(givenHi);
    // then
    EXPECT_EQ(gotLo, givenLo);
    EXPECT_EQ(gotHi, givenHi);
}

TEST(TestBook, TestCheckRatingOutOfRange) {
    EXPECT_ANY_THROW(bookdb::CheckRating(-0.1));
    EXPECT_ANY_THROW(bookdb::CheckRating(+5.1));
}

TEST(TestBook, TestFormatter) { std::println("{}", bookdb::test::GetTestBook()); }
