#include "book_database.hpp"
#include <gtest/gtest.h>
#include <print>

#include "test.hpp"

TEST(TestBookDataBase, TestEmpty) {
    // given
    const auto db = bookdb::BookDatabase();
    // when
    const auto &books = db.GetBooks();
    const auto &authors = db.GetAuthors();
    // then
    EXPECT_EQ(books.empty(), true);
    EXPECT_EQ(authors.empty(), true);
    EXPECT_EQ(db.empty(), true);
}

TEST(TestBookDataBase, TestPushBack) {
    // given
    auto db = bookdb::BookDatabase();
    // when
    db.PushBack(bookdb::test::GetTestBook());
    // then
    EXPECT_EQ(db.size(), 1);
}

TEST(TestBookDataBase, TestNoAuthorDuplicates) {
    // given
    auto db = bookdb::BookDatabase();
    // when
    db.PushBack(bookdb::test::GetTestBook());
    db.PushBack(bookdb::test::GetTestBook());
    // then
    EXPECT_EQ(db.size(), 2);
    EXPECT_EQ(db.GetBooks().size(), 2);
    EXPECT_EQ(db.GetAuthors().size(), 1);
}

TEST(TestBookDataBase, TestFormatter) { std::println("{}", bookdb::BookDatabase()); }
