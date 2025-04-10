//
// Created by Aidan Jost on 4/10/25.
//

module;
#include <cmath>
#include <string>
#include <stdexcept>
# include  <iostream>

export module zeta.fixdec;
import zeta.integer;

export namespace zeta
{
    struct fixed_decimal
    {
    private:
        integer value_;
        int scale_{};

        // helper to get power of 10
        static integer pow10(int exp) noexcept {
            return integer(10).pow(exp);
        }


    public:


        fixed_decimal() noexcept : value_(0) {}
        fixed_decimal(integer value, int scale) noexcept : value_(value), scale_(scale) {}


        // Implicit conversion to double

        fixed_decimal operator~() const noexcept {
            return {~value_, scale_};
        }

        fixed_decimal operator-(const fixed_decimal& other) const noexcept
        {
            if (scale_ == other.scale_) {
                return {value_ - other.value_, scale_};
            }
            int new_scale = std::max(scale_, other.scale_);
            integer adjusted_value = value_ * pow10(new_scale - scale_) -
                                     other.value_ * pow10(new_scale - other.scale_);
            return {adjusted_value, new_scale};
        }

        fixed_decimal operator*(const fixed_decimal& other) const noexcept
        {
            return {value_ * other.value_, scale_ + other.scale_};
        }
        fixed_decimal operator/(const fixed_decimal& other) const noexcept
        {
            return {value_ * pow10(scale_) / other.value_, scale_ - other.scale_};
        }
        fixed_decimal operator%(const fixed_decimal& other) const noexcept
        {
            if (scale_ == other.scale_) {
                return {value_ % other.value_, scale_};
            }
            int new_scale = std::max(scale_, other.scale_);
            integer adjusted_value = value_ * pow10(new_scale - scale_) %
                                     other.value_ * pow10(new_scale - other.scale_);
            return {adjusted_value, new_scale};
        }


        [[nodiscard]] fixed_decimal normalize() const noexcept {
            if (scale_ <= 0) return *this;

            integer temp = value_;
            int new_scale = scale_;

            while (new_scale > 0 && temp % 10 == 0) {
                temp /= 10;
                new_scale--;
            }

            return {temp, new_scale};
        }
        explicit fixed_decimal(double value, int scale = 2) noexcept
            : value_(static_cast<int>(value * pow10(scale))), scale_(scale) {}

        [[nodiscard]] fixed_decimal divide(const fixed_decimal& other, int result_scale) const noexcept {
            // check for division by zero
            if (other.value_ == 0) {
                throw std::runtime_error("Division by zero");
            }
            // Perform the division
            integer adjusted_value = value_ * pow10(result_scale);
            integer result = adjusted_value / other.value_;
            return {result, result_scale};
        }


        [[nodiscard]] int as_int() const
        {
            return static_cast<int>(std::round(as_double()));
        }

        // round to int
        [[nodiscard]] integer round_to_integer() const noexcept {
            return {as_int()};
        }


        friend std::ostream& operator<<(std::ostream& os, const fixed_decimal& val) noexcept;



        bool operator==(const fixed_decimal& other) const noexcept {
            const fixed_decimal a = normalize();
            const fixed_decimal b = other.normalize();
            return a.value_ == b.value_ && a.scale_ == b.scale_;
        }

        [[nodiscard]] fixed_decimal ceil() const noexcept {
            const double d = as_double();
            return from_double(std::ceil(d));
        }

        [[nodiscard]] fixed_decimal floor() const noexcept
        {
            const double d = as_double();
            return from_double(std::floor(d));
        }


        fixed_decimal& operator+=(const fixed_decimal& other) noexcept {
            *this = *this + other;
            return *this;
        }

        fixed_decimal& operator-=(const fixed_decimal& other) noexcept
        {
            *this = *this - other;
            return *this;
        }
        fixed_decimal& operator*=(const fixed_decimal& other) noexcept
        {
            *this = *this * other;
            return *this;
        }
        fixed_decimal& operator/=(const fixed_decimal& other) noexcept
        {
            *this = *this / other;
            return *this;
        }
        fixed_decimal& operator%=(const fixed_decimal& other) noexcept
        {
            *this = *this % other;
            return *this;
        }
        fixed_decimal& operator++() noexcept
        {
            *this += fixed_decimal(1, scale_);
            return *this;
        }
        fixed_decimal& operator--() noexcept
        {
            *this -= fixed_decimal(1, scale_);
            return *this;
        }

        template <std::integral T>
        fixed_decimal operator+(const T& other) const noexcept {
            return *this + fixed_decimal(static_cast<int>(other), scale_);
        }
        template <std::integral T>
        fixed_decimal operator-(const T& other) const noexcept {
            return *this - fixed_decimal(static_cast<int>(other), scale_);
        }
        template <std::integral T>
        fixed_decimal operator*(const T& other) const noexcept {
            return *this * fixed_decimal(static_cast<int>(other), scale_);
        }
        template <std::integral T>
        fixed_decimal operator/(const T& other) const noexcept {
            return *this / fixed_decimal(static_cast<int>(other), scale_);
        }
        template <std::integral T>
        fixed_decimal operator%(const T& other) const noexcept {
            return *this % fixed_decimal(static_cast<int>(other), scale_);
        }
        template <std::integral T>
        fixed_decimal& operator+=(const T& other) noexcept {
            return *this = *this + fixed_decimal(static_cast<int>(other), scale_);
        }
        template <std::integral T>
        fixed_decimal& operator-=(const T& other) noexcept {
            return *this = *this - fixed_decimal(static_cast<int>(other), scale_);
        }
        template <std::integral T>
        fixed_decimal& operator*=(const T& other) noexcept {
            return *this = *this * fixed_decimal(static_cast<int>(other), scale_);
        }
        template <std::integral T>
        fixed_decimal& operator/=(const T& other) noexcept {
            return *this = *this / fixed_decimal(static_cast<int>(other), scale_);
        }
        template <std::integral T>
        fixed_decimal& operator%=(const T& other) noexcept {
            return *this = *this % fixed_decimal(static_cast<int>(other), scale_);
        }

