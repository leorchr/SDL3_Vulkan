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

        void Update(f32 dt);

        Vec position;
        Quat orientation;
        Shape* shape { nullptr };
        Drawable* drawable { nullptr };

    };
}



#endif //GPHYSICS_BODY_HPP
