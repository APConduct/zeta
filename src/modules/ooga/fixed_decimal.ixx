module;
#include <cmath>
#include <string>
#include <stdexcept>
#include <iostream>
#include <concepts>
#include <type_traits>

export module zeta.fixed_decimal;
import zeta.integer;

export namespace zeta
{
    template<typename IntegerT = integer<int>>
    class fixed_decimal
    {
    private:
        IntegerT value_;
        int scale_{};

        // Helper to get power of 10
        static constexpr IntegerT pow10(int exp) noexcept {
            if (exp < 0) {
                return IntegerT(1) / pow10(-exp);
            }
            if (exp == 0) return IntegerT(1);
            
            IntegerT result(1);
            IntegerT base(10);
            
            while (exp > 0) {
                if (exp % 2 == 1) {
                    result *= base;
                }
                base *= base;
                exp /= 2;
            }
            return result;
        }

    public:
        using value_type = IntegerT;
        
        // Constructors
        constexpr fixed_decimal() noexcept : value_(0), scale_(0) {}
        constexpr fixed_decimal(const IntegerT& value, int scale) noexcept : value_(value), scale_(scale) {}
        
        // Conversion constructor for other integer types
        template<std::integral T>
        constexpr explicit fixed_decimal(const T& value, int scale = 0) noexcept
            : value_(static_cast<typename IntegerT::value_type>(value)), scale_(scale) {}
            
        // Floating-point constructor with automatic scale detection
        constexpr explicit fixed_decimal(double value, int scale = 2) noexcept
            : value_(static_cast<typename IntegerT::value_type>(value * std::pow(10, scale))), scale_(scale) {}
            
        // Conversion from other fixed_decimal types
        template<typename OtherIntegerT>
        constexpr explicit fixed_decimal(const fixed_decimal<OtherIntegerT>& other) noexcept
            : value_(IntegerT(other.value())), scale_(other.scale()) {}
            
        // Accessors
        [[nodiscard]] constexpr const IntegerT& value() const noexcept { return value_; }
        [[nodiscard]] constexpr int scale() const noexcept { return scale_; }
        
        // Type conversions
        [[nodiscard]] constexpr double as_double() const noexcept {
            return static_cast<double>(value_.template as<double>()) / std::pow(10, scale_);
        }
        
        [[nodiscard]] constexpr int as_int() const noexcept {
            return static_cast<int>(std::round(as_double()));
        }
        
        constexpr explicit operator double() const noexcept {
            return as_double();
        }
        
        // Unary operators
        constexpr fixed_decimal operator-() const noexcept {
            return fixed_decimal(-value_, scale_);
        }
        
        constexpr fixed_decimal operator~() const noexcept {
            return fixed_decimal(~value_, scale_);
        }
        
        // Binary arithmetic operators with type promotion
        template<typename OtherIntegerT>
        constexpr auto operator+(const fixed_decimal<OtherIntegerT>& other) const noexcept {
            using ResultIntegerT = decltype(std::declval<IntegerT>() + std::declval<OtherIntegerT>());
            using ResultT = fixed_decimal<ResultIntegerT>;
            
            if (scale_ == other.scale()) {
                return ResultT(value_ + other.value(), scale_);
            }
            
            int new_scale = std::max(scale_, other.scale());
            auto adjusted_value = value_ * pow10(new_scale - scale_) +
                                  other.value() * pow10(new_scale - other.scale());
            return ResultT(adjusted_value, new_scale);
        }
        
        template<typename OtherIntegerT>
        constexpr auto operator-(const fixed_decimal<OtherIntegerT>& other) const noexcept {
            using ResultIntegerT = decltype(std::declval<IntegerT>() - std::declval<OtherIntegerT>());
            using ResultT = fixed_decimal<ResultIntegerT>;
            
            if (scale_ == other.scale()) {
                return ResultT(value_ - other.value(), scale_);
            }
            
            int new_scale = std::max(scale_, other.scale());
            auto adjusted_value = value_ * pow10(new_scale - scale_) -
                                  other.value() * pow10(new_scale - other.scale());
            return ResultT(adjusted_value, new_scale);
        }
        
        template<typename OtherIntegerT>
        constexpr auto operator*(const fixed_decimal<OtherIntegerT>& other) const noexcept {
            using ResultIntegerT = decltype(std::declval<IntegerT>() * std::declval<OtherIntegerT>());
            return fixed_decimal<ResultIntegerT>(value_ * other.value(), scale_ + other.scale());
        }
        
