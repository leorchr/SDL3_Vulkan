//
// Created by gaetz on 03/02/2025.
//

#ifndef GPHYSICS_SHAPESPHERE_HPP
#define GPHYSICS_SHAPESPHERE_HPP

#include "Shape.hpp"

namespace gphysics {
    class ShapeSphere : public Shape {
    public:
        ShapeSphere(float radiusP) : radius(radiusP)
        {
        }

        ShapeType GetType() const override { return ShapeType::SHAPE_SPHERE; }
        float radius;
    };
}

#endif //GPHYSICS_SHAPESPHERE_HPP
