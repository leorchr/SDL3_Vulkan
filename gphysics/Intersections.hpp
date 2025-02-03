#pragma once
#include "Body.hpp"
#include "Shape.hpp"

using gphysics::Body;

class Intersections
{
public:
	static bool Intersect(Body& a, Body& b);
};