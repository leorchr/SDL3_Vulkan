#include "Intersections.hpp"
#include "ShapeSphere.hpp"

using gphysics::ShapeSphere;

namespace gphysics {

	bool Intersections::Intersect(Body& a, Body& b, Contact& contact)
	{
		contact.a = &a;
		contact.b = &b;
		const Vec ab = b.position - a.position;
		contact.normal = ab;
		contact.normal.Normalize();
		if (a.shape->GetType() == Shape::ShapeType::SHAPE_SPHERE
			&& b.shape->GetType() == Shape::ShapeType::SHAPE_SPHERE) {
			ShapeSphere* sphereA = static_cast<ShapeSphere*>(a.shape);
			ShapeSphere* sphereB = static_cast<ShapeSphere*>(b.shape);
			contact.ptOnAWorldSpace = a.position

				+ contact.normal * sphereA->radius;

			contact.ptOnBWorldSpace = b.position

				- contact.normal * sphereB->radius;
			const float radiusAB = sphereA->radius + sphereB->radius;
			// We compare squares
			if (ab.SquareMagnitude() < radiusAB * radiusAB) {
				return true;
			}
		}
		return false;
	}
}