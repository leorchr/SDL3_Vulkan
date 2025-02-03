#include "Scene05Bodies.hpp"
#include "SphereCube.hpp"
#include "ShapeSphere.hpp"

using gphysics::ShapeSphere;


void Scene05Bodies::Load(Renderer& renderer) {



    auto sphere = new SphereCube(renderer);
    sphere->Load();

    Body body;
    body.position = Vec(0, 10, 0);
    body.orientation = Quat(0, 0, 0, 1);
    body.shape = new ShapeSphere(1.0f);
    body.drawable = sphere;
    body.inverseMass = 1.0f;
    bodies.push_back(body);

    auto sphere2 = new SphereCube(renderer);
    sphere2->Load();
    Body earth;
    earth.position = Vec(0, -1000, 0);
    earth.orientation = Quat(0, 0, 0, 1);
    earth.shape = new ShapeSphere(1000.0f);
    earth.drawable = sphere2;
    earth.inverseMass = 0.0f;
    bodies.push_back(earth);
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