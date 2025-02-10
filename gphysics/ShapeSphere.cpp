#include "ShapeSphere.hpp"


namespace gphysics {
    Mat3 ShapeSphere::InertiaTensor() const
    {
        Mat3 tensor;
        tensor.Zero();
        tensor.m0 = 2.0f * radius * radius / 5.0f;
        tensor.m4 = 2.0f * radius * radius / 5.0f;
        tensor.m8 = 2.0f * radius * radius / 5.0f;

        return tensor;
    }
}
