#pragma once

#if __has_include(<filesystem>)
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

#if __has_include(<string_view>)
#include <string_view>
namespace sensorsystem::sv
{
    using std::string_view;
}

#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace sensorsystem::fs
{
    using std::experimental::string_view;
}

#else
#error "Error: An implementation of filesystem is required."
#endif