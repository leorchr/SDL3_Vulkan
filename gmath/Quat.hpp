//
// Created by gaetz on 02/02/2025.
//

#ifndef GMATH_QUATERNION_HPP
#define GMATH_QUATERNION_HPP

#include "Vec.hpp"
#include "Core.hpp"

namespace gmath {

    class Quat {
    public:
        real x;
        real y;
        real z;
        real w;

        static const Quat identity;

        Quat() {
            *this = Quat::identity;
        }

        // This directly Sets the quaternion components --
        // don't use for axis/angle
        explicit Quat(real inX, real inY, real inZ, real inW) {
            Set(inX, inY, inZ, inW);
        }

        // Construct the quaternion from an axis and angle
        // It is assumed that axis is already Normalized,
        // and the angle is in radians
        explicit Quat(const Vec &axis, real angle);

        // Directly Set the internal components
        void Set(real inX, real inY, real inZ, real inW);

        void Conjugate();

        real LengthSq() const;

        real Length() const;

        void Normalize();

        // Normalize the provided quaternion
        static Quat Normalize(const Quat &q);

        // Linear interpolation
        static Quat Lerp(const Quat &a, const Quat &b, real f);

        static real Dot(const Quat &a, const Quat &b) {
            return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
        }

        // Spherical Linear Interpolation
        static Quat Slerp(const Quat &a, const Quat &b, real f);

        // Concatenate
        // Rotate by q FOLLOWED BY p
        static Quat Concatenate(const Quat &q, const Quat &p);

    };
}

#endif //GMATH_QUATERNION_HPP
