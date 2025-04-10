module;
#include <string>
// ReSharper disable once CppUnusedIncludeDirective
#include <concepts>
#include <cmath>
export module zeta.integer;

export namespace zeta
{
    /**
     * A wrapper class for integer values with comprehensive operator support
     */
    struct  integer {
    private:
        int value_;

    public:
        // Constructors and basic conversions
        integer(int value = 0) noexcept : value_(value) {}


        operator int() const noexcept { return value_; }        [[nodiscard]] std::string to_string() const { return std::to_string(value_); }
        
        template <typename T>
        [[nodiscard]] T as() const noexcept { return static_cast<T>(value_); }

        [[nodiscard]] float to_float() const noexcept { return as<float>(); }
        [[nodiscard]] double to_double() const noexcept { return as<double>(); }

        // Assignment operator
        integer& operator=(int value) noexcept {
            value_ = value;
            return *this;
        }
        integer& operator=(const integer& other) noexcept = default;

        // Increment/decrement operators
        integer& operator++() noexcept {
            ++value_;
            return *this;
        }

        integer& operator--() noexcept {
            --value_;
            return *this;
        }

        integer operator++(int) noexcept {
            const integer temp = *this;
            ++value_;
            return temp;
        }

        integer operator--(int) noexcept {
            const integer temp = *this;
            --value_;
            return temp;
        }

        // Unary operators
        integer operator-() const noexcept {
            return {-value_};
        }

        integer operator~() const noexcept {
            return {~value_};
        }

        // Compound assignment operators
        integer& operator+=(const integer& other) noexcept {
            value_ += other.value_;
            return *this;
        }

        integer& operator-=(const integer& other) noexcept {
            value_ -= other.value_;
            return *this;
        }

        integer& operator*=(const integer& other) noexcept {
            value_ *= other.value_;
            return *this;
        }

        integer& operator/=(const integer& other) noexcept {
            value_ /= other.value_;
            return *this;
        }

        integer& operator%=(const integer& other) noexcept {
            value_ %= other.value_;
            return *this;
        }

        integer& operator&=(const integer& other) noexcept {
            value_ &= other.value_;
            return *this;
        }

        integer& operator|=(const integer& other) noexcept {
            value_ |= other.value_;
            return *this;
        }

        integer& operator^=(const integer& other) noexcept {
            value_ ^= other.value_;
            return *this;
        }

        integer& operator<<=(const integer& other) noexcept {
            value_ <<= other.value_;
            return *this;
        }

        integer& operator>>=(const integer& other) noexcept {
            value_ >>= other.value_;
            return *this;
        }

        template<std::integral T>
        integer& operator+=(const T& other) noexcept {
            value_ += static_cast<int>(other);
            return *this;
        }

        template<std::integral T>
        integer& operator-=(const T& other) noexcept {
            value_ -= static_cast<int>(other);
            return *this;
        }

        template<std::integral T>
        integer& operator*=(const T& other) noexcept {
            value_ *= static_cast<int>(other);
            return *this;
        }

        template<std::integral T>
        integer& operator/=(const T& other) noexcept {
            value_ /= static_cast<int>(other);
            return *this;
        }

        template<std::integral T>
        integer& operator%=(const T& other) noexcept {
            value_ %= static_cast<int>(other);
            return *this;
        }

        template<std::integral T>
        integer& operator&=(const T& other) noexcept {
            value_ &= static_cast<int>(other);
            return *this;
        }

        template<std::integral T>
        integer& operator|=(const T& other) noexcept {
            value_ |= static_cast<int>(other);
            return *this;
        }

        template<std::integral T>
        integer& operator^=(const T& other) noexcept {
            value_ ^= static_cast<int>(other);
            return *this;
        }

        template<std::integral T>
        integer& operator<<=(const T& other) noexcept {
            value_ <<= static_cast<int>(other);
            return *this;
        }

        template<std::integral T>
        integer& operator>>=(const T& other) noexcept {
            value_ >>= static_cast<int>(other);
            return *this;
        }

        // Binary operators between two integers
        integer operator+(const integer& other) const noexcept {
            return {value_ + other.value_};
        }

        integer operator-(const integer& other) const noexcept {
            return {value_ - other.value_};
        }

        // template<typename T, typename U>
        // U operator*(const T& other) const noexcept {
        //     return {value_ * other.value_};
        // }

        integer operator*(const integer& other) const noexcept {
            return {value_ * other.value_};
        }




        integer operator/(const integer& other) const noexcept {
            return {value_ / other.value_};
        }

        double operator/(double other) const noexcept {
            return static_cast<double>(value_) / other;
        }

        integer operator%(const integer& other) const noexcept {
            return {value_ % other.value_};
        }

        integer operator&(const integer& other) const noexcept {
            return {value_ & other.value_};
        }

        integer operator|(const integer& other) const noexcept {
            return {value_ | other.value_};
        }

        integer operator^(const integer& other) const noexcept {
            return {value_ ^ other.value_};
        }

        integer operator<<(const integer& other) const noexcept {
            return {value_ << other.value_};
        }

        integer operator>>(const integer& other) const noexcept {
            return {value_ >> other.value_};
        }

        // Binary operators with integral types
        template<std::integral T>
        integer operator+(const T& other) const noexcept {
            return integer(value_ + static_cast<int>(other));
        }

        template<std::integral T>
        integer operator-(const T& other) const noexcept {
            return integer(value_ - static_cast<int>(other));
        }

        template<std::integral T>
        integer operator*(const T& other) const noexcept {
            return integer(value_ * static_cast<int>(other));
        }

        template<std::integral T>
        integer operator/(const T& other) const noexcept {
            return integer(value_ / static_cast<int>(other));
        }

