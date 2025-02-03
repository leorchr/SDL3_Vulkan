#include "Scene05Bodies.hpp"
#include "SphereCube.hpp"
#include "ShapeSphere.hpp"
#include "Intersections.hpp"

using gphysics::ShapeSphere;


void Scene05Bodies::Load(Renderer& renderer) {



    float radius = 10.0f;
    auto sphere = new SphereCube(renderer, radius);
    sphere->Load();

    Body body;
    body.position = Vec(0, 10, -10);
    body.orientation = Quat::identity;
    body.shape = new ShapeSphere(1.0f);
    body.drawable = sphere;
    body.inverseMass = 1.0f;
    bodies.push_back(body);

    float radius2 = 100.0f;
    auto sphere2 = new SphereCube(renderer, radius2);
    sphere2->Load();

    Body earth;
    earth.position = Vec(0, -1000, -10); 
    earth.orientation = Quat::identity;
    earth.shape = new ShapeSphere(1000.0f);
    earth.drawable = sphere2;
    earth.inverseMass = 0.0f;
    bodies.push_back(earth);
}

bool Scene05Bodies::Update(float dt) {
    bool stillRunning = ManageInput(inputState);
    // Collision checks
    for (int i = 0; i < bodies.size(); ++i)
    {
        for (int j = i + 1; j < bodies.size(); ++j)
        {
            Body& bodyA = bodies[i];
            Body& bodyB = bodies[j];
            if (bodyA.inverseMass == 0.0f && bodyB.inverseMass == 0.0f)
                continue;
            if (Intersections::Intersect(bodyA, bodyB))
            {
                bodyA.linearVelocity = Vec::zero;
                bodyB.linearVelocity = Vec::zero;
            }
        }
    }

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