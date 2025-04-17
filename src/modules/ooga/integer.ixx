module;
#include <string>
#include <concepts>
#include <cmath>
#include <type_traits>
#include <cstdint>
export module zeta.integer;

export namespace zeta
{
    /**
     * A wrapper class for integer values with comprehensive operator support
     */
    template<std::integral StorageT = int>
    struct integer {
    private:
        StorageT value_;

    public:
        using value_type = StorageT;

        // Constructors and basic conversions
        constexpr integer(const StorageT value = 0) noexcept : value_(value) {}

        // Conversion constructor from other integral types
        template<std::integral OtherT>
        constexpr explicit integer(const OtherT value) noexcept : value_(static_cast<StorageT>(value)) {}

        // Conversion constructor from other integer specializations
        template<std::integral OtherT>
        constexpr explicit integer(const integer<OtherT>& other) noexcept
            : value_(static_cast<StorageT>(other.template as<StorageT>())) {}

        constexpr operator StorageT() const noexcept { return value_; }

        [[nodiscard]] std::string to_string() const { return std::to_string(value_); }

        template <typename T>
        [[nodiscard]] constexpr T as() const noexcept { return static_cast<T>(value_); }

        [[nodiscard]] constexpr float to_float() const noexcept { return as<float>(); }
        [[nodiscard]] constexpr double to_double() const noexcept { return as<double>(); }

        // Assignment operators
        constexpr integer& operator=(StorageT value) noexcept {
            value_ = value;
            return *this;
        }
        constexpr integer& operator=(const integer& other) noexcept = default;

        // Increment/decrement operators
        constexpr integer& operator++() noexcept {
            ++value_;
            return *this;
        }

        constexpr integer& operator--() noexcept {
            --value_;
            return *this;
        }

        constexpr integer operator++(int) noexcept {
            const integer temp = *this;
            ++value_;
            return temp;
        }

        constexpr integer operator--(int) noexcept {
            const integer temp = *this;
            --value_;
            return temp;
        }

        // Unary operators
        constexpr integer operator-() const noexcept {
            return {-value_};
        }

        constexpr integer operator~() const noexcept {
            return {~value_};
        }

        // Compound assignment operators
        constexpr integer& operator+=(const integer& other) noexcept {
            value_ += other.value_;
            return *this;
        }

        constexpr integer& operator-=(const integer& other) noexcept {
            value_ -= other.value_;
            return *this;
        }

        constexpr integer& operator*=(const integer& other) noexcept {
            value_ *= other.value_;
            return *this;
        }

        constexpr integer& operator/=(const integer& other) noexcept {
            value_ /= other.value_;
            return *this;
        }

        constexpr integer& operator%=(const integer& other) noexcept {
            value_ %= other.value_;
            return *this;
        }

        constexpr integer& operator&=(const integer& other) noexcept {
            value_ &= other.value_;
            return *this;
        }

        constexpr integer& operator|=(const integer& other) noexcept {
            value_ |= other.value_;
            return *this;
        }

        constexpr integer& operator^=(const integer& other) noexcept {
            value_ ^= other.value_;
            return *this;
        }

        constexpr integer& operator<<=(const integer& other) noexcept {
            value_ <<= other.value_;
            return *this;
        }

        constexpr integer& operator>>=(const integer& other) noexcept {
            value_ >>= other.value_;
            return *this;
        }

        template<std::integral T>
        constexpr integer& operator+=(const T& other) noexcept {
            value_ += static_cast<StorageT>(other);
            return *this;
        }

        template<std::integral T>
        constexpr integer& operator-=(const T& other) noexcept {
            value_ -= static_cast<StorageT>(other);
            return *this;
        }

        template<std::integral T>
        constexpr integer& operator*=(const T& other) noexcept {
            value_ *= static_cast<StorageT>(other);
            return *this;
        }

        template<std::integral T>
        constexpr integer& operator/=(const T& other) noexcept {
            value_ /= static_cast<StorageT>(other);
            return *this;
        }

