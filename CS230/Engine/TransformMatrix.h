/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TransformMatrix.h
Project: CS230
Author: Kevin Wright
Creation date: 2/12/2021
-----------------------------------------------------------------*/
#pragma once
#include "Vec2.h"

namespace math {
    class TransformMatrix {
    public:
        TransformMatrix();

        const double* operator[](int index) const { return matrix[index]; }
        vec2 operator * (vec2 rhs) const;
        TransformMatrix operator * (TransformMatrix rhs) const;
        TransformMatrix& operator *= (TransformMatrix rhs);
        void Reset();
    protected:
        double matrix[3][3];
    };

    class TranslateMatrix : public TransformMatrix {
    public:
        TranslateMatrix(ivec2 translate);
        TranslateMatrix(vec2 translate);
    };
    
    class RotateMatrix : public TransformMatrix {
    public:
        RotateMatrix(double radians);
    };

    class ScaleMatrix : public TransformMatrix {
    public:
        ScaleMatrix(vec2 scale);
    };
}