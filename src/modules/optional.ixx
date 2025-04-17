//
// Created by Aidan Jost on 4/10/25.
//

module;
#include <stdexcept>
#include <functional>
export module zeta.optional;
import zeta.config;

export namespace zeta
{
    template<typename T>
    struct optional
    {
    private:
        union
        {
            T value_;
            char dummy_[sizeof(T)];
        };
        bool has_value_;
    public:
        constexpr optional() : dummy_{}, has_value_(false) {}

        constexpr explicit optional(const T& value) : value_(value), has_value_(true) {}
        constexpr explicit optional(T&& value) : value_(std::move(value)), has_value_(true) {}

        [[nodiscard]] constexpr bool has_value() const { return has_value_; }
        constexpr T& value() & {
            if (!has_value_)
            {
                if constexpr (config::use_exceptions)
                {
                    throw std::logic_error("optional has no value");

                }
                std::terminate();
            };
            return value_;
        }

        constexpr T value_or(const T& default_value) const&
        {
            return has_value_ ? value_ : default_value;
        }

        template<typename F>
        auto map(F&& f) const -> optional<decltype(f(std::declval<T>()))>
        {
            using ResultType = decltype(f(std::declval<T>()));
            if (has_value_)
            {
                return optional<ResultType>(f(value_));
            }
            return optional<ResultType>();
        }
        ~optional() noexcept
        {
            if (has_value_)
            {
                value_.~T();
            }
        }


    };
}