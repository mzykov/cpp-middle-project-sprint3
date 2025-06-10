#pragma once

namespace bookdb::test {
static const auto GetTestBook() {
    return bookdb::Book("Title", "A.U. Thor", 1985, bookdb::Genre::Biography, 5.0, 1000);
}
}  // namespace bookdb::test