        template<std::integral T>
        constexpr integer& operator%=(const T& other) noexcept {
            value_ %= static_cast<StorageT>(other);
            return *this;
        }

        template<std::integral T>
        constexpr integer& operator&=(const T& other) noexcept {
            value_ &= static_cast<StorageT>(other);
            return *this;
        }

        template<std::integral T>
        constexpr integer& operator|=(const T& other) noexcept {
            value_ |= static_cast<StorageT>(other);
            return *this;
        }

        template<std::integral T>
        constexpr integer& operator^=(const T& other) noexcept {
            value_ ^= static_cast<StorageT>(other);
            return *this;
        }

        template<std::integral T>
        constexpr integer& operator<<=(const T& other) noexcept {
            value_ <<= static_cast<StorageT>(other);
            return *this;
        }

        template<std::integral T>
        constexpr integer& operator>>=(const T& other) noexcept {
            value_ >>= static_cast<StorageT>(other);
            return *this;
        }

        // Binary operators between two integers with common type promotion
        template<std::integral OtherT>
        auto operator+(const integer<OtherT>& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, OtherT>;
            return integer<ResultT>(static_cast<ResultT>(value_) + static_cast<ResultT>(other.template as<ResultT>()));
        }

        template<std::integral OtherT>
        auto operator-(const integer<OtherT>& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, OtherT>;
            return integer<ResultT>(static_cast<ResultT>(value_) - static_cast<ResultT>(other.template as<ResultT>()));
        }

        template<std::integral OtherT>
        auto operator*(const integer<OtherT>& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, OtherT>;
            return integer<ResultT>(static_cast<ResultT>(value_) * static_cast<ResultT>(other.template as<ResultT>()));
        }

        template<std::integral OtherT>
        auto operator/(const integer<OtherT>& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, OtherT>;
            return integer<ResultT>(static_cast<ResultT>(value_) / static_cast<ResultT>(other.template as<ResultT>()));
        }

        double operator/(double other) const noexcept {
            return static_cast<double>(value_) / other;
        }

        template<std::integral OtherT>
        auto operator%(const integer<OtherT>& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, OtherT>;
            return integer<ResultT>(static_cast<ResultT>(value_) % static_cast<ResultT>(other.template as<ResultT>()));
        }

        template<std::integral OtherT>
        auto operator&(const integer<OtherT>& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, OtherT>;
            return integer<ResultT>(static_cast<ResultT>(value_) & static_cast<ResultT>(other.template as<ResultT>()));
        }

        template<std::integral OtherT>
        auto operator|(const integer<OtherT>& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, OtherT>;
            return integer<ResultT>(static_cast<ResultT>(value_) | static_cast<ResultT>(other.template as<ResultT>()));
        }

        template<std::integral OtherT>
        auto operator^(const integer<OtherT>& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, OtherT>;
            return integer<ResultT>(static_cast<ResultT>(value_) ^ static_cast<ResultT>(other.template as<ResultT>()));
        }

        template<std::integral OtherT>
        auto operator<<(const integer<OtherT>& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, OtherT>;
            return integer<ResultT>(static_cast<ResultT>(value_) << static_cast<ResultT>(other.template as<ResultT>()));
        }

        template<std::integral OtherT>
        auto operator>>(const integer<OtherT>& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, OtherT>;
            return integer<ResultT>(static_cast<ResultT>(value_) >> static_cast<ResultT>(other.template as<ResultT>()));
        }

        // Binary operators with integral types
        template<std::integral T>
        auto operator+(const T& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, T>;
            return integer<ResultT>(static_cast<ResultT>(value_) + static_cast<ResultT>(other));
        }

        template<std::integral T>
        auto operator-(const T& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, T>;
            return integer<ResultT>(static_cast<ResultT>(value_) - static_cast<ResultT>(other));
        }

