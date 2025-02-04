#pragma once
#include "Body.hpp"
#include "Shape.hpp"
#include "Contact.hpp"

using gphysics::Body;
using gphysics::Contact;

namespace gphysics {
	class Intersections
	{
	public:
		static bool Intersect(Body& a, Body& b, Contact& contact);
	};
}