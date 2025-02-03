#include <Vec.hpp>
using gmath::Vec;

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

    protected:
        Vec centerOfMass;
    };
}




#endif //GPHYSICS_SHAPE_HPP
