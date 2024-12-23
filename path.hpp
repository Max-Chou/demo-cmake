#ifndef PATH_HPP
#define PATH_HPP

#include <string>

class Path {
public:
    Path(const std::string& path);
    std::string get_path() const;
private:
    std::string path_;
};

#endif