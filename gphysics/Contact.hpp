#pragma once
#include "Vec.hpp"
#include "Body.hpp"
using gmath::Vec;
using gphysics::Body;

namespace gphysics {
	class Contact
	{
	public:
		Vec ptOnAWorldSpace;
		Vec ptOnALocalSpace;
		Vec ptOnBWorldSpace;
		Vec ptOnBLocalSpace;
		Vec normal;
		float separationDistance;
		float timeOfImpact;
		Body* a{ nullptr };
		Body* b{ nullptr };
		static void ResolveContact(Contact& contact);
	};
}