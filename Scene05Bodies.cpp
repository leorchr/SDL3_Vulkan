#include "Scene05Bodies.hpp"
#include "SphereCube.hpp"
#include "ShapeSphere.hpp"
#include "Intersections.hpp"
#include "Contact.hpp"

using gphysics::ShapeSphere;
using gphysics::Intersections;
using gphysics::Contact;


void Scene05Bodies::Load(Renderer& renderer) {
    float radius = 10.0f;
    auto sphere = new SphereCube(renderer, 1.0f);
    sphere->Load();

    Body body;
    body.position = Vec(0, 10, 0);
    body.orientation = Quat::identity;
    body.shape = new ShapeSphere(1.0f);
    body.drawable = sphere;
    body.inverseMass = 1.0f;
    body.elasticity = 0.5f;
    body.friction = 0.5f;
    body.linearVelocity = Vec(1, 0, 20);
    bodies.push_back(body);

    float radius2 = 100.0f;
    auto sphere2 = new SphereCube(renderer, 1000.0f);
    sphere2->Load();

    Body earth;
    earth.position = Vec(0, -1000, 0);
    earth.orientation = Quat::identity;
    earth.shape = new ShapeSphere(1000.0f);
    earth.drawable = sphere2;
    earth.inverseMass = 0.0f;
    earth.elasticity = 0.99f;
    earth.friction = 0.5f;
    bodies.push_back(earth);
}

bool Scene05Bodies::Update(float dt) {
    bool stillRunning = ManageInput(inputState);

    for (int i = 0; i < bodies.size(); ++i)
    {
        bodies[i].ApplyWeight(dt);
    }
        
    // Collision checks
    for (int i = 0; i < bodies.size(); ++i)
    {
        for (int j = i + 1; j < bodies.size(); ++j)
        {
            Body& bodyA = bodies[i];
            Body& bodyB = bodies[j];
            if (bodyA.inverseMass == 0.0f && bodyB.inverseMass == 0.0f)
                continue;
            Contact contact;
            if (Intersections::Intersect(bodyA, bodyB, contact))
            {
                Contact::ResolveContact(contact);
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