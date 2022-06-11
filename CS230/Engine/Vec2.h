/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.h
Author: Duho Choi
Creation date: 3/14/2022
-----------------------------------------------------------------*/
#pragma once
#include <cmath>
#include <limits>

namespace math
{
    [[nodiscard]] constexpr double abs(double d) noexcept { return (d < 0.0) ? -d : d; }

    [[nodiscard]] constexpr bool is_equal(double d1, double d2) noexcept
    {
        return abs(d1 - d2) <= std::numeric_limits<double>::epsilon() * abs(d1 + d2);
    }

    [[nodiscard]] constexpr bool is_equal(int i1, int i2) noexcept { return i1 == i2; }

    struct [[nodiscard]] vec2
    {
        double x{ 0 }, y{ 0 };
        constexpr vec2() noexcept = default;
        constexpr vec2(double x_value, double y_value) noexcept
            : x{ x_value }, y{ y_value }
        {
        }
        constexpr explicit vec2(double value) noexcept
            : vec2{ value, value }
        {
        }
        //constexpr vec2()

        constexpr vec2& operator+=(const vec2& right) noexcept;
        constexpr vec2& operator-=(const vec2& right) noexcept;
        constexpr vec2& operator*=(const double scalar) noexcept;
        constexpr vec2& operator/=(const double scalar) noexcept;

        constexpr vec2 operator-() const noexcept;

        [[nodiscard]] constexpr double LengthSquared() noexcept;
        constexpr vec2 Normalize() noexcept;
    };

    [[nodiscard]] constexpr vec2 operator+(const vec2& left, const vec2& right) noexcept;
    [[nodiscard]] constexpr vec2 operator-(const vec2& left, const vec2& right) noexcept;
    [[nodiscard]] constexpr vec2 operator*(const vec2& left, const double scalar) noexcept;
    [[nodiscard]] constexpr vec2 operator*(const double scalar, const vec2& right) noexcept;
    [[nodiscard]] constexpr vec2 operator/(const vec2& left, const double scalar) noexcept;
    [[nodiscard]] constexpr bool operator==(const vec2& left, const vec2& right) noexcept;
    [[nodiscard]] constexpr bool operator!=(const vec2& left, const vec2& right) noexcept;

    struct [[nodiscard]] ivec2
    {
        int x{ 0 }, y{ 0 };
        constexpr ivec2() noexcept = default;
        constexpr ivec2(int x_value, int y_value) noexcept
            : x{ x_value }, y{ y_value }
        {
        }
        constexpr explicit ivec2(int value) noexcept
            : ivec2{ value, value }
        {
        }

        constexpr ivec2& operator+=(const ivec2& right) noexcept;
        constexpr ivec2& operator-=(const ivec2& right) noexcept;
        constexpr ivec2& operator*=(const int scalar) noexcept;
        constexpr ivec2& operator/=(const int scalar) noexcept;

        constexpr ivec2 operator-() const noexcept;

        explicit constexpr operator vec2() const noexcept
        {
            return vec2{ static_cast<double>(x), static_cast<double>(y) };
        }
    };

    [[nodiscard]] constexpr ivec2 operator+(const ivec2& left, const ivec2& right) noexcept;
    [[nodiscard]] constexpr ivec2 operator-(const ivec2& left, const ivec2& right) noexcept;
    [[nodiscard]] constexpr ivec2 operator*(const ivec2& left, const int scalar) noexcept;
    [[nodiscard]] constexpr ivec2 operator*(const int scalar, const ivec2& right) noexcept;
    [[nodiscard]] constexpr ivec2 operator/(const ivec2& left, const int scalar) noexcept;
    [[nodiscard]] constexpr bool operator==(const ivec2& left, const ivec2& right) noexcept;
    [[nodiscard]] constexpr bool operator!=(const ivec2& left, const ivec2& right) noexcept;

    // ivec2 to vec2 operators
    [[nodiscard]] constexpr vec2 operator*(const ivec2& left, const double scalar) noexcept;
    [[nodiscard]] constexpr vec2 operator*(const double scalar, const ivec2& right) noexcept;
    [[nodiscard]] constexpr vec2 operator/(const ivec2& left, const double scalar) noexcept;
}

#include "Vec2.inl"
