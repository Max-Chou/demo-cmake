#include "path.hpp"

Path::Path(const std::string& path) : path(path) {
    #ifdef _WIN32
    handle = std::make_unique<HANDLE>(CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL));
    if (*handle == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Failed to open path");
    }
    char buffer[MAX_PATH];
    DWORD length = GetFinalPathNameByHandleA(*handle, buffer, MAX_PATH, VOLUME_NAME_NT);
    path = std::string(buffer, length);
    #else
    handle = std::make_unique<HANDLE>(open(path.c_str(), O_RDONLY));
    if (*handle == -1) {
        throw std::runtime_error("Failed to open path");
    }
    #endif

}

Path::~Path() {
    #ifdef _WIN32
    CloseHandle(*handle.get());
    #else
    close(*handle.get());
    #endif
    handle.reset();
}

std::string Path::get_path() const {
    return path;
}
