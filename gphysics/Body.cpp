//
// Created by gaetz on 03/02/2025.
//

#include "Body.hpp"
#include "Shape.hpp"
#include "Drawable.hpp"

namespace gphysics {

    Body::Body(const Vec &position_, const Quat &orientation_, Shape *shape_, Drawable *drawable_) :
            position{position_},
            orientation{orientation_},
            shape{shape_},
            drawable{drawable_} {

    }

    void Body::Update(f32 dt) {
        drawable->Update(dt);
    }

}