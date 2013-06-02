#include <gtest/gtest.h>
#include <nori/detail/stl_file.h>

#include <string>
#include <vector>


TEST(stl_file, construct) {
    nori::detail::stl_file file;

    ASSERT_FALSE(file.is_open());
}

TEST(stl_file, construct_open) {
    nori::detail::stl_file file("data/file.txt");

    ASSERT_TRUE(file.is_open());
}

TEST(stl_file, open) {
    nori::detail::stl_file file;

    file.open("data/file.txt");
    ASSERT_TRUE(file.is_open());
}

TEST(stl_file, close) {
    nori::detail::stl_file file;

    file.open("data/file.txt");
    ASSERT_TRUE(file.is_open());

    file.close();
    ASSERT_FALSE(file.is_open());
}

TEST(stl_file, size) {
    nori::detail::stl_file file("data/file.txt");

    ASSERT_EQ(file.size(), 7);
}

TEST(stl_file, read) {
    nori::detail::stl_file file("data/file.txt");
    std::vector<char> buffer(file.size());

    unsigned int bytes_read = file.read(&buffer[0], buffer.size());

    ASSERT_EQ(bytes_read, buffer.size());
    ASSERT_EQ("content", std::string(&buffer[0], bytes_read));
}

TEST(stl_file, read_some) {
    nori::detail::stl_file file("data/file.txt");
    std::vector<char> buffer(file.size() - 2);

    unsigned int bytes_read = file.read(&buffer[0], buffer.size());

    ASSERT_EQ(bytes_read, buffer.size());
    ASSERT_EQ("conte", std::string(&buffer[0], bytes_read));
}

TEST(stl_file, read_too_much) {
    nori::detail::stl_file file("data/file.txt");
    unsigned int file_size = file.size();
    std::vector<char> buffer(file_size + 10);

    unsigned int bytes_read = file.read(&buffer[0], buffer.size());

    ASSERT_EQ(bytes_read, file_size);
}
