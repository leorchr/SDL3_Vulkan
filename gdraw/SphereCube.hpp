#pragma once
#ifndef GDRAW_SPHERECUBE_HPP
#define GDRAW_SPHERECUBE_HPP

#include "SphereCubeMaterial.hpp"
#include "SphereCubeMesh.hpp"
#include "Mat4.hpp"
#include "Drawable.hpp"

using gmath::Mat4;
namespace gdraw
{
    class SphereCube : public Drawable
    {
    public:
        explicit SphereCube(Renderer& renderer_, float radius);

        void Load();
        void Update(f32 dt);
        void Draw(const Renderer& renderer);
        void Unload();

    private:
        SphereCubeMaterial material;
        SphereCubeMesh mesh;
        void Bind();
    };
}


#endif //GDRAW_CUBE_HPP