        template<typename OtherIntegerT>
        constexpr auto operator/(const fixed_decimal<OtherIntegerT>& other) const {
            if (other.value() == OtherIntegerT(0)) {
                throw std::domain_error("Division by zero");
            }
            
            using ResultIntegerT = decltype(std::declval<IntegerT>() / std::declval<OtherIntegerT>());
            constexpr int precision = 6;
            
            auto scaled_value = value_ * pow10(precision);
            return fixed_decimal<ResultIntegerT>(scaled_value / other.value(), 
                                               scale_ + precision - other.scale());
        }
        
        template<typename OtherIntegerT>
        constexpr auto operator%(const fixed_decimal<OtherIntegerT>& other) const {
            if (other.value() == OtherIntegerT(0)) {
                throw std::domain_error("Modulo by zero");
            }
            
            using ResultIntegerT = decltype(std::declval<IntegerT>() % std::declval<OtherIntegerT>());
            using ResultT = fixed_decimal<ResultIntegerT>;
            
            if (scale_ == other.scale()) {
                return ResultT(value_ % other.value(), scale_);
            }
            
            int new_scale = std::max(scale_, other.scale());
            auto adjusted_value = value_ * pow10(new_scale - scale_) %
                                 (other.value() * pow10(new_scale - other.scale()));
            return ResultT(adjusted_value, new_scale);
        }
        
        // Operations with arithmetic types
        template<typename T>
        requires std::is_arithmetic_v<T>
        constexpr auto operator+(const T& other) const noexcept {
            return *this + fixed_decimal<IntegerT>(other, scale_);
        }
        
        template<typename T>
        requires std::is_arithmetic_v<T>
        constexpr auto operator-(const T& other) const noexcept {
            return *this - fixed_decimal<IntegerT>(other, scale_);
        }
        
        template<typename T>
        requires std::is_arithmetic_v<T>
        constexpr auto operator*(const T& other) const noexcept {
            return *this * fixed_decimal<IntegerT>(other, 0);
        }
        
        template<typename T>
        requires std::is_arithmetic_v<T>
        constexpr auto operator/(const T& other) const {
            return *this / fixed_decimal<IntegerT>(other, 0);
        }
        
        // Compound assignment operators
        template<typename OtherIntegerT>
        constexpr fixed_decimal& operator+=(const fixed_decimal<OtherIntegerT>& other) noexcept {
            *this = *this + other;
            return *this;
        }
        
        template<typename OtherIntegerT>
        constexpr fixed_decimal& operator-=(const fixed_decimal<OtherIntegerT>& other) noexcept {
            *this = *this - other;
            return *this;
        }
        
        template<typename OtherIntegerT>
        constexpr fixed_decimal& operator*=(const fixed_decimal<OtherIntegerT>& other) noexcept {
            *this = *this * other;
            return *this;
        }
        
        template<typename OtherIntegerT>
        constexpr fixed_decimal& operator/=(const fixed_decimal<OtherIntegerT>& other) {
            *this = *this / other;
            return *this;
        }
        
        template<typename T>
        requires std::is_arithmetic_v<T>
        constexpr fixed_decimal& operator+=(const T& other) noexcept {
            *this = *this + other;
            return *this;
        }
        
        // Increment/decrement operators
        constexpr fixed_decimal& operator++() noexcept {
            *this += fixed_decimal(IntegerT(1), 0);
            return *this;
        }
        
        constexpr fixed_decimal operator++(int) noexcept {
            fixed_decimal temp = *this;
            ++(*this);
            return temp;
        }
        
        constexpr fixed_decimal& operator--() noexcept {
            *this -= fixed_decimal(IntegerT(1), 0);
            return *this;
        }
        
        constexpr fixed_decimal operator--(int) noexcept {
            fixed_decimal temp = *this;
            --(*this);
            return temp;
        }
        
        // Comparison operators
        template<typename OtherIntegerT>
        constexpr auto operator<=>(const fixed_decimal<OtherIntegerT>& other) const noexcept {
            const auto a = normalize();
            const auto b = other.normalize();
            
            int common_scale = std::max(a.scale_, b.scale_);
            auto a_scaled = a.value_ * pow10(common_scale - a.scale_);
            auto b_scaled = b.value() * pow10(common_scale - b.scale());
            
            return a_scaled <=> b_scaled;
        }
        
        template<typename OtherIntegerT>
        constexpr bool operator==(const fixed_decimal<OtherIntegerT>& other) const noexcept {
            const auto a = normalize();
            const auto b = other.normalize();
            
            if (a.scale_ == b.scale()) {
                return a.value_ == b.value();
            }
            
            int common_scale = std::max(a.scale_, b.scale_);
            auto a_scaled = a.value_ * pow10(common_scale - a.scale_);
            auto b_scaled = b.value() * pow10(common_scale - b.scale());
            
            return a_scaled == b_scaled;
        }
        
