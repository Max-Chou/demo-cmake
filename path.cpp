#include "path.hpp"

Path::Path(const std::string& path) : path_(path) {}

std::string Path::get_path() const {
    return path_;
}
