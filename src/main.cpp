#include <algorithm>

#include "book_database.hpp"
#include "comparators.hpp"
#include "filters.hpp"
#include "statsistics.hpp"

using namespace bookdb;

int main() {
    BookDatabase<std::vector<Book>> db;

    // Add some books
    db.EmplaceBack("1984", "George Orwell", 1949, Genre::SciFi, 4., 190);
    db.EmplaceBack("Animal Farm", "George Orwell", 1945, Genre::Fiction, 2.1, 143);
    db.EmplaceBack("The Great Gatsby", "F. Scott Fitzgerald", 1925, "Fiction", 4.5, 120);
    db.EmplaceBack("To Kill a Mockingbird", "Harper Lee", 1960, Genre::Fiction, 4.8, 156);
    db.EmplaceBack("Pride and Prejudice", "Jane Austen", 1813, Genre::Fiction, 4.7, 178);
    db.EmplaceBack("The Catcher in the Rye", "J.D. Salinger", 1951, Genre::Fiction, 4.3, 112);
    db.EmplaceBack("Brave New World", "Aldous Huxley", 1932, Genre::SciFi, 3.5, 98);
    db.EmplaceBack("Jane Eyre", "Charlotte Brontë", 1847, Genre::Fiction, 4.6, 110);
    db.EmplaceBack("The Hobbit", "J.R.R. Tolkien", 1937, Genre::Fiction, 4.9, 203);
    db.EmplaceBack("Lord of the Flies", "William Golding", 1954, Genre::Fiction, 4.2, 89);
    std::print("Books: {}\n\n", db);

    // Sort by author
    {
        std::sort(db.begin(), db.end(), comp::LessByAuthor{});
        std::print("Books sorted by author: {}\n\n==================\n", db);
    }

    // Sort by rating
    {
        std::sort(db.begin(), db.end(), comp::LessByRating{});
        std::print("Books sorted by rating: {}\n\n==================\n", db);
    }

    // Author histogram
    {
        auto histogram = buildAuthorHistogramFlat(db);
        std::print("Author histogram:\n{}", histogram);
    }

    // Ratings
    {
        auto genreRatings = calculateGenreRatings(db);
        std::print("\n\nAverage ratings by genres:\n{}\n", genreRatings);

        auto avgRating = calculateAverageRating(db);
        std::print("Average books rating in library: {}\n", avgRating);
    }

    // Filters all_of
    {
        auto filtered = filterBooks(db.begin(), db.end(), all_of(YearBetween(1900, 1999), RatingAbove(4.5)));
        std::print("\n\nBooks from the 20th century with rating ≥ 4.5:\n");
        std::for_each(filtered.cbegin(), filtered.cend(), [](const auto &v) { std::print("{}\n", v.get()); });
    }

    // Filters any_of
    {
        auto filtered = filterBooks(db.begin(), db.end(), any_of(GenreIs("SciFi"), RatingAbove(4.8)));
        std::print("\n\nBooks in SciFi genre or rating ≥ 4.8:\n");
        std::for_each(filtered.cbegin(), filtered.cend(), [](const auto &v) { std::print("{}\n", v.get()); });
    }

    // Top 3 books by rating
    {
        auto topBooks = getTopNBy(db, 3, comp::GreaterByRating{});
        std::print("\n\nTop 3 books by rating:\n");
        std::for_each(topBooks.cbegin(), topBooks.cend(), [](const auto &v) { std::print("{}\n", v.get()); });
    }

    // Most readable book
    {
        auto topBooks = getTopNBy(db, 1, comp::GreaterByReadCount{});
        std::print("\n\nMost readable book:\n");
        std::for_each(topBooks.cbegin(), topBooks.cend(), [](const auto &v) { std::print("{}\n", v.get()); });
    }

    // Random sample books
    {
        auto randomBooks = sampleRandomBooks(db, 3);
        std::print("\n\nRandom books sample of length 3:\n");
        std::for_each(randomBooks.cbegin(), randomBooks.cend(), [](const auto &v) { std::print("{}\n", v.get()); });
    }

    // Find if
    {
        auto orwellBookIt =
            std::find_if(db.begin(), db.end(), [](const auto &v) { return v.GetAuthor() == "George Orwell"; });
        if (orwellBookIt != db.end()) {
            std::print("\n\nTransparent lookup by authors. Found Orwell's book: {}\n", *orwellBookIt);
        }
    }

    return 0;
}
