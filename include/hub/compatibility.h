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

#elif __has_include(<experimental/string_view>)
#include <experimental/filesystem>
namespace sensorsystem::sv
{
    using std::experimental::string_view;
}

#else
#error "Error: An implementation of string_view is required."
#endif

#if __has_include(<optional>)
#include <optional>
namespace sensorsystem::opt
{
    using std::optional;
}

#elif __has_include(<experimental/optional>)
#include <experimental/optional>
namespace sensorsystem::opt
{
    using std::experimental::optional;
}

#else
#error "Error: An implementation of optional is required."
#endif


#if __has_include(<variant>)
#include <variant>
namespace sensorsystem::var
{
    using std::variant;
}

#elif __has_include(<experimental/variant>)
#include <experimental/variant>
namespace sensorsystem::var
{
    using std::experimental::variant;
}

#else
#error "Error: An implementation of variant is required."
#endif