        template<std::integral T>
        auto operator*(const T& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, T>;
            return integer<ResultT>(static_cast<ResultT>(value_) * static_cast<ResultT>(other));
        }

        template<std::integral T>
        auto operator/(const T& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, T>;
            return integer<ResultT>(static_cast<ResultT>(value_) / static_cast<ResultT>(other));
        }

        template<std::integral T>
        auto operator%(const T& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, T>;
            return integer<ResultT>(static_cast<ResultT>(value_) % static_cast<ResultT>(other));
        }

        template<std::integral T>
        auto operator&(const T& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, T>;
            return integer<ResultT>(static_cast<ResultT>(value_) & static_cast<ResultT>(other));
        }

        template<std::integral T>
        auto operator|(const T& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, T>;
            return integer<ResultT>(static_cast<ResultT>(value_) | static_cast<ResultT>(other));
        }

        template<std::integral T>
        auto operator^(const T& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, T>;
            return integer<ResultT>(static_cast<ResultT>(value_) ^ static_cast<ResultT>(other));
        }

        template<std::integral T>
        auto operator<<(const T& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, T>;
            return integer<ResultT>(static_cast<ResultT>(value_) << static_cast<ResultT>(other));
        }

        template<std::integral T>
        auto operator>>(const T& other) const noexcept {
            using ResultT = std::common_type_t<StorageT, T>;
            return integer<ResultT>(static_cast<ResultT>(value_) >> static_cast<ResultT>(other));
        }

        // Comparison operators
        template<std::integral OtherT>
        constexpr bool operator==(const integer<OtherT>& other) const noexcept {
            return value_ == other.template as<StorageT>();
        }

        template<std::integral OtherT>
        constexpr bool operator!=(const integer<OtherT>& other) const noexcept {
            return value_ != other.template as<StorageT>();
        }

        template<std::integral OtherT>
        constexpr auto operator<=>(const integer<OtherT>& other) const noexcept {
            return value_ <=> other.template as<StorageT>();
        }

        template<std::integral T>
        constexpr bool operator==(const T& other) const noexcept {
            return value_ == static_cast<StorageT>(other);
        }

        template<std::integral T>
        constexpr bool operator!=(const T& other) const noexcept {
            return value_ != static_cast<StorageT>(other);
        }

        template<std::integral T>
        constexpr auto operator<=>(const T& other) const noexcept {
            return value_ <=> static_cast<StorageT>(other);
        }

        // Utility methods
        [[nodiscard]] constexpr int digits() const noexcept {
            if (value_ == 0) return 1;
            int count = 0;
            auto n = value_;
            if (n < 0) n = -n;
            while (n != 0) {
                n /= 10;
                count++;
            }
            return count;
        }

        template<std::integral T>
        [[nodiscard]] constexpr auto pow(const T& exponent) const noexcept {
            if (exponent < 0) return integer<StorageT>(0);

            StorageT result = 1;
            StorageT base = value_;
            auto exp = static_cast<StorageT>(exponent);

            while (exp > 0) {
                if (exp % 2 == 1) {
                    result *= base;
                }
                base *= base;
                exp /= 2;
            }
            return integer<StorageT>(result);
        }

        template<typename T>
        requires (!std::integral<T> && std::is_arithmetic_v<T>)
        [[nodiscard]] double pow(const T& exponent) const noexcept {
            return std::pow(static_cast<double>(value_), static_cast<double>(exponent));
        }


    };

    // Free function operators for mixed-type operations
    template<std::integral LhsT, std::integral RhsT>
    auto operator+(const LhsT& lhs, const integer<RhsT>& rhs) noexcept {
        using ResultT = std::common_type_t<LhsT, RhsT>;
        return integer<ResultT>(static_cast<ResultT>(lhs) + static_cast<ResultT>(rhs));
    }

    template<std::integral LhsT, std::integral RhsT>
    auto operator-(const LhsT& lhs, const integer<RhsT>& rhs) noexcept {
        using ResultT = std::common_type_t<LhsT, RhsT>;
        return integer<ResultT>(static_cast<ResultT>(lhs) - static_cast<ResultT>(rhs));
    }

