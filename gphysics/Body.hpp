//
// Created by gaetz on 03/02/2025.
//

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
        f32 inverseMass;
        Shape* shape { nullptr };
        Drawable* drawable { nullptr };

        Vec GetCenterOfMassWorldSpace() const;
        Vec GetCenterOfMassBodySpace() const;
        Vec WorldSpaceToBodySpace(const Vec& worldPoint);
        Vec BodySpaceToWorldSpace(const Vec& bodyPoint);

        void ApplyImpulseLinear(const Vec& impulse);

    };
}

#endif //GPHYSICS_BODY_HPP