        bool operator==(const integer& other) const noexcept {
            return *this == fixed_decimal(other, scale_);
        }
        bool operator!=(const fixed_decimal& other) const noexcept {
            return !(*this == other);
        }
        bool operator!=(const integer& other) const noexcept {
            return *this != fixed_decimal(other, scale_);
        }
        bool operator<(const fixed_decimal& other) const noexcept {
            const fixed_decimal a = normalize();
            const fixed_decimal b = other.normalize();
            return a.value_ < b.value_;
        }
        bool operator<(const integer& other) const noexcept {
            return *this < fixed_decimal(other, scale_);
        }

        bool operator<=(const fixed_decimal& other) const noexcept
        {
            const fixed_decimal a = normalize();
            const fixed_decimal b = other.normalize();
            return a.value_ <= b.value_;
        }
        bool operator<=(const integer& other) const noexcept
        {
            return *this <= fixed_decimal(other, scale_);
        }

        bool operator>(const fixed_decimal& other) const noexcept
        {
            const fixed_decimal a = normalize();
            const fixed_decimal b = other.normalize();
            return a.value_ > b.value_;
        }

        bool operator>(const integer& other) const noexcept
        {
            return *this > fixed_decimal(other, scale_);
        }
        bool operator>=(const fixed_decimal& other) const noexcept
        {
            const fixed_decimal a = normalize();
            const fixed_decimal b = other.normalize();
            return a.value_ >= b.value_;
        }
        bool operator>=(const integer& other) const noexcept
        {
            return *this >= fixed_decimal(other, scale_);
        }
        [[nodiscard]] fixed_decimal plus(const fixed_decimal& other) const noexcept
        {
            return *this + other;
        }
        [[nodiscard]] fixed_decimal minus(const fixed_decimal& other) const noexcept
        {
            return *this - other;
        }
        [[nodiscard]] fixed_decimal times(const fixed_decimal& other) const noexcept
        {
            return *this * other;
        }
        [[nodiscard]] fixed_decimal divided_by(const fixed_decimal& other) const noexcept
        {
            return *this / other;
        }
        fixed_decimal& operator=(integer other) noexcept
        {
            value_ = other;
            return *this;
        }
        fixed_decimal& operator=(double other) noexcept
        {
            *this = from_double(other);
            return *this;
        }
        fixed_decimal& operator+=(double other) noexcept
        {
            *this = *this + from_double(other);
            return *this;
        }
        fixed_decimal& operator-=(double other) noexcept
        {
            *this = *this - from_double(other);
            return *this;
        }
        fixed_decimal& operator*=(double other) noexcept
        {
            *this = *this * from_double(other);
            return *this;
        }
        fixed_decimal& operator/=(double other) noexcept
        {
            *this = *this / from_double(other);
            return *this;
        }



        fixed_decimal(const fixed_decimal& other) noexcept = default;
        fixed_decimal& operator=(const fixed_decimal& other) noexcept = default;
        fixed_decimal(fixed_decimal&& other) noexcept = default;
        fixed_decimal& operator=(fixed_decimal&& other) noexcept = default;

        template<std::integral T>
        fixed_decimal(T value, int scale) noexcept : value_(static_cast<int>(value)), scale_(scale) {}

        explicit operator double() const noexcept {
            return static_cast<double>(value_.as<int>()) / static_cast<double>(pow10(scale_));
        }

        fixed_decimal operator-() const noexcept {
            return {-value_, scale_};
        }

        fixed_decimal operator+(const fixed_decimal& other) const noexcept {
            if (scale_ == other.scale_) {
                return {value_ + other.value_, scale_};
            }
            int new_scale = std::max(scale_, other.scale_);
            integer adjusted_value = pow10(new_scale - scale_) * value_ +
                                     other.value_ * pow10(new_scale - other.scale_);
            return {adjusted_value, new_scale};
        }

        [[nodiscard]] double as_double() const noexcept {
            return static_cast<double>(value_.as<int>()) / static_cast<double>(pow10(scale_));
        }

        static fixed_decimal from_double(double val) noexcept {
            int new_scale = 0;
            while (std::abs(val - std::round(val)) > 1e-10 && new_scale < 10) {
                val *= 10;
                new_scale++;
            }
            return {static_cast<int>(std::round(val)), new_scale};
        }

        [[nodiscard]] fixed_decimal round(int new_scale) const noexcept {
            if (scale_ == new_scale) return *this;

            integer factor = pow10(new_scale - scale_);
            integer rounded_value = (value_ * factor + (factor / 2)) / factor;
            return {rounded_value, new_scale};
        }

        friend std::ostream& operator<<(std::ostream& os, const fixed_decimal& val) noexcept {
            const fixed_decimal normalized = val.normalize();
            os << (normalized.value_ / static_cast<double>(pow10(normalized.scale_)));
            if (normalized.scale_ > 0) {
                os << '.';
                const integer remainder = normalized.value_ % pow10(normalized.scale_);
                std::string decimals = remainder.to_string();
                while (decimals.length() < normalized.scale_) {
                    decimals = "0" + decimals;
                }
                os << decimals;
            }
            return os;
        }

        
        

    };



};
