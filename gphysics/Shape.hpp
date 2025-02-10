#include <Mat3.hpp>
#include <Vec.hpp>
using gmath::Vec;
using gmath::Mat3;

#ifndef GPHYSICS_SHAPE_HPP
#define GPHYSICS_SHAPE_HPP

namespace gphysics {
    class Shape {
    public:
        enum class ShapeType
        {
            SHAPE_SPHERE,
        };

        [[nodiscard]] virtual ShapeType GetType() const = 0;
        virtual Vec GetCenterOfMass() const { return centerOfMass; }

        virtual Mat3 InertiaTensor() const = 0;

    protected:
        Vec centerOfMass;
    };
}




#endif //GPHYSICS_SHAPE_HPP
