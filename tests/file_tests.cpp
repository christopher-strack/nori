#include <gtest/gtest.h>
#include <nori/file.h>

#include <string>
#include <vector>
#include <stdexcept>


TEST(file, construct) {
    nori::file file;

    ASSERT_FALSE(file.is_open());
}

TEST(file, construct_open) {
    nori::file file("assets/file.txt");

    ASSERT_TRUE(file.is_open());
}

TEST(file, open) {
    nori::file file;

    file.open("assets/file.txt");
    ASSERT_TRUE(file.is_open());
}

TEST(file, open_invalid) {
    nori::file file;

    file.open("assets/invalid_file_location.txt");
    ASSERT_FALSE(file.is_open());
}

TEST(file, close) {
    nori::file file;

    file.open("assets/file.txt");
    ASSERT_TRUE(file.is_open());

    file.close();
    ASSERT_FALSE(file.is_open());
}

TEST(file, size) {
    nori::file file("assets/file.txt");

    ASSERT_EQ(file.size(), 7);
}

TEST(file, read) {
    nori::file file("assets/file.txt");
    std::vector<char> buffer(file.size());

    unsigned int bytes_read = file.read(&buffer[0], buffer.size());

    ASSERT_EQ(bytes_read, buffer.size());
    ASSERT_EQ("content", std::string(&buffer[0], bytes_read));
}

TEST(file, read_some) {
    nori::file file("assets/file.txt");
    std::vector<char> buffer(file.size() - 2);

    unsigned int bytes_read = file.read(&buffer[0], buffer.size());

    ASSERT_EQ(bytes_read, buffer.size());
    ASSERT_EQ("conte", std::string(&buffer[0], bytes_read));
}

TEST(file, read_too_much) {
    nori::file file("assets/file.txt");
    unsigned int file_size = file.size();
    std::vector<char> buffer(file_size + 10);

    unsigned int bytes_read = file.read(&buffer[0], buffer.size());

    ASSERT_EQ(bytes_read, file_size);
}


#if defined(ANDROID)

TEST(android_file, open_none_asset_location) {
    nori::file file;

    ASSERT_THROW(file.open("file.txt"), std::runtime_error);
}

#endif
