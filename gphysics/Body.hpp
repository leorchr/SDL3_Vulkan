#ifndef GPHYSICS_BODY_HPP
#define GPHYSICS_BODY_HPP

#include "Vec.hpp"
#include "Quat.hpp"

namespace gdraw {
    class Shape;
    class Drawable;
}

namespace gphysics {
    class Shape;
}

using gmath::Vec;
using gmath::Quat;
using gmath::Mat3;
using gphysics::Shape;
using gdraw::Drawable;

namespace gphysics {
    class Body
    {
    public:
        Body(const Vec &position_, const Quat &orientation_, Shape* shape_, Drawable* drawable_);
        Body();

        void Update(f32 dt);

        void ApplyWeight(f32 dt);

        Vec position;
        Quat orientation;
        Vec linearVelocity;
        Vec angularVelocity;

        f32 inverseMass;
        f32 elasticity;
        f32 friction;

        Shape* shape { nullptr };
        Drawable* drawable { nullptr };

        Vec GetCenterOfMassWorldSpace() const;
        Vec GetCenterOfMassBodySpace() const;
        Vec WorldSpaceToBodySpace(const Vec& worldPoint);
        Vec BodySpaceToWorldSpace(const Vec& bodyPoint);

        void ApplyImpulseLinear(const Vec& impulse);
        void ApplyImpulseAngular(const Vec& impulse);
        void ApplyImpulse(const Vec& impulsePoint, const Vec& impulse);

        Mat3 GetInverseInertiaTensorBodySpace() const;
        Mat3 GetInverseInertiaTensorWorldSpace() const;

    };
}

#endif //GPHYSICS_BODY_HPP