        // Utility methods
        [[nodiscard]] constexpr fixed_decimal normalize() const noexcept {
            if (scale_ <= 0) return *this;
            
            IntegerT temp = value_;
            int new_scale = scale_;
            
            while (new_scale > 0 && temp % IntegerT(10) == IntegerT(0)) {
                temp /= IntegerT(10);
                new_scale--;
            }
            
            return fixed_decimal(temp, new_scale);
        }
        
        [[nodiscard]] constexpr fixed_decimal round(int new_scale) const noexcept {
            if (scale_ == new_scale) return *this;
            
            if (scale_ < new_scale) {
                // Increasing precision - just scale up
                return fixed_decimal(value_ * pow10(new_scale - scale_), new_scale);
            }
            
            // Decreasing precision - need to round
            IntegerT factor = pow10(scale_ - new_scale);
            IntegerT rounded_value = (value_ + (factor / IntegerT(2))) / factor;
            return fixed_decimal(rounded_value, new_scale);
        }
        
        [[nodiscard]] constexpr fixed_decimal floor() const noexcept {
            IntegerT int_part = value_ / pow10(scale_);
            return fixed_decimal(int_part, 0);
        }
        
        [[nodiscard]] constexpr fixed_decimal ceil() const noexcept {
            IntegerT int_part = value_ / pow10(scale_);
            IntegerT frac_part = value_ % pow10(scale_);
            
            if (frac_part > IntegerT(0)) {
                int_part += IntegerT(1);
            }
            
            return fixed_decimal(int_part, 0);
        }
        
        // Static factory methods
        static constexpr fixed_decimal from_double(double val, int precision = 6) noexcept {
            int scale = 0;
            double working_val = std::abs(val);
            
            // Find appropriate scale based on fractional part
            while (std::abs(working_val - std::round(working_val)) > 1e-10 && scale < precision) {
                working_val *= 10;
                scale++;
            }
            
            return fixed_decimal(
                IntegerT(static_cast<typename IntegerT::value_type>(std::round(val * std::pow(10, scale)))),
                scale);
        }
        
        // Stream output
        friend std::ostream& operator<<(std::ostream& os, const fixed_decimal& val) noexcept {
            os << val.as_double();
            return os;
        }
    };
    
    // Free function operators for mixed-type operations
    template<typename T, typename IntegerT>
    requires std::is_arithmetic_v<T>
    constexpr auto operator+(const T& lhs, const fixed_decimal<IntegerT>& rhs) noexcept {
        return fixed_decimal<IntegerT>(lhs, rhs.scale()) + rhs;
    }
    
    template<typename T, typename IntegerT>
    requires std::is_arithmetic_v<T>
    constexpr auto operator-(const T& lhs, const fixed_decimal<IntegerT>& rhs) noexcept {
        return fixed_decimal<IntegerT>(lhs, rhs.scale()) - rhs;
    }
    
    template<typename T, typename IntegerT>
    requires std::is_arithmetic_v<T>
    constexpr auto operator*(const T& lhs, const fixed_decimal<IntegerT>& rhs) noexcept {
        return fixed_decimal<IntegerT>(lhs, 0) * rhs;
    }
    
    template<typename T, typename IntegerT>
    requires std::is_arithmetic_v<T>
    constexpr auto operator/(const T& lhs, const fixed_decimal<IntegerT>& rhs) {
        return fixed_decimal<IntegerT>(lhs, 0) / rhs;
    }
    
    // Type aliases
    using default_fixed_decimal = fixed_decimal<default_integer>;
    using fixed_decimal_t = default_fixed_decimal; // For backward compatibility
    
    // Fixed-size decimal aliases
    using fd8 = fixed_decimal<i8>;
    using fd16 = fixed_decimal<i16>;
    using fd32 = fixed_decimal<i32>;
    using fd64 = fixed_decimal<i64>;
    
    // Unsigned variants
    using ufd8 = fixed_decimal<u8>;
    using ufd16 = fixed_decimal<u16>;
    using ufd32 = fixed_decimal<u32>;
    using ufd64 = fixed_decimal<u64>;

    // Fast/least variants
    using fast_fd32 = fixed_decimal<fast_i32>;
    using fast_fd64 = fixed_decimal<fast_i64>;
    using least_fd32 = fixed_decimal<least_i32>;
    using least_fd64 = fixed_decimal<least_i64>;
    
    // High-precision variants
    using high_precision_fd = fixed_decimal<i64>;
    
    // Updated concept for type checking
    template <typename T>
    concept is_fixed_decimal = requires(T t) {
        { t.as_double() } -> std::convertible_to<double>;
        { t.scale() } -> std::convertible_to<int>;
    };
}