/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.inl
Author: Duho Choi
Creation date: 3/19/2022
-----------------------------------------------------------------*/

#include "Vec2.h"

namespace math
{
    // vec2 operators
    constexpr vec2 operator+(const vec2& left, const vec2& right) noexcept
    {
        const double new_x = left.x + right.x;
        const double new_y = left.y + right.y;
        return vec2{ new_x, new_y };
    }
    constexpr vec2& vec2::operator+=(const vec2& right) noexcept
    {
        *this = *this + right;
        return *this;
    }
    constexpr vec2 operator-(const vec2& left, const vec2& right) noexcept
    {
        const double new_x = left.x - right.x;
        const double new_y = left.y - right.y;
        return vec2{ new_x, new_y };
    }
    constexpr vec2& vec2::operator-=(const vec2& right) noexcept
    {
        *this = *this - right;
        return *this;
    }
    constexpr vec2 operator*(const vec2& left, const double scalar) noexcept
    {
        const double new_x = left.x * scalar;
        const double new_y = left.y * scalar;
        return vec2{ new_x, new_y };
    }
    constexpr vec2 operator*(const double scalar, const vec2& right) noexcept
    {
        const double new_x = scalar * right.x;
        const double new_y = scalar * right.y;
        return vec2{ new_x, new_y };
    }
    constexpr vec2& vec2::operator*=(const double scalar) noexcept
    {
        *this = *this * scalar;
        return *this;
    }
    constexpr vec2 operator/(const vec2& left, const double scalar) noexcept
    {
        const double new_x = left.x / scalar;
        const double new_y = left.y / scalar;
        return vec2{ new_x, new_y };
    }
    constexpr vec2& vec2::operator/=(const double scalar) noexcept
    {
        *this = *this / scalar;
        return *this;
    }
    constexpr bool operator==(const vec2& left, const vec2& right) noexcept
    {
        return is_equal(left.x, right.x) && is_equal(left.y, right.y);
    }
    constexpr bool operator!=(const vec2& left, const vec2& right) noexcept
    {
        return !is_equal(left.x, right.x) || !is_equal(left.y, right.y);
    }
    constexpr vec2 vec2::operator-() const noexcept
    {
        const vec2 vector{ -x, -y };
        return vector;
    }

    // vec2 functions
    constexpr double vec2::LengthSquared() noexcept
    {
        const double length = abs(this->x * this->x + this->y * this->y);
        return length;
    }
    constexpr vec2 vec2::Normalize() noexcept
    {
        *this = *this / abs(sqrt(this->x * this->x + this->y * this->y));
        return *this;
    }

    // ivec2 operators
    constexpr ivec2 operator+(const ivec2& left, const ivec2& right) noexcept
    {
        const int new_x = left.x + right.x;
        const int new_y = left.y + right.y;
        return ivec2{ new_x, new_y };
    }
    constexpr ivec2& ivec2::operator+=(const ivec2& right) noexcept
    {
        *this = *this + right;
        return *this;
    }
    constexpr ivec2 operator-(const ivec2& left, const ivec2& right) noexcept
    {
        const int new_x = left.x - right.x;
        const int new_y = left.y - right.y;
        return ivec2{ new_x, new_y };
    }
    constexpr ivec2& ivec2::operator-=(const ivec2& right) noexcept
    {
        *this = *this - right;
        return *this;
    }
    constexpr ivec2 operator*(const ivec2& left, const int scalar) noexcept
    {
        const int new_x = left.x * scalar;
        const int new_y = left.y * scalar;
        return ivec2{ new_x, new_y };
    }
    constexpr ivec2 operator*(const int scalar, const ivec2& right) noexcept
    {
        const int new_x = scalar * right.x;
        const int new_y = scalar * right.y;
        return ivec2{ new_x, new_y };
    }
    constexpr ivec2& ivec2::operator*=(const int scalar) noexcept
    {
        *this = *this * scalar;
        return *this;
    }
    constexpr ivec2 operator/(const ivec2& left, const int scalar) noexcept
    {
        const int new_x = left.x / scalar;
        const int new_y = left.y / scalar;
        return ivec2{ new_x, new_y };
    }
    constexpr ivec2& ivec2::operator/=(const int scalar) noexcept
    {
        *this = *this / scalar;
        return *this;
    }
    constexpr bool operator==(const ivec2& left, const ivec2& right) noexcept
    {
        return is_equal(left.x, right.x) && is_equal(left.y, right.y);
    }
    constexpr bool operator!=(const ivec2& left, const ivec2& right) noexcept
    {
        return !is_equal(left.x, right.x) || !is_equal(left.y, right.y);
    }
    constexpr ivec2 ivec2::operator-() const noexcept
    {
        const ivec2 vector { -x, -y };

        return vector;
    }

    // ivec2 to vec2 operators
    constexpr vec2 operator*(const ivec2& left, const double scalar) noexcept
    {
        vec2 new_vec = static_cast<vec2>(left);
        return new_vec * scalar;
    }
    constexpr vec2 operator*(const double scalar, const ivec2& right) noexcept
    {
        vec2 new_vec = static_cast<vec2>(right);
        return scalar * new_vec;
    }
    constexpr vec2 operator/(const ivec2& left, const double scalar) noexcept
    {
        vec2 new_vec = static_cast<vec2>(left);
        return new_vec / scalar;
    }
}
