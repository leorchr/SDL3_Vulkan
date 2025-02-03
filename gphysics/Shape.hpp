//
// Created by gaetz on 02/02/2025.
//

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
    };
}




#endif //GPHYSICS_SHAPE_HPP
