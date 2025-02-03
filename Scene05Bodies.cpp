#include "Scene05Bodies.hpp"
#include "SphereCube.hpp"
#include "ShapeSphere.hpp"

using gphysics::ShapeSphere;


void Scene05Bodies::Load(Renderer& renderer) {
    auto shape = new ShapeSphere(1.0f);
    auto sphere = new SphereCube(renderer);
    sphere->Load();

    bodies.emplace_back(Vec::zero, Quat::identity, shape, sphere);
}

bool Scene05Bodies::Update(float dt) {
    bool stillRunning = ManageInput(inputState);
    for (auto& body : bodies) {
        body.Update(dt);
    }

    return stillRunning;
}

void Scene05Bodies::Draw(Renderer& renderer) {
    renderer.Begin();

    for (auto& body : bodies) {
        body.drawable->Draw(renderer);
    }
    renderer.End();
}

void Scene05Bodies::Unload(Renderer& renderer) {
    for (auto& body : bodies) {
        body.drawable->Unload();
    }
}