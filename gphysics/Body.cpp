#include "Body.hpp"
#include "Shape.hpp"
#include "Drawable.hpp"
#include "Mat4.hpp"
#include "iostream"

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
        position += linearVelocity * dt;


        Vec positionCM = GetCenterOfMassWorldSpace();
        Vec CMToPositon = position - positionCM;

        Mat3 orientationMat = orientation.ToMat3();
        Mat3 inertiaTensor = orientationMat * shape->InertiaTensor() * orientationMat.Transpose();

        Vec alpha = inertiaTensor.Inverse() * (angularVelocity.Cross(inertiaTensor * angularVelocity));

        angularVelocity += alpha * dt;
        // Update orientation
        Vec dAngle = angularVelocity * dt;
        Quat dq = Quat(dAngle, dAngle.Magnitude());
        orientation = dq * orientation;
        orientation.Normalize();

        // Get the new model position
        position = positionCM + dq.RotatePoint(CMToPositon);


        drawable->setTransform(Mat4::CreateTranslation(position));
    }

    void Body::ApplyWeight(f32 dt)
    {
        if (inverseMass != 0) {
            float mass = 1.0f / inverseMass;
            // Gravity needs to be an impulse I
            // I == dp, so F == dp/dt <=> dp = F * dt
            // <=> I = F * dt <=> I = m * g * dt
            Vec impulseGravity = Vec(0, -10, 0) * mass * dt;
            ApplyImpulseLinear(impulseGravity);
        }
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

    void Body::ApplyImpulseAngular(const Vec& impulse)
    {
        if (inverseMass == 0.0f) return;
        // L = I w = r x p
        // dL = I dw = r x J
        // dw = I^-1 * ( r x J )
        angularVelocity += GetInverseInertiaTensorWorldSpace() * impulse;
        // Clamp angular velocity
        // -- 30 rad per seconds, sufficient for now
        const float maxAngularSpeed = 30.0f;
        if (angularVelocity.SquareMagnitude() > maxAngularSpeed * maxAngularSpeed)
        {
            angularVelocity.Normalize();
            angularVelocity *= maxAngularSpeed;
        }
    }

    void Body::ApplyImpulse(const Vec& impulsePoint, const Vec& impulse)
    {
        if (inverseMass == 0.0f) return;
        ApplyImpulseLinear(impulse);
        // Applying impulse must produce torques through the center of mass
        Vec position = GetCenterOfMassWorldSpace();
        Vec r = impulsePoint - position;
        Vec dL = r.Cross(impulse); // World space
        ApplyImpulseAngular(dL);
    }

    Mat3 Body::GetInverseInertiaTensorBodySpace() const
    {
        Mat3 inertiaTensor = shape->InertiaTensor();
        Mat3 inverseInertiaTensor = inertiaTensor.Inverse() * inverseMass;
        return inverseInertiaTensor;
    }

    Mat3 Body::GetInverseInertiaTensorWorldSpace() const
    {
        Mat3 inertiaTensor = shape->InertiaTensor();
        Mat3 inverseInertiaTensor = inertiaTensor.Inverse() * inverseMass;
        Mat3 orient = orientation.ToMat3();
        inverseInertiaTensor = orient * inverseInertiaTensor
        * orient.Transpose();

        return inverseInertiaTensor;
    }

}