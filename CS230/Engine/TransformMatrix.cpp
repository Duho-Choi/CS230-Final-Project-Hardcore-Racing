/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TransformMatrix.cpp
Project: CS230
Author: Duho Choi
Creation date: 4/5/2022
-----------------------------------------------------------------*/
#pragma once
#include "TransformMatrix.h"

namespace math {
    TransformMatrix::TransformMatrix() {
        this->Reset();
    }

    TransformMatrix TransformMatrix::operator * (TransformMatrix rhs) const {
        TransformMatrix result;

        result.matrix[0][0] = matrix[0][0] * rhs[0][0] + matrix[0][1] * rhs[1][0] + matrix[0][2] * rhs[2][0];
        result.matrix[0][1] = matrix[0][0] * rhs[0][1] + matrix[0][1] * rhs[1][1] + matrix[0][2] * rhs[2][1];
        result.matrix[0][2] = matrix[0][0] * rhs[0][2] + matrix[0][1] * rhs[1][2] + matrix[0][2] * rhs[2][2];
        result.matrix[1][0] = matrix[1][0] * rhs[0][0] + matrix[1][1] * rhs[1][0] + matrix[1][2] * rhs[2][0];
        result.matrix[1][1] = matrix[1][0] * rhs[0][1] + matrix[1][1] * rhs[1][1] + matrix[1][2] * rhs[2][1];
        result.matrix[1][2] = matrix[1][0] * rhs[0][2] + matrix[1][1] * rhs[1][2] + matrix[1][2] * rhs[2][2];
        result.matrix[2][0] = matrix[2][0] * rhs[0][0] + matrix[2][1] * rhs[1][0] + matrix[2][2] * rhs[2][0];
        result.matrix[2][1] = matrix[2][0] * rhs[0][1] + matrix[2][1] * rhs[1][1] + matrix[2][2] * rhs[2][1];
        result.matrix[2][2] = matrix[2][0] * rhs[0][2] + matrix[2][1] * rhs[1][2] + matrix[2][2] * rhs[2][2];

        return result;
    }

    math::vec2 math::TransformMatrix::operator * (math::vec2 rhs) const {
        math::vec2 result;
        result.x = matrix[0][0] * rhs.x + matrix[0][1] * rhs.y + matrix[0][2];
        result.y = matrix[1][0] * rhs.x + matrix[1][1] * rhs.y + matrix[1][2];
        return result;
    }

    TransformMatrix& TransformMatrix::operator *= (TransformMatrix rhs) {
        (*this) = (*this) * rhs;
        return (*this);
    }

    void TransformMatrix::Reset() {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (j == i)
                    matrix[i][j] = 1;
                else
                    matrix[i][j] = 0;
            }
        }
    }

    TranslateMatrix::TranslateMatrix(ivec2 translate)
        : TransformMatrix()
    {
        matrix[0][2] = translate.x;
        matrix[1][2] = translate.y;
    }
    TranslateMatrix::TranslateMatrix(vec2 translate)
        : TransformMatrix()
    {
        matrix[0][2] = translate.x;
        matrix[1][2] = translate.y;
    }

    RotateMatrix::RotateMatrix(double radians)
        : TransformMatrix()
    {
        matrix[0][0] = cos(radians);
        matrix[0][1] = -sin(radians);
        matrix[1][0] = sin(radians);
        matrix[1][1] = cos(radians);
    }

    ScaleMatrix::ScaleMatrix(vec2 scale)
        : TransformMatrix()
    {
        matrix[0][0] = scale.x;
        matrix[1][1] = scale.y;
    }
}