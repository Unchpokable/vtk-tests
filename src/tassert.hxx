#include <concepts>
#include <format>
#include <source_location>

#define SRC_LOC std::source_location::current()

namespace assert
{
template<typename Condition, typename... Args>
    requires std::convertible_to<Condition, bool>
void cond_fmt(Condition&& cond, std::format_string<Args...> fmt,
    const std::source_location& loc = std::source_location::current(), Args&&... args)
{
    if(!static_cast<bool>(cond)) {
        auto msg = std::format(fmt, std::forward<Args>(args)...);
        throw std::runtime_error(std::format("{}:{} in {}: {}", loc.file_name(), loc.line(), loc.function_name(), msg));
    }
}
} // namespace assert