        template<std::integral T>
        integer operator%(const T& other) const noexcept {
            return integer(value_ % static_cast<int>(other));
        }

        template<std::integral T>
        integer operator&(const T& other) const noexcept {
            return integer(value_ & static_cast<int>(other));
        }

        template<std::integral T>
        integer operator|(const T& other) const noexcept {
            return integer(value_ | static_cast<int>(other));
        }

        template<std::integral T>
        integer operator^(const T& other) const noexcept {
            return integer(value_ ^ static_cast<int>(other));
        }

        template<std::integral T>
        integer operator<<(const T& other) const noexcept {
            return integer(value_ << static_cast<int>(other));
        }

        template<std::integral T>
        integer operator>>(const T& other) const noexcept {
            return integer(value_ >> static_cast<int>(other));
        }

        // Comparison operators
        bool operator==(const integer& other) const noexcept {
            return value_ == other.value_;
        }

        bool operator!=(const integer& other) const noexcept {
            return value_ != other.value_;
        }

        bool operator<(const integer& other) const noexcept {
            return value_ < other.value_;
        }

        bool operator<=(const integer& other) const noexcept {
            return value_ <= other.value_;
        }

        bool operator>(const integer& other) const noexcept {
            return value_ > other.value_;
        }

        bool operator>=(const integer& other) const noexcept {
            return value_ >= other.value_;
        }

        template<std::integral T>
        bool operator==(const T& other) const noexcept {
            return value_ == static_cast<int>(other);
        }

        template<std::integral T>
        bool operator!=(const T& other) const noexcept {
            return value_ != static_cast<int>(other);
        }

        template<std::integral T>
        bool operator<(const T& other) const noexcept {
            return value_ < static_cast<int>(other);
        }

        template<std::integral T>
        bool operator<=(const T& other) const noexcept {
            return value_ <= static_cast<int>(other);
        }

        template<std::integral T>
        bool operator>(const T& other) const noexcept {
            return value_ > static_cast<int>(other);
        }

        template<std::integral T>
        bool operator>=(const T& other) const noexcept {
            return value_ >= static_cast<int>(other);
        }

        // Utility methods
        [[nodiscard]] int digits() const noexcept {
            if (value_ == 0) return 1;
            int count = 0;
            int n = value_;
            if (n < 0) n = -n;
            while (n != 0) {
                n /= 10;
                count++;
            }
            return count;
        }

        // Power operation (renamed to avoid confusion with bitwise XOR)
        template<std::integral T>
        [[nodiscard]] integer pow(const T& exponent) const noexcept {
            if (exponent < 0) return {0}; // handle negative exponents
            
            int result = 1;
            int base = value_;
            int exp = static_cast<int>(exponent);
            
            while (exp > 0) {
                if (exp % 2 == 1) {
                    result *= base;
                }
                base *= base;
                exp /= 2;
            }
            return {result};
        }
        //generic pow function (for fractional exponents)
        template<std::floating_point T>
        double pow(const T& exponent) const noexcept {
            return std::pow(static_cast<double>(value_), static_cast<double>(exponent));
        }
        [[nodiscard]] double pow(double exponent) const noexcept {
            return std::pow(static_cast<double>(value_), exponent);
        }



    };



    // Friend operators for reversed operand order
    template<std::integral T>
    integer operator+(const T& lhs, const integer& rhs) noexcept {
        return integer(static_cast<int>(lhs) + static_cast<int>(rhs));
    }

    template<std::integral T>
    integer operator-(const T& lhs, const integer& rhs) noexcept {
        return integer(static_cast<int>(lhs) - static_cast<int>(rhs));
    }

    template<std::integral T>
    integer operator*(const T& lhs, const integer& rhs) noexcept {
        return integer(static_cast<int>(lhs) * static_cast<int>(rhs));
    }

    template<std::integral T>
    integer operator/(const T& lhs, const integer& rhs) noexcept {
        return integer(static_cast<int>(lhs) / static_cast<int>(rhs));
    }

    template<std::integral T>
    integer operator%(const T& lhs, const integer& rhs) noexcept {
        return integer(static_cast<int>(lhs) % static_cast<int>(rhs));
    }

    template<std::integral T>
    integer operator&(const T& lhs, const integer& rhs) noexcept {
        return integer(static_cast<int>(lhs) & static_cast<int>(rhs));
    }

    template<std::integral T>
    integer operator|(const T& lhs, const integer& rhs) noexcept {
        return integer(static_cast<int>(lhs) | static_cast<int>(rhs));
    }

    template<std::integral T>
    integer operator^(const T& lhs, const integer& rhs) noexcept {
        return integer(static_cast<int>(lhs) ^ static_cast<int>(rhs));
    }

    template<std::integral T>
    bool operator==(const T& lhs, const integer& rhs) noexcept {
        return static_cast<int>(lhs) == static_cast<int>(rhs);
    }

    template<std::integral T>
    bool operator!=(const T& lhs, const integer& rhs) noexcept {
        return static_cast<int>(lhs) != static_cast<int>(rhs);
    }

    template<std::integral T>
    bool operator<(const T& lhs, const integer& rhs) noexcept {
        return static_cast<int>(lhs) < static_cast<int>(rhs);
    }

    template<std::integral T>
    bool operator<=(const T& lhs, const integer& rhs) noexcept {
        return static_cast<int>(lhs) <= static_cast<int>(rhs);
    }

    template<std::integral T>
    bool operator>(const T& lhs, const integer& rhs) noexcept {
        return static_cast<int>(lhs) > static_cast<int>(rhs);
    }

    template<std::integral T>
    bool operator>=(const T& lhs, const integer& rhs) noexcept {
        return static_cast<int>(lhs) >= static_cast<int>(rhs);
    }





}