    template<std::integral LhsT, std::integral RhsT>
    auto operator*(const LhsT& lhs, const integer<RhsT>& rhs) noexcept {
        using ResultT = std::common_type_t<LhsT, RhsT>;
        return integer<ResultT>(static_cast<ResultT>(lhs) * static_cast<ResultT>(rhs));
    }

    template<std::integral LhsT, std::integral RhsT>
    auto operator/(const LhsT& lhs, const integer<RhsT>& rhs) noexcept {
        using ResultT = std::common_type_t<LhsT, RhsT>;
        return integer<ResultT>(static_cast<ResultT>(lhs) / static_cast<ResultT>(rhs));
    }

    template<std::integral LhsT, std::integral RhsT>
    auto operator%(const LhsT& lhs, const integer<RhsT>& rhs) noexcept {
        using ResultT = std::common_type_t<LhsT, RhsT>;
        return integer<ResultT>(static_cast<ResultT>(lhs) % static_cast<ResultT>(rhs));
    }

    template<std::integral LhsT, std::integral RhsT>
    auto operator&(const LhsT& lhs, const integer<RhsT>& rhs) noexcept {
        using ResultT = std::common_type_t<LhsT, RhsT>;
        return integer<ResultT>(static_cast<ResultT>(lhs) & static_cast<ResultT>(rhs));
    }

    template<std::integral LhsT, std::integral RhsT>
    auto operator|(const LhsT& lhs, const integer<RhsT>& rhs) noexcept {
        using ResultT = std::common_type_t<LhsT, RhsT>;
        return integer<ResultT>(static_cast<ResultT>(lhs) | static_cast<ResultT>(rhs));
    }

    template<std::integral LhsT, std::integral RhsT>
    auto operator^(const LhsT& lhs, const integer<RhsT>& rhs) noexcept {
        using ResultT = std::common_type_t<LhsT, RhsT>;
        return integer<ResultT>(static_cast<ResultT>(lhs) ^ static_cast<ResultT>(rhs));
    }

    template<std::integral LhsT, std::integral RhsT>
    constexpr bool operator==(const LhsT& lhs, const integer<RhsT>& rhs) noexcept {
        return static_cast<RhsT>(lhs) == static_cast<RhsT>(rhs);
    }

    template<std::integral LhsT, std::integral RhsT>
    constexpr bool operator!=(const LhsT& lhs, const integer<RhsT>& rhs) noexcept {
        return static_cast<RhsT>(lhs) != static_cast<RhsT>(rhs);
    }

    template<std::integral LhsT, std::integral RhsT>
    constexpr auto operator<=>(const LhsT& lhs, const integer<RhsT>& rhs) noexcept {
        return static_cast<RhsT>(lhs) <=> static_cast<RhsT>(rhs);
    }

    // Common aliases
    using default_integer = integer<int>;

    // Fixed-size integer aliases
    using i8 = integer<std::int8_t>;
    using i16 = integer<std::int16_t>;
    using i32 = integer<std::int32_t>;
    using i64 = integer<std::int64_t>;

    // Unsigned variants
    using u8 = integer<std::uint8_t>;
    using u16 = integer<std::uint16_t>;
    using u32 = integer<std::uint32_t>;
    using u64 = integer<std::uint64_t>;

    // Fast/least variants

    using fast_i32 = integer<std::int_fast32_t>;
    using fast_i64 = integer<std::int_fast64_t>;
    using least_i32 = integer<std::int_least32_t>;
    using least_i64 = integer<std::int_least64_t>;

    // For backwards compatibility with existing code
    using integer_t = default_integer;

    // Updated concept for type checking
    template <typename T>
    concept is_integer = std::integral<T> ||
                        (requires { typename T::value_type; } &&
                         std::integral<typename T::value_type>);
}