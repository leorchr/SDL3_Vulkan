#ifndef GDRAW_DRAWABLE_HPP
#define GDRAW_DRAWABLE_HPP

#include "Mat4.hpp"
#include <Defines.hpp>

using gmath::Mat4;

namespace gdraw {

    class Renderer;

    class Drawable {
    public:
        virtual void Load() = 0;
        virtual void Update(f32 dt) = 0;
        virtual void Draw(const Renderer& renderer) = 0;
        virtual void Unload() = 0;
        Mat4 getTransform() const { return transform; }
        void setTransform(Mat4 newTransform);

    protected:
        Mat4 transform{ Mat4::identity };
    };
}

#endif