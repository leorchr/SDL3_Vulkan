#include "Body.hpp"
#include "Shape.hpp"
#include "Drawable.hpp"
#include "Mat4.hpp"

namespace gphysics {

    Body::Body(const Vec &position_, const Quat &orientation_, Shape *shape_, Drawable *drawable_) :
            position{position_},
            orientation{orientation_},
            shape{shape_},
            drawable{drawable_} {
    }

    Body::Body() :
        position{ Vec::zero },
        orientation{ Quat::identity },
        shape{ nullptr },
        drawable{ nullptr } {}

    void Body::Update(f32 dt) {

        if (inverseMass != 0) {
            float mass = 1.0f / inverseMass;
            // Gravity needs to be an impulse I
            // I == dp, so F == dp/dt <=> dp = F * dt
            // <=> I = F * dt <=> I = m * g * dt
            Vec impulseGravity = Vec(0, -10, 0) * mass * dt;
            ApplyImpulseLinear(impulseGravity);
            position += linearVelocity * dt;
        }


        drawable->setTransform(Mat4::CreateTranslation(position));
    }


    Vec Body::GetCenterOfMassWorldSpace() const
    {
        const Vec centerOfMass = shape->GetCenterOfMass();
        const Vec pos = position + orientation.RotatePoint(centerOfMass);
        return pos;
    }

    Vec Body::GetCenterOfMassBodySpace() const
    {
        return shape->GetCenterOfMass();
    }

    Vec Body::WorldSpaceToBodySpace(const Vec& worldPoint)
    {
        const Vec tmp = worldPoint - GetCenterOfMassWorldSpace();
        const Quat invertOrient = orientation.Inverse();
        Vec bodySpace = invertOrient.RotatePoint(tmp);
        return bodySpace;
    }

    Vec Body::BodySpaceToWorldSpace(const Vec& bodyPoint)
    {
        Vec worldSpace = GetCenterOfMassWorldSpace()

            + orientation.RotatePoint(bodyPoint);

        return worldSpace;
    }

    void Body::ApplyImpulseLinear(const Vec& impulse)
    {
        if (inverseMass == 0.0f) return;
        // dv = J / m
        linearVelocity += impulse * inverseMass;
    }

}