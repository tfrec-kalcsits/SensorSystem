#pragma once

#if __has_include(<filesystem>)
#error "Has filesystem"
#include <filesystem>
namespace sensorsystem::fs
{
    using std::filesystem::exists;
}

#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace sensorsystem::fs
{
    using std::experimental::filesystem::exists;
}

#else
#error "Error: An implementation of filesystem is required."
#endif