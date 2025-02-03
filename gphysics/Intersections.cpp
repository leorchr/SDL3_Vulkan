#include "Intersections.hpp"
#include "ShapeSphere.hpp"

using gphysics::ShapeSphere;

bool Intersections::Intersect(Body& a, Body& b)
{
	const Vec ab = b.position - a.position;
	if (a.shape->GetType() == Shape::ShapeType::SHAPE_SPHERE
		&& b.shape->GetType() == Shape::ShapeType::SHAPE_SPHERE) {
		ShapeSphere* sphereA = reinterpret_cast<ShapeSphere*>(a.shape);
		ShapeSphere* sphereB = reinterpret_cast<ShapeSphere*>(b.shape);
		const float radiusAB = sphereA->radius + sphereB->radius;
		// We compare squares
		if (ab.SquareMagnitude() < radiusAB * radiusAB) {
			return true;
		}
	}
	return false;
}