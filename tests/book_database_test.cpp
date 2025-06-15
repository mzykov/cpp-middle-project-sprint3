#include "book_database.hpp"
#include <gtest/gtest.h>
#include <print>

#include "test.hpp"

// 1.
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

// 2.
TEST(TestBookDataBase, TestPushBack) {
    // given
    auto db = bookdb::BookDatabase();
    const auto book = bookdb::test::GetTestBook();
    // when
    db.PushBack(book);
    // then
    EXPECT_EQ(db.size(), 1);
    EXPECT_EQ(db.back().GetTitle(), book.title);
    EXPECT_EQ(db.back().GetAuthor(), book.author);
    EXPECT_EQ(db.back().GetYear(), book.year);
    EXPECT_EQ(db.back().GetGenre(), book.genre);
    EXPECT_EQ(db.back().GetRating(), book.rating);
    EXPECT_EQ(db.back().GetReadCount(), book.read_count);
}

// 3.
TEST(TestBookDataBase, TestEmplaceBack) {
    // given
    auto db = bookdb::BookDatabase();
    const auto book = bookdb::test::GetTestBook();
    // when
    db.EmplaceBack(book.title, book.author, book.year, book.genre, book.rating, book.read_count);
    // then
    EXPECT_EQ(db.size(), 1);
    EXPECT_EQ(db.back().GetTitle(), book.title);
    EXPECT_EQ(db.back().GetAuthor(), book.author);
    EXPECT_EQ(db.back().GetYear(), book.year);
    EXPECT_EQ(db.back().GetGenre(), book.genre);
    EXPECT_EQ(db.back().GetRating(), book.rating);
    EXPECT_EQ(db.back().GetReadCount(), book.read_count);
}

// 4.
TEST(TestBookDataBase, TestInitializerList) {
    // given
    auto db = bookdb::BookDatabase({
        bookdb::test::GetTestBook(),
        bookdb::test::GetTestBook(),
        bookdb::test::GetTestBook(),
    });
    // when
    auto gotSize = db.size();
    // then
    EXPECT_EQ(gotSize, 3);
}

// 5.
TEST(TestBookDataBase, TestClear) {
    // given
    auto db = bookdb::BookDatabase({bookdb::test::GetTestBook()});
    {
        // when
        auto gotSize = db.size();
        // then
        EXPECT_EQ(gotSize, 1);
    }
    {
        // when
        db.clear();
        auto gotSize = db.size();
        // then
        EXPECT_EQ(gotSize, 0);
    }
}

// 6.
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

// 7.
TEST(TestBookDataBase, TestAuthorOwnership) {
    // given
    auto db = bookdb::BookDatabase();
    const auto book = bookdb::test::GetTestBook();
    const std::string trueAuthor = "T.R. ue Author";
    // when
    {
        std::string scopedAuthor = trueAuthor;
        db.EmplaceBack(book.title, scopedAuthor, book.year, book.genre, book.rating, book.read_count);
    }
    // then
    EXPECT_EQ(db.back().GetAuthor(), trueAuthor);
}

// 8.
TEST(TestBookDataBase, TestFormatter) { std::println("{}", bookdb::BookDatabase()); }
