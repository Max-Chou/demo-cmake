#ifndef PATH_HPP
#define PATH_HPP

#include "platform.hpp"
class Path {
public:
    #ifdef _WIN32
    using HANDLE = void*;
    #else
    using HANDLE = int;
    #endif

    Path(const std::string& path);
    ~Path();
    std::string get_path() const;
private:
    std::string path;
    std::unique_ptr<HANDLE> handle;
};

#endif