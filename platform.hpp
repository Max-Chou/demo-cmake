#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#endif

#include <string>
#include <memory>
#include <stdexcept>
#endif