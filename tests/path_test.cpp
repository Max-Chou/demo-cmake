#include <gtest/gtest.h>
#include "../path.hpp"
#include <filesystem>

// Common tests for both platforms
TEST(PathTest, ConstructorAndGetter) {
    EXPECT_THROW({
        Path path("./test_file.txt");
    }, std::runtime_error);
}

TEST(PathTest, EmptyPath) {
    EXPECT_THROW({
        Path path("");
    }, std::runtime_error);
}

#ifdef _WIN32
// Windows-specific tests
TEST(PathTest, WindowsPathSeparator) {
    Path path("C:\\Windows\\System32");
    std::string path_str = path.get_path();
    EXPECT_TRUE(path_str.find('\\') != std::string::npos);
}

TEST(PathTest, WindowsInvalidPath) {
    EXPECT_THROW({
        Path path("Z:\\NonExistentFolder\\NonExistentFile.txt");
    }, std::runtime_error);
}

TEST(PathTest, WindowsLongPath) {
    std::string long_path = "C:\\";
    for (int i = 0; i < 10; i++) {
        long_path += "very_long_directory_name\\";
    }
    EXPECT_THROW({
        Path path(long_path);
    }, std::runtime_error);
}

#else
// Linux-specific tests
TEST(PathTest, LinuxPathSeparator) {
    Path path("/usr/local/bin");
    std::string path_str = path.get_path();
    EXPECT_TRUE(path_str.find('/') != std::string::npos);
}

TEST(PathTest, LinuxInvalidPath) {
    EXPECT_THROW({
        Path path("/nonexistent/directory/file.txt");
    }, std::runtime_error);
}

TEST(PathTest, LinuxPermissions) {
    // Create a temporary file with no read permissions
    std::string temp_file = "/tmp/no_read_permission.txt";
    std::ofstream file(temp_file);
    file.close();
    chmod(temp_file.c_str(), S_IWUSR); // Write-only permission

    EXPECT_THROW({
        Path path(temp_file);
    }, std::runtime_error);

    // Cleanup
    std::filesystem::remove(temp_file);
}

TEST(PathTest, LinuxSymlink) {
    // Create a file and a symlink to it
    std::string real_file = "/tmp/real_file.txt";
    std::string symlink_file = "/tmp/symlink_file.txt";
    
    std::ofstream file(real_file);
    file.close();
    symlink(real_file.c_str(), symlink_file.c_str());

    Path path(symlink_file);
    EXPECT_NE(path.get_path(), symlink_file);
    EXPECT_EQ(path.get_path(), real_file);

    // Cleanup
    std::filesystem::remove(symlink_file);
    std::filesystem::remove(real_file);
}
#endif

// Cleanup test
TEST(PathTest, Destructor) {
    {
        Path path("./test_file.txt");
    }
    // If we reach here without crashes, destructor worked
    SUCCEED();
}